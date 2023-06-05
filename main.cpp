#include <iostream>
#include <filesystem>

namespace fs = std::filesystem ;

int main() {
    std::string sourceDirectory = "/home/vlad/Документы/test";
    std::string destinationDirectory = "/home/vlad/Загрузки/test2";
    std::string fileExtension = ".txt";

    fs::create_directories(destinationDirectory);

    int exitCode = 0;

    for (const auto& entry : fs::directory_iterator(sourceDirectory)) {
        const auto& sourcePath = entry.path();
        const auto& destinationPath = destinationDirectory + "/" + sourcePath.filename().string();

        if (sourcePath.extension() == fileExtension) {
            std::error_code errorCode;
            fs::rename(sourcePath, destinationPath, errorCode);

            if (errorCode) {
                std::cout << "Помилка переміщення файлу " << sourcePath << ": " << errorCode.message() << std::endl;
                exitCode = 1;
            } else {
                std::cout << "Файл " << sourcePath << " переміщено до " << destinationPath << std::endl;
            }
        }
    }

    return exitCode;
}
