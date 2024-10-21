#include "Floor.h"

Floor::Floor() : blocks(17) {}

Floor::Floor(int blockCount) {
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

void Floor::setMentor(std::string_view mentorName) {
    mentor = mentorName;
}

void Floor::printBlocksInfo() {
    bool firstPrint = true;

    for (auto& block : blocks) { // Использование диапазонного цикла for
        if (block.getResidents().empty())
            continue;

        if (firstPrint) {
            std::cout << "Воспитатель " << floorNumber << " этажа: " << mentor << std::endl;
            firstPrint = false;
        }
        block.printBlockResidents();
        std::cout << std::endl;
    }
}

void Floor::sortBlocks() {
    std::sort(blocks.begin(), blocks.end(), [](const Block& a, const Block& b) {
        return a.getBlockNumber() < b.getBlockNumber();
        });
}