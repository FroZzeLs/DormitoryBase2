#pragma once
#include "Logic.h"

class Resident {
protected:
    int blockNumber;
    int studActive; // 0 - �� ��������, 1 - ���������, 2 - ��
    int opt;
    bool debtor;
public:
    Resident(int blockNumber, int studActive, int opt);
    virtual void inputResidentInfo() = 0;
};