#include "memorymanager.h"

MemoryManager::MemoryManager(int numPages)
{
         processMap = (int *)malloc(sizeof(int)*1000);
	entries=(TranslationEntry **)malloc(sizeof(TranslationEntry *)*1000);
	
	bitMap = new BitMap(numPages);
	lock = new Lock("lock of memory manager");
        
}

MemoryManager::~MemoryManager()
{
	delete bitMap;
	delete lock;
}



void
MemoryManager::FreePage(int physPageNum)
{
	lock->Acquire();
	bitMap->Clear(physPageNum);
	lock->Release();
}

bool
MemoryManager::PageIsAllocated(int physPageNum)
{
	lock->Acquire();
	bool ret = bitMap->Test(physPageNum);
	lock->Release();
	return ret;
}

bool
MemoryManager::IsAnyPageFree()
{
	lock->Acquire();
	bool ret;
	if(bitMap->NumClear() == 0)
		ret = false;
	else
		ret = true;
	lock->Release();
	return ret;
}

int
MemoryManager::AllocPage()
{
	lock->Acquire();
	int ret = bitMap->Find();
	lock->Release();
	return ret;
}


int
MemoryManager::Alloc(int p,TranslationEntry &e)
{
	lock->Acquire();
	int alloted = bitMap->Find();
	if(alloted >0){
		processMap[alloted]=p;
		entries[alloted]=e;
	}
	lock->Release();
	return ret;
}

int
MemoryManager::AllocByForce()
{	
	lock->Acquire();
	//int ret = rand()%NumPhysPages;	//for random replacement

       int total=bitMap->itemnum();
       int no=1000000000; //max number
        int p;
      TranslationEntry * t;

     for(i=1;i<=10000;i++)
     {
          t=entries[i];
         if(t!=NULL)
            {
              if(t->time<no)
                { 
                     no=t->time;
                     p=t->physicalPage;
                }

               
            }
     }


	
	lock->Release();
	return p;
}


int
MemoryManager::NumFreePages()
{
	lock->Acquire();
	int ret = bitMap->NumClear();
	lock->Release();
	return ret;
}
