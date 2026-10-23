#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <limits>
#include "lzw.h"
#include "lzwDec.h"

int main(void) {
    
    std::string text = "";
    int choice = 0;

    while (true) {

        // Display menu and current state of the text variable
        std::cout << "\n====================================" << std::endl;
        std::cout << "Current string length: " << text.length() << " characters" << std::endl;
        std::cout << "====================================" << std::endl;
        std::cout << "1. Enter custom text from keyboard" << std::endl;
        std::cout << "2. Load text from a .txt file" << std::endl;
        std::cout << "3. Clear current text" << std::endl;
        std::cout << "4. Run Compression Algorithm" << std::endl;
        std::cout << "5. Run Decompression Algorithm" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Select an option (1-6): ";

        if (!(std::cin >> choice)) {
            // Handle non-integer input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
            continue;
        }

        // Clear the buffer newline before using std::getline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "Enter your text: ";
            std::getline(std::cin, text);
            std::cout << "Text updated successfully!" << std::endl;

        } else if (choice == 2) {
            std::string filePath;
            std::cout << "Enter the path to your .txt file: ";
            std::getline(std::cin, filePath);

            std::ifstream inFile(filePath);
            if (inFile.is_open()) {
                // Read the entire file into the 'text' variable at once
                text = std::string((std::istreambuf_iterator<char>(inFile)),
                                    std::istreambuf_iterator<char>());
                inFile.close();
                std::cout << "File loaded successfully! (" << text.length() << " bytes read)" << std::endl;
            } else {
                std::cout << "Error: Could not open file at path '" << filePath << "'" << std::endl;
            }
        }
        else if (choice == 3) {
            text.clear();
            std::cout << "Text variable has been cleared." << std::endl;
        } 
        else if (choice == 4) {
            lempelZiv(text);
        } 
        else if (choice == 5) {
            lzwDecompression();
        }
        else if (choice == 6) {
            std::cout << "Exiting program. Goodbye!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid choice! Please select 1, 2, 3, 4, 5 or 6." << std::endl;
        }
    }

    return 0;
}