#pragma once
#include "Block.h"

class Floor {
    friend class Database;
    friend bool checkForOriginality(const std::vector<Floor> floors, const StudentResident& newStudent);
private:
    int floorNumber;
    std::string mentor;
    std::vector<Block> blocks;
public:
    Floor();
    Floor(int blockCount);

    void addResidentToBlock(int blockIndex, const StudentResident& person);

    int getFloorNumber() const;
    std::string getMentor() const;
    std::vector<Block>& getBlocks();

    void setFloorNumber(int floorNumberValue);
    void setMentor(const std::string& Mentor);

    void printBlocksInfo();
};