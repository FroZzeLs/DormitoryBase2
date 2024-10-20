#pragma once
#include "Block.h"

class Floor {
    friend class Database;
    friend bool checkForOriginality(std::vector<Floor>& floors, const StudentResident& newStudent);
private:
    int floorNumber = 0;
    std::string mentor = "";
    std::vector<Block> blocks;
public:
    Floor();
    explicit Floor(int blockCount);

    void addResidentToBlock(int blockIndex, const StudentResident& person);

    int getFloorNumber() const;
    std::string getMentor() const;
    std::vector<Block>& getBlocks();

    void setFloorNumber(int floorNumberValue);
    void setMentor(std::string_view Mentor);

    void printBlocksInfo();
};