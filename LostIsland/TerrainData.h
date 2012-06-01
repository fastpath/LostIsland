#pragma once
#include "Octree.h"
#define UNITS_PER_GRID 0.5f

class TerrainData
{
private:
    Octree* m_pData;
    INT m_size;
    FLOAT m_minX;
    FLOAT m_minY;
    FLOAT m_minZ;
    FLOAT m_maxX;
    FLOAT m_maxY;
    FLOAT m_maxZ;

    CHAR Density2Value(FLOAT p_density) CONST;
    FLOAT Value2Density(SHORT p_value) CONST;
    VOID Grid2World(INT p_gridX, INT p_gridY, INT p_gridZ, FLOAT& p_worldX, FLOAT& p_worldY, FLOAT& p_worldZ) CONST;
    VOID World2Grid(FLOAT p_worldX, FLOAT p_worldY, FLOAT p_worldZ, INT& p_gridX, INT& p_gridY, INT& p_gridZ) CONST;

public:
    TerrainData(VOID);
    ~TerrainData(VOID);

    BOOL Init(INT p_size);
    VOID SetDimension(FLOAT p_minX, FLOAT p_minY, FLOAT p_minZ, FLOAT p_maxX, FLOAT p_maxY, FLOAT p_maxZ);
    VOID SetDensity(FLOAT p_worldX, FLOAT p_worldY, FLOAT p_worldZ, FLOAT p_density);
    VOID SaveTerrain(string p_filename) CONST;
    VOID LoadTerrain(string p_filename);

    VOID Test(VOID);
    VOID GenerateTestData(VOID);
};

