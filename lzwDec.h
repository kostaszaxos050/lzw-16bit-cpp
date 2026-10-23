bool codeInDict(const std::unordered_map<int, std::string> &dict, const int &key) {
    return dict.find(key) != dict.end();
}

void lzwDecompression () {
    //Opening file in binary mode and placing the streams initial position at the end
    std::ifstream compFile("compressed.bin", std::ios::binary | std::ios::ate);
    //File to store the decompressed text and the log files
    std::ofstream decFile("decompressed.txt");
    std::ofstream logFile("decLog.txt");
    
    if (!compFile.is_open() || !decFile.is_open() || !logFile.is_open()) {
        std::cerr << "Failed to open compressed file or decompressed file!" << std::endl;
        return;
    }

    //Getting file size
    std::streamsize fileSize = compFile.tellg();

    //Checking if file size matches the 2 byte alignment for uint_16
    if(fileSize % sizeof(uint16_t) != 0) {
        std::cerr << "File size is not aligned to 16-bit emmited codes" << std::endl;
        return;
    }

    size_t elementCount = fileSize / sizeof(uint16_t);
    
    //Setting seek to the begining
    compFile.seekg(0, std::ios::beg);

    //Allocating the vector for the emmtied codes
    std::vector<uint16_t> codes(elementCount);

    //Reading raw bytes directly into the vector buffer
    compFile.read(reinterpret_cast<char*>(codes.data()), fileSize);

    //Initializing a dictionary for the decompression but this time with int as the key and string as the value
    std::unordered_map<int, std::string> dictionary;

    //Prefilling it with the 255 known ASCII characters
    for (int i = 0; i < 256; i++) {
        std::string ch(1, static_cast<char>(i)); // Creates a 1-character string from int i
        dictionary[i] = ch;                      // e.g. "A" = 65, "B" = 66

        logFile << "Emmited code: " << i << " outputs: " << dictionary[i] << std::endl;
    }

    //LZW Decompression loop
    uint16_t oldCode, currentCode;
    oldCode = codes.at(0);
    logFile << "--- First code emmits: " << codes.at(0) << " and outputs: '" << dictionary[oldCode] << "' ---" << std::endl;
    decFile << dictionary[oldCode];
    
    int newVal = 256;

    for(int i = 1; i < codes.size(); i++) {
        std::string currentStr = "";
        currentCode = codes[i];

        //Checking if current code exits in the dictionary
        if (codeInDict(dictionary, currentCode)) {
            //Normal case with str existing in the dictonary
            currentStr +=  dictionary[currentCode];
            logFile << "--- Found known str: '" << currentStr << "' with code: " << currentCode << std::endl;
        }
        else {
            //Exeption case with str not existing in the dictionary
            currentStr += dictionary[oldCode] + dictionary[oldCode][0];
            logFile << "--- Found unknown str: '" << currentStr << "' with code: " << currentCode << std::endl;
        }

        decFile << currentStr;
        
        logFile << "Saving '" << dictionary[oldCode] << currentStr[0] << "' to dictionary with value of: " << newVal << std::endl;
        dictionary[newVal++] = dictionary[oldCode] + currentStr[0];

        oldCode = currentCode;

        std::cout << "\rProgress: " << (i * 100) / codes.size() << "%" << std::flush;
    }
}