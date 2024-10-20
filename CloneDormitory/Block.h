#pragma once
#include <vector>
#include <ranges>
#include <algorithm>
#include "StudentResident.h"

class Block {
    friend class Floor;
private:
    int blockNumber;
    int residentCount;
    std::vector<StudentResident> residents;
public:
    Block();

    void printBlockResidents();
    void addResident(const StudentResident& person);
    void deleteResident(const StudentResident& person);

    int getBlockNumber() const;
    int getResidentCount() const;

    void setBlockNumber(int blockNumberValue);
    void setResidentCount(int residentsAmount);

    std::vector<StudentResident>& getResidents();
};