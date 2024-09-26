#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

namespace Task1 {
    class OutOfRangeException : public std::runtime_error {
    public:
        OutOfRangeException(const std::string& message) : std::runtime_error(message) {}
    };

    int getRandomNumber(int N, int M) { //  Если N больше или равно M, то функция бросает исключение OutOfRangeException.
        if (N >= M) {
            throw OutOfRangeException("N must be less than M");
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(N, M - 1);

        return dis(gen);
    }
}

namespace Task2 {
    class InvalidInputException : public std::invalid_argument {
    public:
        InvalidInputException(const std::string& message) : std::invalid_argument(message) {}
    };

    bool validateStringFormat(const std::string& input) { //Функция validateStringFormat принимает строку в формате "слово длина_слова" и возвращает true, если длина слова действительно равна длине, указанной в строке. Если строка введена в неверном формате, функция бросает исключение InvalidInputException.
        // Разбиваем строку на слово и длину
        size_t spacePos = input.find(' ');
        if (spacePos == std::string::npos) {
            throw InvalidInputException("Input string must be in the format 'word length'");
        }

        std::string word = input.substr(0, spacePos);
        std::string lengthStr = input.substr(spacePos + 1);

        // Проверяем, что длина слова соответствует заданной
        size_t wordLength = word.length();
        size_t length;
        try {
            length = std::stoi(lengthStr);
        }
        catch (const std::invalid_argument&) {
            throw InvalidInputException("Length must be a valid integer");
        }

        return wordLength == length;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    try {
        int randomNumber = Task1::getRandomNumber(10, 20);
        std::cout << "Random number: " << randomNumber << std::endl;
    }
    catch (const Task1::OutOfRangeException & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        if (Task2::validateStringFormat("hello 5")) {
            std::cout << "Valid format" << std::endl;
        }
        else {
            std::cout << "Invalid format" << std::endl;
        }

        if (Task2::validateStringFormat("world 10")) {
            std::cout << "Valid format" << std::endl;
        }
        else {
            std::cout << "Invalid format" << std::endl;
        }

        Task2::validateStringFormat("hello world");
    }
    catch (const Task2::InvalidInputException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}