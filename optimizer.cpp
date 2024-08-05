#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <openssl/sha.h>  // For hashing, you need OpenSSL or another library>

namespace fs = std::filesystem;

// Function to compute SHA-256 hash of a file
std::string computeFileHash(const fs::path& filePath)
{
    constexpr size_t bufferSize = 8192;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    std::ifstream file(filePath, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + filePath.string());
    }

    char buffer[bufferSize];
    while (file.read(buffer, bufferSize))
    {
        SHA256_Update(&sha256, buffer, file.gcount());
    }
    SHA256_Update(&sha256, buffer, file.gcount());
    SHA256_Final(hash, &sha256);

    // Convert hash to hex string
    std::string hashString;
    hashString.reserve(SHA256_DIGEST_LENGTH * 2); // Reserve space to avoid reallocations
    for (unsigned char byte : hash)
    {
        char buf[3];
        snprintf(buf, sizeof(buf), "%02x", byte);
        hashString += buf;
    }

    return hashString;
}

// Function to filter, delete duplicate images, and generate a report
void deleteDuplicateImages(const fs::path& directoryPath, const fs::path& reportFilePath)
{
    std::unordered_map<std::string, fs::path> fileHashes;
    std::ofstream reportFile(reportFilePath);

    if (!reportFile)
    {
        throw std::runtime_error("Failed to open report file: " + reportFilePath.string());
    }

    for (const auto& entry : fs::directory_iterator(directoryPath))
    {
        if (entry.is_regular_file())
        {
            auto filePath = entry.path();
            auto extension = filePath.extension().string();

            // Simple image file extensions filter
            if (extension == ".jpg" || extension == ".png" || extension == ".bmp" || extension == ".gif")
            {
                try
                {
                    std::string fileHash = computeFileHash(filePath);
                    auto result = fileHashes.emplace(fileHash, filePath);

                    if (!result.second)
                    {
                        // Duplicate found, delete the file
                        std::cout << "Deleting duplicate file: " << filePath << std::endl;
                        reportFile << result.first->second.filename().string() << ":" << filePath.filename().string() << std::endl;
                        fs::remove(filePath);
                    }
                }
                catch (const std::exception& e)
                {
                    std::cerr << "Error processing file " << filePath << ": " << e.what() << std::endl;
                }
            }
        }
    }
}

int main()
{
    fs::path directoryPath = "/home/sky/Projects/SkyPong2/idk"; // Specify your directory path here
    fs::path reportFilePath = "duplicates_report.txt"; // Specify the report file path here

    try
    {
        deleteDuplicateImages(directoryPath, reportFilePath);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
