#pragma once


class MemoryPool
{
private:
    CONST static SIZE_T CHUNK_HEADER_SIZE;

    UCHAR** m_ppRawMemArray;
    UINT    m_memArraySize;
    UINT    m_chunkSize;
    UINT    m_numChunks;
    BOOL    m_resizable;
    UCHAR*  m_pHead;

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
    VOID PrintInfo(VOID) CONST;
    SIZE_T GetSystemAllocatedBytes(VOID) CONST { return m_memArraySize * m_numChunks * (m_chunkSize + CHUNK_HEADER_SIZE); }
    SIZE_T GetPoolAllocatedChunks(VOID) CONST { return m_allocated; }
    SIZE_T GetPoolAllocatedBytes(VOID) CONST { return m_allocated * (m_chunkSize + CHUNK_HEADER_SIZE); }
    SIZE_T GetPoolFreeBytes(VOID) CONST { return (m_memArraySize * m_numChunks - m_allocated) * (m_chunkSize + CHUNK_HEADER_SIZE); }
    DOUBLE GetPoolUsage(VOID) CONST { return (DOUBLE)this->GetPoolAllocatedBytes() / (DOUBLE)(this->GetPoolAllocatedBytes() + this->GetPoolFreeBytes()); }
    UINT GetChunkSize(VOID) CONST { return m_chunkSize; }
};