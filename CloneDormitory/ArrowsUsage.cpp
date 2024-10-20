#include "ArrowsUsage.h"

void handleKeyPress(int& value, int maxIndex, int lastNotEmptyFloor) {
    bool error = false;
    do {
        char key = _getch();

        if (key == 0 || key == -32) {
            key = _getch();
        }

        switch (key) {
        case 77: // Стрелка вправо
            if (value < maxIndex) {
                value += 1;
            }
            else if (value == maxIndex) {
                error = true;
                break;
            }
            error = false;
            break;
        case 75: // Стрелка влево
            if (value > 0 && value != maxIndex) {
                value -= 1;
            }
            else if (value == maxIndex) {
                value = lastNotEmptyFloor;
            }
            else if (value == 0) {
                error = true;
                break;
            }
            error = false;
            break;
        case 13: // Клавиша Enter
            value = -1;
            error = false;
            break;
        default:
            error = true;
            break;
        }
    } while (error);
}
