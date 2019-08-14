#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#ifndef BITMAP_H
#include "bitmap.h"
#endif

#ifndef SYNCH_H
#include "synch.h"
#endif

class MemoryManager{
public:
	MemoryManager(int numPages);
	~MemoryManager();
	int AllocPage();
	void FreePage(int physPageNum);
	bool PageIsAllocated(int physPageNum);
	bool IsAnyPageFree();
	int NumFreePages();
       int Alloc(int p,TranslationEntry &e);
       int AllocByForce();
private:
	BitMap *bitMap;
	Lock *lock;
      int *processMap;
     TranslationEntry **entries;

};

#endif
