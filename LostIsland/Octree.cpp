#include "StdAfx.h"
#include "Octree.h"


MemoryPool Octree::sm_pool;


Octree::Octree(VOID):
m_pFather(NULL), m_pSons(NULL), m_value(DEFAULT_VALUE), m_minX(0), m_minY(0), m_minZ(0), m_size(0)
{
}


Octree::~Octree(VOID)
{
    if(m_pSons != NULL) {
        sm_pool.Free(m_pSons);
    }
}


VOID Octree::SetValue(INT p_x, INT p_y, INT p_z, CHAR p_value)
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
                m_pSons = (Octree*)sm_pool.Alloc();
                for(INT i=0; i < 8; ++i)
                {
                    m_pSons[i].Init(this, i);
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


CHAR Octree::GetValue(INT p_x, INT p_y, INT p_z) CONST
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
            sm_pool.Free(m_pSons);
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
        //ERROR("called GetSonIndex() but position is not in tree");
        std::cerr << "error1: " << m_minX << " " << m_minY << " " << m_minZ << " " << m_size << std::endl;
        std::cerr << "error2: " << p_x << " " << p_y << " " << p_z << " " << std::endl;
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
    std::cout << "Octree size: " << m_size << std::endl;
    for(INT y=0; y < m_size; ++y) 
    {
        std::cout << "y=" << (m_minY + y) << std::endl;
        for(INT z=0; z < m_size; ++z) 
        {
            for(INT x=0; x < m_size; ++x) 
            {
                std::cout << (INT)this->GetValue(m_minX + x, m_minY + y, m_minZ + z) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}


ULONG Octree::GetNumNodes(VOID) CONST
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


ULONG Octree::GetMaxNumNodes(VOID) CONST
{
    ULONG sum = 0;
    ULONG start = 1;
    INT size = m_size;
    while(size > 0)
    {
        sum += start;
        start *= 8;
        size /= 2;
    }
    return sum;
}


VOID Octree::Init(INT p_size)
{
    m_size = p_size;
    m_minX = m_minY = m_minZ = 0;
    m_value = DEFAULT_VALUE;
    m_flags = 0;
    m_pFather = NULL;
    m_pSons = NULL;
}


VOID Octree::Init(Octree *p_pFather, INT p_sonIndex)
{
    //std::cout << p_pFather->m_minX << " " << p_pFather->m_minY << " " << p_pFather->m_minZ << " " << p_pFather->m_size << std::endl;
    m_pFather = p_pFather;
    m_size = p_pFather->m_size/2;
    m_value = p_pFather->m_value;
    m_minX = p_pFather->m_minX + (p_sonIndex % 2) * m_size;
    m_minY = p_pFather->m_minY + ((p_sonIndex >> 1) % 2) * m_size;
    m_minZ = p_pFather->m_minZ + ((p_sonIndex >> 2) % 2) * m_size;
    m_pSons = NULL;
    
}


BOOL Octree::Init(std::fstream& p_stream)
{
    using std::fstream;
    using std::ios;

    INT size;
    p_stream.seekg(0, ios::beg);
    p_stream.read((CHAR*)&size, sizeof(INT));
    
    this->Init(size);
    BOOL result;
#ifdef _DEBUG
    std::cout << "loading octree..." << std::endl;
    INT id = g_timer.Tick(IMMEDIATE);
    result = this->InitIntern(p_stream);
    std::cout << "loading took " << (1e-3 * (DOUBLE)g_timer.Tock(id, ERASE)) << " secs" << std::endl;
#else
    result = this->InitIntern(p_stream);
#endif
    return result;
}


#define NODE_FILE_NODESIZE (2 * sizeof(CHAR) + 8 * sizeof(INT))
#define NODE_FILE_OFFSET sizeof(INT)


BOOL Octree::InitIntern(std::fstream& p_stream)
{
    using std::fstream;
    using std::ios;
    using std::streampos;
    if(!p_stream.good())
    {
        //return FALSE;
    }

    INT pSons[8];
    p_stream.read(&m_value, sizeof(CHAR));
    p_stream.read(&m_flags, sizeof(CHAR));
    p_stream.read((CHAR*)pSons, 8 * sizeof(INT));

    BOOL error = FALSE;
    if(pSons[0] != 0)
    {
        m_pSons = (Octree*)sm_pool.Alloc();
        for(INT i=0; i < 8 && !error; ++i)
        {
            m_pSons[i].Init(this, i);
            p_stream.seekg(NODE_FILE_OFFSET + pSons[i] * NODE_FILE_NODESIZE, ios::beg);
            error = !m_pSons[i].InitIntern(p_stream);
        }
    }
    if(error)
    {
        std::cout << "ERROR!!!" << std::endl;
        sm_pool.Free(m_pSons);
        m_pSons = NULL;
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}


static INT g_currentNode = 0;


VOID Octree::Save(std::fstream& p_stream) CONST
{
    g_currentNode = 0;

    using std::fstream;
    using std::ios;

    p_stream.seekp(0, ios::beg);
    p_stream.write((CHAR*)&m_size, sizeof(INT));

#ifdef _DEBUG
    std::cout << "saving octree..." << std::endl;
    INT id = g_timer.Tick(IMMEDIATE);
    this->SaveIntern(p_stream);
    std::cout << "saving took " << (1e-3 * (DOUBLE)g_timer.Tock(id, ERASE)) << " secs" << std::endl;
#else
    this->SaveIntern(p_stream);
#endif
    
}


VOID Octree::SaveIntern(std::fstream& p_stream) CONST
{
    INT thisNodeNr = g_currentNode++;

    INT pSonPointers[8] = { 0,0,0,0,0,0,0,0 };
    p_stream.seekp(NODE_FILE_OFFSET + thisNodeNr * NODE_FILE_NODESIZE, std::ios::beg);
    p_stream.write(&m_value, sizeof(CHAR));
    p_stream.write(&m_flags, sizeof(CHAR));
    p_stream.write((CHAR*)pSonPointers, 8 * sizeof(INT));
    
    if(m_pSons != NULL)
    {
        for(INT i=0; i < 8; ++i)
        {
            pSonPointers[i] = g_currentNode;
            m_pSons[i].SaveIntern(p_stream);
        }

        p_stream.seekp(NODE_FILE_OFFSET + thisNodeNr * NODE_FILE_NODESIZE + 2 * sizeof(CHAR), std::ios::beg);
        p_stream.write((CHAR*)pSonPointers, 8 * sizeof(INT));
    }
}
