#include "Resident.h"

Resident::Resident(int blockNumber, int studActive, int opt)
    : blockNumber(blockNumber), studActive(studActive), opt(opt) 
{debtor = opt < normOfOpt() ? true : false;}
