#include "Block.h"

void Block::addResident(const StudentResident& person) {
    residents.push_back(person);
    blockNumber = person.getBlockNumber();
    residentCount++;
}

void Block::printBlockResidents() const {
    std::cout << "\nÁëîê ¹" << blockNumber << ":" << std::endl;
    if (residentCount > 0) {
        for (const auto& resident : residents) {
            resident.printInfo(1);
        }
    }
}

int Block::getBlockNumber() const {
    return blockNumber;
}

int Block::getResidentCount() const {
    return residentCount;
}

void Block::setBlockNumber(int blockNumberValue) {
    blockNumber = blockNumberValue;
}

void Block::setResidentCount(int residentsAmount) {
    residentCount = residentsAmount;
}

std::vector<StudentResident>& Block::getResidents() {
    return residents;
}

void Block::deleteResident(const StudentResident& person) {
    for (int i = 0; i < residents.size(); i++) {
        if (residents[i] == person) {
            residents.erase(residents.begin() + i);
            return;
        }
   }
}
