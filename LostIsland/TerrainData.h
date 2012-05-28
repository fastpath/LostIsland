#pragma once
#include "Octree.h"

class TerrainData
{
private:
    Octree* m_pData;
    MemoryPool* m_pPool;
    INT m_size;

public:
    TerrainData(VOID);
    ~TerrainData(VOID);

    VOID Test(VOID);
    BOOL Init(INT p_size);
};

