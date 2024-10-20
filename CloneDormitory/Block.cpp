#include "Block.h"

Block::Block() : blockNumber(0), residentCount(0), residents() {}

void Block::addResident(const StudentResident& person) {
    residents.push_back(person);
    blockNumber = person.getBlockNumber();
    residentCount++;
}

void Block::printBlockResidents() {
    std::cout << "Блок №" << blockNumber << ":" << std::endl;
    if (residentCount > 0) {
        for (int i = 0; i < residents.size(); i++)
            residents[i].printInfo(1);
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
