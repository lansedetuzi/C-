#ifndef _MEMORYPOOLBYLINKEDLIST
#define _MEMORYPOOLBYLINKEDLIST

#define MINUNITSIZE 64
struct Memory_Trunk;

typedef struct Memory_Block
{
	size_t m_count;
	size_t m_start;
	Memory_Trunk *m_pMemTrunk;
} Memory_Block;

/************************************************************************/
/* 可用内存块结构体                                                     */
/************************************************************************/
typedef struct Memory_Trunk
{
	Memory_Block *m_pFreeMemAddr;
	Memory_Trunk *m_preTrunk;
	Memory_Trunk *m_nextTrunk;
} Memory_Trunk;

/************************************************************************/
/* 内存池结构体                                                         */
/************************************************************************/
typedef struct MemoryPool
{
	void *memory;
	size_t size;
	Memory_Block *pMem_Map;
	Memory_Trunk *pFreeMemTrunk;
	Memory_Trunk *pFreeMemTrunkPool;
	size_t memUsedSize;						// 记录内存池中已经分配给用户的内存大小
	size_t memMapPoolCount;					// 记录链表单元缓冲池中剩余单元的个数，个数为0时不能分配单元给pFreeMemTrunk
	size_t FreeMemTrunkCount;				// 记录pFreeMemTrunk链表中的单元个数
	size_t memMapUnitCount;
	size_t memBlockCount;					// 一个mem_unit大小为MINUNITSIZE
} MemoryPool, *PMemoryPool;

/************************************************************************/
/* 创建内存池
   pBuf--给定的内存buf起始地址
   bufSize--给定的内存buf大小											*/
/************************************************************************/
PMemoryPool createMemoryPool(void* pBuf, size_t bufSize);

/************************************************************************/
/* 释放内存池
   pMemPool--要释放的内存池地址											*/
/************************************************************************/
void releaseMemoryPool(PMemoryPool *pMemPool);

/************************************************************************/
/*	从内存池分配指定大小的内存
	pMemPool--要分配的内存池地址
	memSize--分配内存的大小
	成功时返回要分配的内存起始地址，否则返回NULL						*/
/************************************************************************/
void* getMemory(size_t memSize, PMemoryPool *pMemPool);

/************************************************************************/
/* 从内存池中释放申请的内存
	pMemPool--内存池地址
	ptrMemBlock--申请的内存起始地址										*/
/************************************************************************/
void freeMemory(void* ptrMemBlock, PMemoryPool *pMemPool);

#endif // _MEMORYPOOLBYLINKEDLIST