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
    UINT    m_allocated;

    BOOL GrowMemory(VOID);
    UCHAR* CreateNewMemoryBlock(VOID);
    UCHAR* GetNext(UCHAR* p_pBlock);
    VOID SetNext(UCHAR* p_pBlock, UCHAR* p_pNext);

public:
    MemoryPool(VOID);
    ~MemoryPool(VOID);

    BOOL Init(INT p_chunkSize, INT p_numChunks, BOOL p_resizeable);
    VOID* Alloc(VOID);
    VOID Free(VOID* p_pMem);

    UINT GetNumAllocatedChunks(VOID) CONST { return m_allocated; }
};

