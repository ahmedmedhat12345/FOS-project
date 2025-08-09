/*
 * dynamic_allocator.c
 *
 *  Created on: Sep 21, 2023
 *      Author: HP
 */
#include <inc/assert.h>
#include <inc/string.h>
#include "../inc/dynamic_allocator.h"


// Adjusting allocation address to be 4-byte aligned



//==================================================================================//
//============================== GIVEN FUNCTIONS ===================================//
//==================================================================================//

//=====================================================
// 1) GET BLOCK SIZE (including size of its meta data):
//=====================================================
__inline__ uint32 get_block_size(void* va)
{
	uint32 *curBlkMetaData = ((uint32 *)va - 1) ;
	return (*curBlkMetaData) & ~(0x1);
}

//===========================
// 2) GET BLOCK STATUS:
//===========================
__inline__ int8 is_free_block(void* va)
{
	uint32 *curBlkMetaData = ((uint32 *)va - 1) ;
	return (~(*curBlkMetaData) & 0x1) ;
}

//===========================
// 3) ALLOCATE BLOCK:
//===========================

void *alloc_block(uint32 size, int ALLOC_STRATEGY)
{
	void *va = NULL;
	switch (ALLOC_STRATEGY)
	{
	case DA_FF:
		va = alloc_block_FF(size);
		break;
	case DA_NF:
		va = alloc_block_NF(size);
		break;
	case DA_BF:
		va = alloc_block_BF(size);
		break;
	case DA_WF:
		va = alloc_block_WF(size);
		break;
	default:
		cprintf("Invalid allocation strategy\n");
		break;
	}
	return va;
}
//===========================
// 4) PRINT BLOCKS LIST:
//===========================

void print_blocks_list(struct MemBlock_LIST list)
{
    cprintf("=========================================\n");
    struct BlockElement* blk;
    cprintf("\nDynAlloc Blocks List:\n");
    LIST_FOREACH(blk, &list)
    {
        // Print the address, size, and allocation status
        cprintf("Address: %p (size: %d, isFree: %d)\n", (void*)blk, get_block_size(blk), is_free_block(blk));
    }
    cprintf("=========================================\n");
}


////********************************************************************************//
////********************************************************************************//

//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//

bool is_initialized = 0;
//==================================
// [1] INITIALIZE DYNAMIC ALLOCATOR:
//==================================
void initialize_dynamic_allocator(uint32 daStart, uint32 initSizeOfAllocatedSpace)
{
    //=========================================
    //DON'T CHANGE THESE LINES=================
    if (initSizeOfAllocatedSpace == 0)
        return;
    is_initialized = 1;
    //=========================================
                 LIST_INIT(&freeBlocksList);
    uint32 *BEG_header = (uint32 *)daStart;
                  uint32 *END_header = (uint32 *)(daStart + initSizeOfAllocatedSpace - sizeof(uint32));
    uint32 blksz = initSizeOfAllocatedSpace - 2 * sizeof(uint32);
    uint32 *initial_free_block_header = (uint32 *)(daStart + sizeof(uint32));
               *BEG_header = (0 | 1);
    *END_header = (0 | 1);
           *initial_free_block_header = blksz & ~1;
    uint32 *initial_free_block_footer = (uint32 *)((uint8 *)initial_free_block_header + blksz - 4);
                        *initial_free_block_footer = blksz & ~1;
                    struct BlockElement *firstfreeblock = (struct BlockElement *)((char *)initial_free_block_header + 4);
    LIST_INSERT_HEAD(&freeBlocksList, firstfreeblock);
}

//==================================
// [2] SET BLOCK HEADER & FOOTER:
//==================================
void set_block_data(void* va, uint32 totalSize, bool isAllocated) {
    if (totalSize == 0) {
        return;
    }
              uint32 x = (uint32)va;
    uint32 blkHeaderint = x - sizeof(uint32);
                                uint32 blkFooterint = x + totalSize - 2 * sizeof(uint32);
    if (isAllocated) {
        totalSize |= 1;
    } else {
        totalSize &= ~1;
    }
    uint32 *blkHeader = (uint32 *)blkHeaderint;
                             uint32 *blkFooter = (uint32 *)blkFooterint;
                *blkHeader = totalSize;
    *blkFooter = totalSize;
}

//=========================================
// [3] ALLOCATE BLOCK BY FIRST FIT:
//=========================================

void *alloc_block_FF(uint32 size)
{
    //==================================================================================
    //DON'T CHANGE THESE LINES==========================================================
    //==================================================================================
    {
        if (size % 2 != 0) size++; // ensure that the size is even (to use LSB as allocation flag)
        if (size < DYN_ALLOC_MIN_BLOCK_SIZE)
            size = DYN_ALLOC_MIN_BLOCK_SIZE;
        if (!is_initialized)
        {
            uint32 required_size = size + 2 * sizeof(int)  + 2 * sizeof(int);
            uint32 da_start = (uint32)sbrk(ROUNDUP(required_size, PAGE_SIZE) / PAGE_SIZE);
            uint32 da_break = (uint32)sbrk(0);
            initialize_dynamic_allocator(da_start, da_break - da_start);
        }
    }
    //==================================================================================
    //==================================================================================

    if (size == 0)
    {
        return NULL;
    }
    struct BlockElement *pointer;
                              uint32 recentspace = size + 2 * sizeof(int);
    LIST_FOREACH(pointer, &(freeBlocksList))
    {
                                  uint32 spaceofblkkk = get_block_size((void *)pointer);
   if (recentspace <= spaceofblkkk)
        {
                                        uint32 separate;
if (spaceofblkkk - recentspace >= 16)
            {	separate = spaceofblkkk - recentspace;
 uint32 *recentblkk = (uint32 *)((uint32)pointer + recentspace);
                                   set_block_data((void *)pointer, recentspace, 1);
 set_block_data((void *)recentblkk, separate, 0);
                                LIST_INSERT_AFTER(&(freeBlocksList), (struct BlockElement *)pointer, (struct BlockElement *)recentblkk);
 LIST_REMOVE(&(freeBlocksList), pointer);
            }
            else
            {
                                    set_block_data((void *)pointer, spaceofblkkk, 1);
 LIST_REMOVE(&(freeBlocksList), pointer);
            }
                           return (void *)pointer;
        }
    }
                               uint32 wholespace = size + 2 * sizeof(uint32);
    void *modernstorage = sbrk(1);
                         if (modernstorage == (void *)-1)
                                                   {
        return NULL;
                                                    }
                           uint32 *limit = (uint32 *)((uint32)modernstorage + PAGE_SIZE - sizeof(uint32));
 *limit = 1;
                          struct BlockElement *finalemptyblk = LIST_LAST(&(freeBlocksList));
 uint32 *limitoffinalblk;
    if (finalemptyblk)
    {
    	          limitoffinalblk = (uint32 *)((uint32)finalemptyblk + get_block_size((void *)finalemptyblk));
 }
else
    {
    	               limitoffinalblk = NULL;
}
              if (finalemptyblk && (uint32)limitoffinalblk == (uint32)modernstorage)
    {
                            uint32 freshsz = get_block_size((void *)finalemptyblk) + PAGE_SIZE;
 set_block_data((void *)finalemptyblk, freshsz, 0);
}
  else
                  {
                                 set_block_data(modernstorage, PAGE_SIZE, 0);
LIST_INSERT_HEAD(&(freeBlocksList), (struct BlockElement *)modernstorage);
                    }
                            return alloc_block_FF(size);
}







// [4] ALLOCATE BLOCK BY BEST FIT:
//=========================================
void* alloc_block_BF(uint32 size) {/*

    */
	return NULL;
}
//===================================================
// [5] FREE BLOCK WITH COALESCING:
//===================================================
void free_block(void *va) {
	//panic("free_block is not implemented yet");
    if (va == NULL) {
        return;
    }
                      struct BlockElement *deleted = (struct BlockElement *)((uint32)va);
    uint32 blockSize = get_block_size((void *)deleted);
           uint32 sizeofmeta = sizeof(struct BlockElement);
    set_block_data((void *)deleted, blockSize, /*isAllocated*/ 0);
    // Insert the block into the free list in sorted order
                    struct BlockElement *ptr = NULL;
    LIST_FOREACH(ptr, &freeBlocksList) {
        if ((uint32)ptr > (uint32)deleted) break; // Find where to add
    }
    if (ptr == NULL) {
        LIST_INSERT_TAIL(&freeBlocksList, deleted);
    } else {
        LIST_INSERT_BEFORE(&freeBlocksList, ptr, deleted);
    }
    // merge with nxt blk if  free
              struct BlockElement *afterfree = LIST_NEXT(deleted);
    if (afterfree && is_free_block((void *)afterfree) &&
        ((uint32)deleted + blockSize  == (uint32)afterfree)) {
                        uint32 newSize = blockSize + get_block_size((void *)afterfree) ;
        set_block_data((void *)deleted, newSize, /*isAllocated*/ 0);
                    LIST_REMOVE(&freeBlocksList, afterfree);
    }
               struct BlockElement *beforefree = LIST_PREV(deleted);
    if (beforefree && is_free_block((void *)beforefree) &&
        ((uint32)beforefree + get_block_size((void *)beforefree)  == (uint32)deleted)) {
                    uint32 newSize = get_block_size((void *)beforefree) + get_block_size((void *)deleted) ;
        set_block_data((void *)beforefree, newSize, /*isAllocated*/ 0);
                              LIST_REMOVE(&freeBlocksList, deleted);
        deleted = beforefree;
    }
}

//=========================================
// [6] REALLOCATE BLOCK BY FIRST FIT:
//=========================================
void *realloc_block_FF(void *va, uint32 new_size){
	if (!va && new_size == 0)
	                 return NULL;
if (!va)
	        return alloc_block_FF(new_size);
	                   if (!new_size)
return free_block(va), NULL;
       uint32 szofmeta = sizeof(struct BlockElement);
struct BlockElement* cur = (struct BlockElement*)va - 1;
	                 uint32 prvsz = get_block_size(cur) - szofmeta;
	                        set_block_data(cur + 1, get_block_size(cur), 0);
	                              struct BlockElement* after = LIST_NEXT(cur);
	    if ((new_size > prvsz) && after && (uint32)cur + get_block_size(cur) == (uint32)after
	    		&& is_free_block(after))
	    {
	                uint32 newmrgdsz = get_block_size(cur) + get_block_size(after);
 set_block_data(cur + 1, newmrgdsz, 0);
	                           LIST_REMOVE(&freeBlocksList, after);
	    }
	 if (prvsz >= new_size)
	        set_block_data(cur + 1, new_size + szofmeta, 1);
	    return va;
void* new_va = alloc_block_FF(new_size);
	             if (!new_va)
	    {
	set_block_data(cur + 1, prvsz + szofmeta, 1);
	        return NULL;
	    }
	            memcpy(new_va, va, prvsz);
free_block(va);
	    return new_va;
}

/*********************************************************************************************/
/*********************************************************************************************/
//=========================================
// [7] ALLOCATE BLOCK BY WORST FIT:
//=========================================
void *alloc_block_WF(uint32 size)
{
	panic("alloc_block_WF is not implemented yet");
	return NULL;
}

//=========================================
// [8] ALLOCATE BLOCK BY NEXT FIT:
//=========================================
void *alloc_block_NF(uint32 size)
{
	panic("alloc_block_NF is not implemented yet");
	return NULL;
}
