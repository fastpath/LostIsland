#pragma once
#include "MemoryPool.h"
#include <iostream>
#include <fstream>
#define DEFAULT_VALUE 0

class Octree
{
private:
    static MemoryPool sm_pool;

    INT m_minX;
    INT m_minY;
    INT m_minZ;
    INT m_size;
    Octree* m_pSons;
    Octree* m_pFather;
    CHAR m_value;
    CHAR m_flags;
    //INT m_filePointer;

    INT GetSonIndex(INT p_x, INT p_y, INT p_z) CONST;
    BOOL IsIn(INT p_x, INT p_y, INT p_z) CONST;
    VOID CheckSons(VOID);
    VOID Init(Octree *p_pFather, INT p_sonIndex);
    BOOL InitIntern(std::fstream& p_stream);
    VOID SaveIntern(std::fstream& p_stream) CONST;

public:
    Octree(VOID);
    ~Octree(VOID);

    VOID Init(INT p_size);
    BOOL Init(std::fstream& p_stream);
    VOID Save(std::fstream& p_stream) CONST;
    VOID SetValue(INT p_x, INT p_y, INT p_z, CHAR p_value);
    CHAR GetValue(INT p_x, INT p_y, INT p_z) CONST;
    VOID PrintTree(VOID) CONST;
    ULONG GetNumNodes(VOID) CONST;
    ULONG GetMaxNumNodes(VOID) CONST;
    
    INT GetMinX(VOID) CONST { return m_minX; }
    INT GetMinY(VOID) CONST { return m_minY; }
    INT GetMinZ(VOID) CONST { return m_minZ; }
    INT GetMaxX(VOID) CONST { return m_minX + m_size; }
    INT GetMaxY(VOID) CONST { return m_minY + m_size; }
    INT GetMaxZ(VOID) CONST { return m_minZ + m_size; }
    VOID PrintUsage(VOID) CONST { std::cout << "tree usage: " << this->GetNumNodes() << " of " << this->GetMaxNumNodes() << " nodes (" << (UINT)(100.0 * (DOUBLE)this->GetNumNodes() / (DOUBLE)this->GetMaxNumNodes()) << "%)" << std::endl << std::endl; }

    static BOOL InitMemoryPool(INT p_numChunks) { return sm_pool.Init(8*sizeof(Octree), p_numChunks, TRUE); }
    static MemoryPool& GetMemoryPool(VOID) { return sm_pool; }
};

