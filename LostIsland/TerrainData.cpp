#include "StdAfx.h"
#include "TerrainData.h"

#include "Octree.h"

TerrainData::TerrainData(VOID):
m_pData(NULL), m_pPool(NULL), m_size(0)
{
}


TerrainData::~TerrainData(void)
{
    SAFE_DELETE(m_pData);
    SAFE_DELETE(m_pPool);
}


BOOL TerrainData::Init(INT p_size)
{
    m_pPool = new MemoryPool();
    BOOL result = m_pPool->Init(8*sizeof(Octree), p_size*p_size, TRUE);
    if(!result)
    {
        SAFE_DELETE(m_pPool);
        return FALSE;
    }
    else
    {
        std::cout << p_size << std::endl;
        m_pData = new Octree(0, 0, 0, p_size, m_pPool);
        m_size = p_size;
        return TRUE;
    }
}


VOID TerrainData::Test(VOID)
{
    m_pPool->PrintInfo();
    m_pData->PrintUsage();

    m_pData->SetValue(0, 0, 0, 1);
    m_pData->SetValue(4, 3, 2, 2);

    m_pPool->PrintInfo();
    m_pData->PrintUsage();

    for(INT x=0; x < m_size; ++x) 
    {
        for(INT y=0; y+x < m_size; ++y) 
        {
            for(INT z=0; z+y+x < m_size; ++z) 
            {
                m_pData->SetValue(x, y, z, x+y+z);
            }
        }
    }

    m_pPool->PrintInfo();
    m_pData->PrintUsage();
}