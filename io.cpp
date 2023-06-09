#include <iostream>
#include <fstream>

int main() {
    std::ofstream outputFile("data.txt"); // Create a file for writing
    
    if (outputFile.is_open()) {
        outputFile << "cpu_usage = " << 01 << std::endl; // Write data to the file
        outputFile << "gamecode = " << 42 << std::endl;
        outputFile.close(); // Close the file
    } else {
        std::cout << "Failed to open the file for writing." << std::endl;
        return 1;
    }
    
    std::ifstream inputFile("data.txt"); // Open the file for reading
    
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) { // Read the file line by line
            std::cout << line << std::endl; // Print each line
        }
        inputFile.close(); // Close the file
    } else {
        std::cout << "Failed to open the file for reading." << std::endl;
        return 1;
    }
    
    return 0;
}
