//helping function to check if a character or sequence of character exits in the dictionary (reads only)
bool existsInDict(const std::unordered_map<std::string, int> &dict, const std::string &key) {
    return dict.find(key) != dict.end();
}

void lempelZiv(std::string  txt) {
    //intital dictionary
    std::unordered_map<std::string, int> dictionary;
    std::vector<uint16_t> compressed;

    //Creating a 'log' and compressed files
    std::ofstream logFile("log.txt");
    std::ofstream outFile("compressed.bin", std::ios::binary);

    //Checking if the files opened successfully
    if (!logFile.is_open() || !outFile.is_open()) {
        std::cerr << "Failed to open output files!" << std::endl;
        return;
    }

    //Inserting every ASCII character to dictionary before reading the text
    for (int i = 0; i < 256; i++) {
        std::string ch(1, static_cast<char>(i)); // Creates a 1-character string from int i
        dictionary[ch] = i;                      // e.g. "A" = 65, "B" = 66

        logFile << "Character: " << ch << " outputs: " << dictionary[ch] << std::endl;
    }

    int val = 256;
    const int MAX_DICT_SIZE = 65535; //Maximum size of 16 bit int
    std::string current = "";

    //LZW Compression loop
    int p = 1; //percentage feedback
    for (char c : txt) {
        std::string combinedStr = current + c;

        logFile << "===============================" << std::endl;
        logFile << "Trying to add: " << combinedStr << " to dictionary" << std::endl;

        //If the str matches then it exapands it with the next character for the next iteration of the loop 
        //e.g. str "ABCABCABC" "A" found in dictiony then A becomes "AB" 
        if(existsInDict(dictionary, combinedStr)) {
            logFile << "Found: " << combinedStr << " in dictionary" << std::endl;
            logFile << "===============================" << std::endl;

            current = combinedStr;
        }
        else {
            logFile << "Did not found: " << combinedStr << " in dictionary, adding it with val: " << val << std::endl;
            logFile << "===============================" << std::endl;

            if(!current.empty()) compressed.push_back(dictionary[current]); //Emitting the code for the match we had before character 'c'
            if(val < MAX_DICT_SIZE) dictionary[combinedStr] = val++; //Adding the new unseen pattern to the dictionary
            else logFile << "MAXIMUM SIZE OF DICTIONINARY REACHED" << std::endl;

            current = std::string(1, c); //Resetting current to hold just the new character for the next iteration
        }

        //Creating a progress bar as the algorithm runs
        std::cout << "\rProgress: " << (p * 100) / txt.length() << "%" << std::flush;
        p++;
    }

    //Breaking line after the progress bar
    std::cout << std::endl;

    //Emitting the final remaining pattern after loop terminates
    if (!current.empty()) {
        logFile << "===============================" << std::endl;
        logFile << "Adding remaining pattern: " << current << "with value: " << dictionary[current] << std::endl;
        logFile << "===============================" << std::endl;
        
        compressed.push_back(dictionary[current]);
    }

    std::cout << "Compressed code: ";   
    for (int i : compressed) {
        std::cout << i << " ";
    }

    //Outputing compressed file
    outFile.write(reinterpret_cast<const char*>(compressed.data()), 
                  compressed.size() * sizeof(uint16_t));

    //closing files
    logFile.close();
    outFile.close();

    std::cout << std::endl;
}