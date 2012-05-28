#include "StdAfx.h"
#include "Terrain.h"

#include "Octree.h"

Terrain::Terrain(void)
{
}


Terrain::~Terrain(void)
{
}


VOID Terrain::Test(VOID)
{
    MemoryPool pool;
    pool.Init(8*sizeof(Octree), 1024*1024, TRUE);
    pool.PrintInfo();

#define TREE_SIZE 256
    Octree tree(0, 0, 0, TREE_SIZE, &pool);
    tree.SetValue(0, 0, 0, 1);
    tree.SetValue(4, 3, 2, 2);

    pool.PrintInfo();
    tree.PrintUsage();

    for(INT x=0; x < TREE_SIZE; ++x) 
    {
        for(INT y=0; y+x < TREE_SIZE; ++y) 
        {
            for(INT z=0; z+y+x < TREE_SIZE; ++z) 
            {
                tree.SetValue(x, y, z, x+y+z);
            }
        }
    }
    pool.PrintInfo();
    tree.PrintUsage();
}