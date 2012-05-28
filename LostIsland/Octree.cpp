#include "StdAfx.h"
#include "Octree.h"


Octree::Octree(INT p_minX, INT p_minY, INT p_minZ, INT p_size, MemoryPool* p_pPool):
m_pFather(NULL), m_pSons(NULL), m_pPool(p_pPool), m_value(DEFAULT_VALUE)
{
    this->SetDimension(p_minX, p_minY, p_minZ, p_size);
}


Octree::~Octree(VOID)
{
    if(m_pSons != NULL) {
        m_pPool->Free(m_pSons);
    }
}


VOID Octree::SetValue(INT p_x, INT p_y, INT p_z, INT p_value)
{
    if(m_size == 1)
    {
        m_value = p_value;
    }
    else
    {
        if(m_pSons == NULL)
        {
            if(p_value != m_value)
            {
                m_pSons = (Octree*)m_pPool->Alloc();
                for(INT i=0; i < 8; ++i)
                {
                    m_pSons[i].Init(this);
                    m_pSons[i].SetDimension(m_minX + (i % 2) * m_size/2,
                                            m_minY + ((i >> 1) % 2) * m_size/2,
                                            m_minZ + ((i >> 2) % 2) * m_size/2,
                                            m_size/2);
                }
            }
            else 
            {
                return;
            }
        }
        INT index = this->GetSonIndex(p_x, p_y, p_z);
        m_pSons[index].SetValue(p_x, p_y, p_z, p_value);
    }
    if(m_pSons != NULL)
    {
        this->CheckSons();
    }
    if(m_pSons == NULL && m_pFather != NULL)
    {
        m_pFather->CheckSons();
    }
}


USHORT Octree::GetValue(INT p_x, INT p_y, INT p_z) CONST
{
    if(m_pSons == NULL)
    {
        return m_value;
    }
    else
    {
        INT index = this->GetSonIndex(p_x, p_y, p_z);
        return m_pSons[index].GetValue(p_x, p_y, p_z);
    }
}


VOID Octree::CheckSons(VOID)
{
    if(m_pSons != NULL)
    {
        m_value = m_pSons[0].m_value;
        BOOL collapsable = TRUE;
        for(INT i=0; collapsable && i < 8; ++i) 
        {
            if(m_pSons[i].m_pSons != NULL || m_pSons[i].m_value != m_value)
            {
                collapsable = FALSE;
            }
        }
        if(collapsable)
        {
            m_pPool->Free(m_pSons);
            m_pSons = NULL;
        }
    }
}


INT Octree::GetSonIndex(INT p_x, INT p_y, INT p_z) CONST
{
    INT index = 0;
#ifdef _DEBUG
    if(!this->IsIn(p_x, p_y, p_z))
    {
        ERROR("called GetSonIndex() but position is not in tree");
        return -1;
    }
#endif
    index |= p_x >= (m_minX + m_size/2) ? 1 : 0;
    index |= p_y >= (m_minY + m_size/2) ? 2 : 0;
    index |= p_z >= (m_minZ + m_size/2) ? 4 : 0;
    return index;
}


BOOL Octree::IsIn(INT p_x, INT p_y, INT p_z) CONST
{
    return m_minX <= p_x && p_x < m_minX + m_size &&
           m_minY <= p_y && p_y < m_minY + m_size &&
           m_minZ <= p_z && p_z < m_minZ + m_size;
}


VOID Octree::PrintTree(VOID) CONST
{
    for(INT z=0; z < m_size; ++z) 
    {
        std::cout << "z=" << (m_minZ + z) << std::endl;
        for(INT y=0; y < m_size; ++y) 
        {
            for(INT x=0; x < m_size; ++x) 
            {
                std::cout << this->GetValue(m_minX + x, m_minY + y, m_minZ + z) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}


UINT Octree::GetNumNodes(VOID) CONST
{
    if(m_pSons == NULL)
    {
        return 1;
    }
    else 
    {
        return 1 + m_pSons[0].GetNumNodes()
                 + m_pSons[1].GetNumNodes()
                 + m_pSons[2].GetNumNodes()
                 + m_pSons[3].GetNumNodes()
                 + m_pSons[4].GetNumNodes()
                 + m_pSons[5].GetNumNodes()
                 + m_pSons[6].GetNumNodes()
                 + m_pSons[7].GetNumNodes();
    }
}


UINT Octree::GetMaxNumNodes(VOID) CONST
{
    UINT n = 0;
    UINT size = m_size;
    while(size > 1)
    {
        size >>= 1;
        ++n;
    }
    return ((1 << (3 * (n + 1))) - 1) / 7;
}
