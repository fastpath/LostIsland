#pragma once
#include "MemoryPool.h"
#define DEFAULT_VALUE 0

class Octree
{
private:
    MemoryPool* m_pPool;
    INT m_minX;
    INT m_minY;
    INT m_minZ;
    INT m_size;
    Octree* m_pSons;
    Octree* m_pFather;
    USHORT m_value;

    INT GetSonIndex(INT p_x, INT p_y, INT p_z) CONST;
    BOOL IsIn(INT p_x, INT p_y, INT p_z) CONST;
    VOID CheckSons(VOID);
    VOID SetDimension(INT p_minX, INT p_minY, INT p_minZ, INT p_size) { m_minX = p_minX; m_minY = p_minY; m_minZ = p_minZ; m_size = p_size; }
    VOID Init(Octree *p_pFather) { m_pFather = p_pFather; m_pPool = p_pFather->m_pPool; m_value = p_pFather->m_value; m_pSons = NULL; }

public:
    Octree(INT p_minX, INT p_minY, INT p_minZ, INT p_size, MemoryPool* p_pPool);
    ~Octree(VOID);

    VOID SetValue(INT p_x, INT p_y, INT p_z, INT p_value);
    USHORT GetValue(INT p_x, INT p_y, INT p_z) CONST;
    VOID PrintTree(VOID) CONST;
    UINT GetNumNodes(VOID) CONST;
    UINT GetMaxNumNodes(VOID) CONST;

    INT GetMinX(VOID) CONST { return m_minX; }
    INT GetMinY(VOID) CONST { return m_minY; }
    INT GetMinZ(VOID) CONST { return m_minZ; }
    INT GetMaxX(VOID) CONST { return m_minX + m_size; }
    INT GetMaxY(VOID) CONST { return m_minY + m_size; }
    INT GetMaxZ(VOID) CONST { return m_minZ + m_size; }
    VOID PrintUsage(VOID) CONST { std::cout << "tree usage: " << this->GetNumNodes() << " of " << this->GetMaxNumNodes() << " nodes (" << (UINT)(100.0 * (DOUBLE)this->GetNumNodes() / (DOUBLE)this->GetMaxNumNodes()) << "%)" << std::endl << std::endl;

 }

};

