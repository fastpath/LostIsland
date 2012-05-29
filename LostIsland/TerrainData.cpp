#include "StdAfx.h"
#include "TerrainData.h"

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
        m_pData = new Octree(0, 0, 0, p_size, m_pPool);
        m_size = p_size;
        this->SetDimension(-0.5f * UNITS_PER_GRID * (FLOAT)p_size,
                           -0.5f * UNITS_PER_GRID * (FLOAT)p_size,
                           -0.5f * UNITS_PER_GRID * (FLOAT)p_size,
                           +0.5f * UNITS_PER_GRID * (FLOAT)p_size,
                           +0.5f * UNITS_PER_GRID * (FLOAT)p_size,
                           +0.5f * UNITS_PER_GRID * (FLOAT)p_size);
        return TRUE;
    }
}


VOID TerrainData::Test(VOID)
{
    std::cout << "generating " << m_size << "^3 octree..." << std::endl;
    INT id = g_timer.Tick(IMMEDIATE);

    FLOAT worldX = m_minX;
    FLOAT dx = (m_maxX - m_minX) / (FLOAT)m_size;
    for(INT x=0; x < m_size; ++x) 
    {
        FLOAT worldY = m_minY;
        FLOAT dy = (m_maxY - m_minY) / (FLOAT)m_size;
        for(INT y=0; y < m_size; ++y) 
        {
            FLOAT worldZ = m_minZ;
            FLOAT dz = (m_maxZ - m_minZ) / (FLOAT)m_size;
            for(INT z=0; z < m_size; ++z) 
            {
                FLOAT density = worldY - sin(worldX)*cos(worldZ);
                this->SetDensity(worldX, worldY, worldZ, density);
                worldZ += dz;
            }
            worldY += dy;
        }
        worldX += dx;
    }

    std::cout << "generation took " << (1e-3 * (DOUBLE)g_timer.Tock(id, ERASE)) << " secs" << std::endl << std::endl;

    m_pPool->PrintInfo();
    m_pData->PrintUsage();

    //m_pData->PrintTree();
}


VOID TerrainData::SetDimension(FLOAT p_minX, FLOAT p_minY, FLOAT p_minZ, FLOAT p_maxX, FLOAT p_maxY, FLOAT p_maxZ)
{
    m_minX = p_minX;
    m_minY = p_minY;
    m_minZ = p_minZ;
    m_maxX = p_maxX;
    m_maxY = p_maxY;
    m_maxZ = p_maxZ;
}


SHORT TerrainData::Density2Value(FLOAT p_density) CONST
{
    p_density = 1.0f + CLAMP(p_density, -1.0f, +1.0f);
    return (SHORT)MIX((FLOAT)SHORT_MIN, (FLOAT)SHORT_MAX, 0.5f*p_density);
}


FLOAT TerrainData::Value2Density(SHORT p_value) CONST
{
    return 2.0f * LERP(p_value, (FLOAT)SHORT_MIN, (FLOAT)SHORT_MAX) - 1.0f;
}


VOID TerrainData::SetDensity(FLOAT p_worldX, FLOAT p_worldY, FLOAT p_worldZ, FLOAT p_density)
{
    INT x, y, z;
    this->World2Grid(p_worldX, p_worldY, p_worldZ, x, y, z);
    m_pData->SetValue(x, y, z, this->Density2Value(p_density));
}


VOID TerrainData::Grid2World(INT p_gridX, INT p_gridY, INT p_gridZ, FLOAT& p_worldX, FLOAT& p_worldY, FLOAT& p_worldZ) CONST
{
    p_worldX = m_minX + (m_maxX - m_minX) * LERP((FLOAT)p_gridX, 0.0f, (FLOAT)m_size);
    p_worldY = m_minY + (m_maxY - m_minY) * LERP((FLOAT)p_gridY, 0.0f, (FLOAT)m_size);
    p_worldZ = m_minZ + (m_maxZ - m_minZ) * LERP((FLOAT)p_gridZ, 0.0f, (FLOAT)m_size);
}


VOID TerrainData::World2Grid(FLOAT p_worldX, FLOAT p_worldY, FLOAT p_worldZ, INT& p_gridX, INT& p_gridY, INT& p_gridZ) CONST
{
    p_gridX = (INT)((FLOAT)m_size * LERP(p_worldX, m_minX, m_maxX));
    p_gridY = (INT)((FLOAT)m_size * LERP(p_worldY, m_minY, m_maxY));
    p_gridZ = (INT)((FLOAT)m_size * LERP(p_worldZ, m_minZ, m_maxZ));
}