#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <openssl/bio.h>
#include <openssl/evp.h>

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
void ReplaceLineInFile(const string& filename, int lineNumber, const string& newContent) {
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

std::string Base64Encode(const std::string& input) {
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* mem = BIO_new(BIO_s_mem());
    BIO_push(b64, mem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, input.c_str(), input.length());
    BIO_flush(b64);
    BUF_MEM* mem_buf;
    BIO_get_mem_ptr(b64, &mem_buf);
    std::string encoded_data(mem_buf->data, mem_buf->length);
    BIO_free_all(b64);
    return encoded_data;
}

std::string Base64Decode(const std::string& input) {
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* mem = BIO_new_mem_buf(input.c_str(), input.length());
    BIO_push(b64, mem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    char* buffer = new char[input.length()];
    int decoded_length = BIO_read(b64, buffer, input.length());
    std::string decoded_data(buffer, decoded_length);
    delete[] buffer;
    BIO_free_all(b64);
    return decoded_data;
}

int main() {
    std::string input = "Hello, World!";
    std::string encoded = Base64Encode(input);
    std::cout << "Encoded: " << encoded << std::endl;
    std::string decoded = Base64Decode(encoded);
    std::cout << "Decoded: " << decoded << std::endl;
    return 0;
}
