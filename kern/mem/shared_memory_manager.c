#include <inc/memlayout.h>
#include "shared_memory_manager.h"

#include <inc/mmu.h>
#include <inc/error.h>
#include <inc/string.h>
#include <inc/assert.h>
#include <inc/queue.h>
#include <inc/environment_definitions.h>

#include <kern/proc/user_environment.h>
#include <kern/trap/syscall.h>
#include "kheap.h"
#include "memory_manager.h"

//==================================================================================//
//============================== GIVEN FUNCTIONS ===================================//
//==================================================================================//
struct Share* get_share(int32 ownerID, char* name);

//===========================
// [1] INITIALIZE SHARES:
//===========================
//Initialize the list and the corresponding lock
void sharing_init()
{
#if USE_KHEAP
	LIST_INIT(&AllShares.shares_list) ;
	init_spinlock(&AllShares.shareslock, "shares lock");
#else
	panic("not handled when KERN HEAP is disabled");
#endif
}

//==============================
// [2] Get Size of Share Object:
//==============================
int getSizeOfSharedObject(int32 ownerID, char* shareName)
{
	//[PROJECT'24.MS2] DONE
	// This function should return the size of the given shared object
	// RETURN:
	//	a) If found, return size of shared object
	//	b) Else, return E_SHARED_MEM_NOT_EXISTS
	//
	struct Share* ptr_share = get_share(ownerID, shareName);
	if (ptr_share == NULL)
		return E_SHARED_MEM_NOT_EXISTS;
	else
		return ptr_share->size;

	return 0;
}

//===========================================================


//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//
//===========================
// [1] Create frames_storage:
//===========================
// Create the frames_storage and initialize it by 0
inline struct FrameInfo** create_frames_storage(int numOfFrames)
{
	//TODO: [PROJECT'24.MS2 - #16] [4] SHARED MEMORY - create_frames_storage()
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	//panic("create_frames_storage is not implemented yet");
	//Your Code is Here...
	 struct FrameInfo **frames = (struct FrameInfo **)kmalloc(sizeof(struct FrameInfo*) * numOfFrames);
		if(frames == NULL){
			return NULL;
		}

int i = 0;
	                      	while (i < numOfFrames) { frames[i] = 0;
		                          ++i;
		}
	                                    	return frames;
}

//=====================================
// [2] Alloc & Initialize Share Object:
//=====================================
//Allocates a new shared object and initialize its member
//It dynamically creates the "framesStorage"
//Return: allocatedObject (pointer to struct Share) passed by reference
struct Share* create_share(int32 ownerID, char* shareName, uint32 size, uint8 isWritable)
{
	//TODO: [PROJECT'24.MS2 - #16] [4] SHARED MEMORY - create_share()
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	//panic("create_share is not implemented yet");
	//Your Code is Here...
	struct Share* current = (struct Share*)kmalloc(sizeof(struct Share));
		if(current == NULL)
		{
			return NULL;
		}
		current->size = size;
	                                    	current->isWritable = isWritable;
		                                                             current->ownerID = ownerID;
		strncpy(current->name,shareName,64);
	                               	current->references = 1;

		                                       int framescnt = ROUNDUP(size, PAGE_SIZE)/ PAGE_SIZE;
		current->framesStorage = create_frames_storage(framescnt);

	                                         	if(current->framesStorage == NULL)
		{
			                                   kfree(current);
			return NULL;
		}
		                                   uint32 address = (uint32)current;
		                  current->ID = address & 0x7ffffff;
		return current;
}

//=============================
// [3] Search for Share Object:
//=============================
//Search for the given shared object in the "shares_list"
//Return:
//	a) if found: ptr to Share object
//	b) else: NULL
struct Share* get_share(int32 ownerID, char* name)
{
	//TODO: [PROJECT'24.MS2 - #17] [4] SHARED MEMORY - get_share()
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	//panic("get_share is not implemented yet");
	//Your Code is Here...
	struct Share* share;
	acquire_spinlock(&(AllShares.shareslock));
		           LIST_FOREACH(share, &(AllShares.shares_list))
		{

if(share->ownerID == ownerID && strcmp(share->name, name) == 0){
			                  	release_spinlock(&(AllShares.shareslock));
				return share;
}
             		}
		release_spinlock(&(AllShares.shareslock));
		return NULL;
}

//=========================
// [4] Create Share Object:
//=========================
int createSharedObject(int32 ownerID, char* shareName, uint32 size, uint8 isWritable, void* virtual_address) {

	struct Env* myenv = get_cpu_proc();
                                               struct Share* standings = get_share(ownerID, shareName);
    if (standings != NULL) {
                                         return E_SHARED_MEM_EXISTS;
    }

                         struct Share* current = create_share(ownerID, shareName, size, isWritable);
    if (current == NULL) {
                                      return E_NO_SHARE;
    }
                             int framescount = ROUNDUP(size, PAGE_SIZE) / PAGE_SIZE;
    int i = 0;
    struct FrameInfo* frameInfo;
    while (i < framescount) {
    int ret = allocate_frame(&(frameInfo));
map_frame(myenv->env_page_directory, frameInfo, (uint32)virtual_address + i * PAGE_SIZE, PERM_USER | PERM_WRITEABLE);
current ->framesStorage[i] = frameInfo;
        ++i;
    }
                                    acquire_spinlock(&(AllShares.shareslock));
    LIST_INSERT_HEAD(&(AllShares.shares_list), current);
                              release_spinlock(&(AllShares.shareslock));
    return current->ID;

}

//======================
// [5] Get Share Object:
//======================
int getSharedObject(int32 ownerID, char* shareName, void* virtual_address)
{
	//TODO: [PROJECT'24.MS2 - #21] [4] SHARED MEMORY [KERNEL SIDE] - getSharedObject()
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	//panic("getSharedObject is not implemented yet");
	//Your Code is Here...
	struct Env* myenv = get_cpu_proc();
	                              		 struct Share* currentshare = get_share(ownerID, shareName);
 if (currentshare == NULL){
                                				 return E_SHARED_MEM_NOT_EXISTS;
			 }

                                        		 int framescount = ROUNDUP(currentshare->size, PAGE_SIZE) / PAGE_SIZE;
		 int i = 0;
		 while (i < framescount) {
		                                               map_frame(myenv->env_page_directory, currentshare->framesStorage[i], (uint32)virtual_address + i * PAGE_SIZE, PERM_USER | (currentshare->isWritable ? PERM_WRITEABLE : 0));
		                                                  ++i;
		 }

                              			currentshare -> references +=1;

			return currentshare ->ID;
}

//==================================================================================//
//============================== BONUS FUNCTIONS ===================================//
//==================================================================================//

//==========================
// [B1] Delete Share Object:
//==========================
//delete the given shared object from the "shares_list"
//it should free its framesStorage and the share object itself
void free_share(struct Share* ptrShare)
{
	//TODO: [PROJECT'24.MS2 - BONUS#4] [4] SHARED MEMORY [KERNEL SIDE] - free_share()
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	panic("free_share is not implemented yet");
	//Your Code is Here...

}
//========================
// [B2] Free Share Object:
//========================
int freeSharedObject(int32 sharedObjectID, void *startVA)
{
	//TODO: [PROJECT'24.MS2 - BONUS#4] [4] SHARED MEMORY [KERNEL SIDE] - freeSharedObject()
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	panic("freeSharedObject is not implemented yet");
	//Your Code is Here...

}
