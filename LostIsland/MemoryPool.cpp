#include "StdAfx.h"
#include "MemoryPool.h"


const static size_t CHUNK_HEADER_SIZE = sizeof(UCHAR*);


MemoryPool::MemoryPool(VOID):
m_ppRawMemArray(NULL), m_memArraySize(0), m_pHead(NULL)
{
}


MemoryPool::~MemoryPool(void)
{
    for(UINT i=0; i < m_memArraySize; ++i) {
        delete[] m_ppRawMemArray[i];
    }
    delete[] m_ppRawMemArray;
}


BOOL MemoryPool::init(INT p_chunkSize, INT p_numChunks, BOOL p_resizable)
{
    m_chunkSize = p_chunkSize;
    m_numChunks = p_numChunks;
    m_resizable = p_resizable;
    return this->growMemory();
}


BOOL MemoryPool::growMemory(VOID)
{
    UCHAR** ppMemArray = new UCHAR*[m_memArraySize+1];
    for(UINT i=0; i < m_memArraySize; ++i)
    {
        ppMemArray[i] = m_ppRawMemArray[i];
    }
    ppMemArray[m_memArraySize] = this->createNewMemoryBlock();

    if(m_pHead != NULL)
    {
        UCHAR* pCurrent = m_pHead;
        UCHAR* pNext = this->getNext(pCurrent);
        while(pNext != NULL) {
            pCurrent = pNext;
            pNext = this->getNext(pCurrent);
        }
        this->setNext(pCurrent, ppMemArray[m_memArraySize]);
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


UCHAR* MemoryPool::createNewMemoryBlock(VOID)
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


UCHAR* MemoryPool::getNext(UCHAR* p_pBlock)
{
    UCHAR** pChunkHeader = (UCHAR**)p_pBlock;
    return pChunkHeader[0];
}


VOID MemoryPool::setNext(UCHAR* p_pBlock, UCHAR* p_pNext)
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
            this->growMemory();
        }
        else
        {
            return NULL;
        }
    }
    UCHAR* pMem = m_pHead;
    m_pHead = this->getNext(pMem);
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
    this->setNext(m_pHead, pOldHead);
}