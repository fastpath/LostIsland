#include "StdAfx.h"
#include "MemoryPool.h"


CONST SIZE_T MemoryPool::CHUNK_HEADER_SIZE = sizeof(UCHAR*);


MemoryPool::MemoryPool(VOID):
m_ppRawMemArray(NULL), m_memArraySize(0), m_pHead(NULL), m_allocated(0)
{
}


MemoryPool::~MemoryPool(VOID)
{
    for(UINT i=0; i < m_memArraySize; ++i) {
        delete[] m_ppRawMemArray[i];
    }
    delete[] m_ppRawMemArray;
}


BOOL MemoryPool::Init(INT p_chunkSize, INT p_numChunks, BOOL p_resizable)
{
    m_chunkSize = p_chunkSize;
    m_numChunks = p_numChunks;
    m_resizable = p_resizable;
    return this->GrowMemory();
}


BOOL MemoryPool::GrowMemory(VOID)
{
    UCHAR** ppMemArray = new UCHAR*[m_memArraySize+1];
    for(UINT i=0; i < m_memArraySize; ++i)
    {
        ppMemArray[i] = m_ppRawMemArray[i];
    }
    ppMemArray[m_memArraySize] = this->CreateNewMemoryBlock();

    if(m_pHead != NULL)
    {
        UCHAR* pCurrent = m_pHead;
        UCHAR* pNext = this->GetNext(pCurrent);
        while(pNext != NULL) {
            pCurrent = pNext;
            pNext = this->GetNext(pCurrent);
        }
        this->SetNext(pCurrent, ppMemArray[m_memArraySize]);
    }
    else
    {
        m_pHead = ppMemArray[m_memArraySize];
    }

    ++m_memArraySize;
    delete[] m_ppRawMemArray;
    m_ppRawMemArray = ppMemArray;
    return TRUE;
}


UCHAR* MemoryPool::CreateNewMemoryBlock(VOID)
{
    size_t blockSize = CHUNK_HEADER_SIZE + m_chunkSize;
    size_t memBlockSize = m_numChunks * blockSize;

    UCHAR* pMemBlock = new UCHAR[memBlockSize];
    UCHAR* pCurrent = pMemBlock;
    UCHAR* pEnd = pMemBlock + memBlockSize;
    while(pCurrent < pEnd)
    {
        UCHAR* pNext = pCurrent + blockSize;
        UCHAR** pChunkHeader = (UCHAR**)pCurrent;
        pChunkHeader[0] = (pNext < pEnd ? pNext : NULL);
        pCurrent += blockSize;
    }
    return pMemBlock;
}


UCHAR* MemoryPool::GetNext(UCHAR* p_pBlock) CONST
{
    UCHAR** pChunkHeader = (UCHAR**)p_pBlock;
    return pChunkHeader[0];
}


VOID MemoryPool::SetNext(UCHAR* p_pBlock, UCHAR* p_pNext)
{
    UCHAR** pChunkHeader = (UCHAR**)p_pBlock;
    pChunkHeader[0] = p_pNext;
}


VOID* MemoryPool::Alloc(VOID)
{
    if(m_pHead == NULL) 
    {
        if(m_resizable)
        {
            this->GrowMemory();
        }
        else
        {
            return NULL;
        }
    }
    ++m_allocated;
    UCHAR* pMem = m_pHead;
    m_pHead = this->GetNext(pMem);
    return pMem + CHUNK_HEADER_SIZE;
}


VOID MemoryPool::Free(VOID* p_pMem)
{
    if(p_pMem == NULL)
    {
        return;
    }
    UCHAR* pOldHead = m_pHead;
    m_pHead = (UCHAR*)p_pMem - CHUNK_HEADER_SIZE;
    this->SetNext(m_pHead, pOldHead);
    --m_allocated;
}


VOID MemoryPool::PrintInfo(VOID) CONST
{

    std::cout << "chunk size: " << FormatBytes(this->GetChunkSize()) << std::endl
              << "system memory used: " << FormatBytes(this->GetSystemAllocatedBytes()) << std::endl
              << "pool memory used: " << FormatBytes(this->GetPoolAllocatedBytes()) << std::endl
              << "pool memory free: " << FormatBytes(this->GetPoolFreeBytes()) << std::endl
              << "usage of allocated system memory: " << (UINT)(100.0 * this->GetPoolUsage()) << "%" << std::endl << std::endl;
}


#include <sstream>
string MemoryPool::FormatBytes(SIZE_T p_bytes)
{
    INT unit = 0;
    while(p_bytes > 4096 && unit < 3)
    {
        p_bytes /= 1024;
        ++unit;
    }
    std::ostringstream str;
    str << p_bytes;
    switch(unit)
    {
    case 0: str << " Bytes"; break;
    case 1: str << " KB"; break;
    case 2: str << " MB"; break;
    case 3: str << " GB"; break;
    default: return "weird"; break;
    }
    return str.str();
}