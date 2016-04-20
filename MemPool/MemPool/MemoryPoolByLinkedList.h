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
/* �����ڴ��ṹ��                                                     */
/************************************************************************/
typedef struct Memory_Trunk
{
	Memory_Block *m_pFreeMemAddr;
	Memory_Trunk *m_preTrunk;
	Memory_Trunk *m_nextTrunk;
} Memory_Trunk;

/************************************************************************/
/* �ڴ�ؽṹ��                                                         */
/************************************************************************/
typedef struct MemoryPool
{
	void *memory;
	size_t size;
	Memory_Block *pMem_Map;
	Memory_Trunk *pFreeMemTrunk;
	Memory_Trunk *pFreeMemTrunkPool;
	size_t memUsedSize;						// ��¼�ڴ�����Ѿ�������û����ڴ��С
	size_t memMapPoolCount;					// ��¼����Ԫ�������ʣ�൥Ԫ�ĸ���������Ϊ0ʱ���ܷ��䵥Ԫ��pFreeMemTrunk
	size_t FreeMemTrunkCount;				// ��¼pFreeMemTrunk�����еĵ�Ԫ����
	size_t memMapUnitCount;
	size_t memBlockCount;					// һ��mem_unit��СΪMINUNITSIZE
} MemoryPool, *PMemoryPool;

/************************************************************************/
/* �����ڴ��
   pBuf--�������ڴ�buf��ʼ��ַ
   bufSize--�������ڴ�buf��С											*/
/************************************************************************/
PMemoryPool createMemoryPool(void* pBuf, size_t bufSize);

/************************************************************************/
/* �ͷ��ڴ��
   pMemPool--Ҫ�ͷŵ��ڴ�ص�ַ											*/
/************************************************************************/
void releaseMemoryPool(PMemoryPool *pMemPool);

/************************************************************************/
/*	���ڴ�ط���ָ����С���ڴ�
	pMemPool--Ҫ������ڴ�ص�ַ
	memSize--�����ڴ�Ĵ�С
	�ɹ�ʱ����Ҫ������ڴ���ʼ��ַ�����򷵻�NULL						*/
/************************************************************************/
void* getMemory(size_t memSize, PMemoryPool *pMemPool);

/************************************************************************/
/* ���ڴ�����ͷ�������ڴ�
	pMemPool--�ڴ�ص�ַ
	ptrMemBlock--������ڴ���ʼ��ַ										*/
/************************************************************************/
void freeMemory(void* ptrMemBlock, PMemoryPool *pMemPool);

#endif // _MEMORYPOOLBYLINKEDLIST