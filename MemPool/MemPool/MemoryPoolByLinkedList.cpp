#include "MemoryPoolByLinkedList.h"
#include <memory.h>

PMemoryPool createMemoryPool(void* pBuf, size_t bufSize)
{
	memset(pBuf, 0, bufSize);
	PMemoryPool pMem_Pool = (PMemoryPool)pBuf;

	// ������Ҫ����memory map��Ԫ��
	size_t mem_pool_struct_size = sizeof(MemoryPool);
	pMem_Pool->memMapPoolCount = (bufSize - mem_pool_struct_size + MINUNITSIZE - 1) / MINUNITSIZE;
	pMem_Pool->memMapUnitCount = (bufSize - mem_pool_struct_size + MINUNITSIZE - 1) / MINUNITSIZE;
	pMem_Pool->pMem_Map = (Memory_Block *)((char *)pBuf);
}

