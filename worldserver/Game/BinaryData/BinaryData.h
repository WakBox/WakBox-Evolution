#ifndef BINARYDATA_H
#define BINARYDATA_H

#include "Utils/Singleton.h"
#include "BinaryDataStructure.h"

class BinaryDataMgr : public Singleton<BinaryDataMgr>
{
public:
    BinaryDataMgr();
    ~BinaryDataMgr();
private:

};

#endif // BINARYDATA_H
