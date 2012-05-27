#pragma once

class MemoryPool
{
private:
    UCHAR** m_ppRawMemArray;
    UINT    m_memArraySize;
    UINT    m_chunkSize;
    UINT    m_numChunks;
    BOOL    m_resizable;
    UCHAR*  m_pHead;

    BOOL growMemory(VOID);
    UCHAR* createNewMemoryBlock(VOID);
    UCHAR* getNext(UCHAR* p_pBlock);
    VOID setNext(UCHAR* p_pBlock, UCHAR* p_pNext);

public:
    MemoryPool(VOID);
    ~MemoryPool(VOID);

    BOOL init(INT p_chunkSize, INT p_numChunks, BOOL p_resizeable);
    VOID* Alloc(VOID);
    VOID Free(VOID* p_pMem);
};

