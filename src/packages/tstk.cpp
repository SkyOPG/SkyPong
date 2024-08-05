#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string ReadLineFromFile(const string& filename, int lineNumber) {
    ifstream file(filename);
    string line;
    int currentLineNumber = 0;

    while (getline(file, line)) {
        currentLineNumber++;
        if (currentLineNumber == lineNumber) {
            file.close();
            return line;
        }
    }
    if (!line.empty()) {
        cout << "there is nothing here moment" << endl;
    }

    file.close();
    return "";
}
void ReplaceLineInFile(const string& filename, unsigned int lineNumber, const string& newContent) {
    ifstream inputFile(filename);
    vector<string> lines;
    string line;

    while (getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    if (lineNumber <= 0 || lineNumber > lines.size()) {
        cout << "Invalid line number." << endl;
        return;
    }

    lines[lineNumber - 1] = newContent;

    ofstream outputFile(filename);
    for (const string& updatedLine : lines) {
        outputFile << updatedLine << endl;
    }

    outputFile.close();

    std::cout << "Line " << lineNumber << " replaced successfully." << std::endl;
}