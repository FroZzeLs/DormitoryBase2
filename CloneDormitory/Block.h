#pragma once
#include <vector>
#include <ranges>
#include <algorithm>
#include "StudentResident.h"

class Block {
    friend class Floor;
private:
    int blockNumber = 0;
    int residentCount = 0;
    std::vector<StudentResident> residents;
public:
    Block() = default;

    void printBlockResidents() const;
    void addResident(const StudentResident& person);
    void deleteResident(const StudentResident& person);

    int getBlockNumber() const;
    int getResidentCount() const;

    void setBlockNumber(int blockNumberValue);
    void setResidentCount(int residentsAmount);

    std::vector<StudentResident>& getResidents();
};