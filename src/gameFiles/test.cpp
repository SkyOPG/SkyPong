#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream save ("data.txt");
if (!save.is_open()) {
    return 1;
}
std::string line1, line2, line3, line4;
std::getline(save, line1);
std::getline(save, line2);
std::getline(save, line3);
std::getline(save, line4);
save.close();
std::cout << line1 << " " << line2 << " " << line3 << " " << line4;
  return 0;
}