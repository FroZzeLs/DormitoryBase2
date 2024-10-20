#include "Floor.h"

Floor::Floor() : floorNumber(0), mentor(""), blocks(17) {}

Floor::Floor(int blockCount) : floorNumber(0), mentor("") {
    blocks.resize(blockCount);
}

void Floor::addResidentToBlock(int blockIndex, const StudentResident& person) {

    blocks[blockIndex].addResident(person);
    floorNumber = person.getBlockNumber() / 100;
}

int Floor::getFloorNumber() const {
    return floorNumber;
}

std::vector<Block>& Floor::getBlocks(){
    return blocks;
}

void Floor::setFloorNumber(int floorNumberValue) {
    floorNumber = floorNumberValue;
}

void Floor::setMentor(const std::string& mentorName) {
    mentor = mentorName;
}

void Floor::printBlocksInfo(){
    bool firstPrint = true;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i].getResidents().empty())
            continue;
        if (firstPrint) {
            std::cout << "Воспитатель " << floorNumber << " этажа: " << mentor << std::endl;
            firstPrint = false;
        }
        blocks[i].printBlockResidents();
        std::cout << std::endl;
    }
}