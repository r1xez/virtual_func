#include <iostream>
#include <fstream>

class FileHandler {
public:
    virtual void Display(const char* path) {
        std::ifstream file(path);
        if (!file) {
            std::cerr << "Unable to open file: " << path << std::endl;
            return;
        }
        std::cout << "File contents:\n";
        char ch;
        while (file.get(ch)) {
            std::cout << ch;
        }
        file.close();
        std::cout << std::endl;
    }

    virtual ~FileHandler() = default;
};


class AsciiFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        std::ifstream file(path);
        if (!file) {
            std::cerr << "Unable to open file: " << path << std::endl;
            return;
        }
        std::cout << "File contents in ASCII codes:\n";
        char ch;
        while (file.get(ch)) {
            std::cout << static_cast<int>(ch) << " ";
        }
        file.close();
        std::cout << std::endl;
    }
};


class BinaryFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        std::ifstream file(path);
        if (!file) {
            std::cerr << "Unable to open file: " << path << std::endl;
            return;
        }
        std::cout << "File contents in binary format:\n";
        char ch;
        while (file.get(ch)) {
            PrintBinary(static_cast<unsigned char>(ch));
            std::cout << " ";
        }
        file.close();
        std::cout << std::endl;
    }

private:
    void PrintBinary(unsigned char ch) {
        for (int i = 7; i >= 0; --i) {
            std::cout << ((ch >> i) & 1);
        }
    }
};


class UpperCaseFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        std::ifstream file(path);
        if (!file) {
            std::cerr << "Unable to open file: " << path << std::endl;
            return;
        }
        std::cout << "File contents in uppercase:\n";
        char ch;
        while (file.get(ch)) {
            std::cout << static_cast<char>(toupper(ch));
        }
        file.close();
        std::cout << std::endl;
    }
};

int main() {
    FileHandler* handler = nullptr;

    std::cout << "Choose display option:\n";
    std::cout << "1. Default display\n";
    std::cout << "2. ASCII codes display\n";
    std::cout << "3. Binary display\n";
    std::cout << "4. Uppercase display\n";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        handler = new FileHandler();
        break;
    case 2:
        handler = new AsciiFileHandler();
        break;
    case 3:
        handler = new BinaryFileHandler();
        break;
    case 4:
        handler = new UpperCaseFileHandler();
        break;
    default:
        std::cerr << "Invalid choice!" << std::endl;
        return 1;
    }

    std::cout << "Enter file path: ";
    std::string path;
    std::cin >> path;

    handler->Display(path.c_str());

    delete handler;
    return 0;
}
