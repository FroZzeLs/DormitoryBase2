#include "Logic.h"

int normOfOpt() {
    const int septemberNumber = 8;
    const int julyNumber = 6;
    const int differenceForStartOfYear = 4;

    std::time_t t = std::time(nullptr);
    std::tm currentTime;
    localtime_s(&currentTime, &t);

    int currentMonth = currentTime.tm_mon;
    int monthsSinceSeptember;

    if (currentMonth > septemberNumber)
        monthsSinceSeptember = currentMonth - septemberNumber;
    else if (currentMonth < julyNumber)
        monthsSinceSeptember = currentMonth + differenceForStartOfYear;
    else
        return 0;
    return 4 * monthsSinceSeptember;
}

int inputInteger(int lower, int higher) {
    int number;
    while (true) {
        std::cin >> number;
        if (std::cin.fail() || std::cin.peek() != '\n' || number < lower || number > higher) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Пожалуйста, попробуйте еще раз." << std::endl;
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return number;
        }
    }
}