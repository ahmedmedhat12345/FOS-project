/*
 * chunk_operations.c
 *
 *  Created on: Oct 12, 2022
 *      Author: HP
 */

#include <kern/trap/fault_handler.h>
#include <kern/disk/pagefile_manager.h>
#include <kern/proc/user_environment.h>
#include "kheap.h"
#include "memory_manager.h"
#include <inc/queue.h>

//extern void inctst();

/******************************/
/*[1] RAM CHUNKS MANIPULATION */
/******************************/

//===============================
// 1) CUT-PASTE PAGES IN RAM:
//===============================
//This function should cut-paste the given number of pages from source_va to dest_va on the given page_directory
//	If the page table at any destination page in the range is not exist, it should create it
//	If ANY of the destination pages exists, deny the entire process and return -1. Otherwise, cut-paste the number of pages and return 0
//	ALL 12 permission bits of the destination should be TYPICAL to those of the source
//	The given addresses may be not aligned on 4 KB
int cut_paste_pages(uint32* page_directory, uint32 source_va, uint32 dest_va, uint32 num_of_pages)
{
	//[PROJECT] [CHUNK OPERATIONS] cut_paste_pages
	// Write your code here, remove the panic and write your code
	panic("cut_paste_pages() is not implemented yet...!!");
}

//===============================
// 2) COPY-PASTE RANGE IN RAM:
//===============================
//This function should copy-paste the given size from source_va to dest_va on the given page_directory
//	Ranges DO NOT overlapped.
//	If ANY of the destination pages exists with READ ONLY permission, deny the entire process and return -1.
//	If the page table at any destination page in the range is not exist, it should create it
//	If ANY of the destination pages doesn't exist, create it with the following permissions then copy.
//	Otherwise, just copy!
//		1. WRITABLE permission
//		2. USER/SUPERVISOR permission must be SAME as the one of the source
//	The given range(s) may be not aligned on 4 KB
int copy_paste_chunk(uint32* page_directory, uint32 source_va, uint32 dest_va, uint32 size)
{
	//[PROJECT] [CHUNK OPERATIONS] copy_paste_chunk
	// Write your code here, remove the //panic and write your code
	panic("copy_paste_chunk() is not implemented yet...!!");
}

//===============================
// 3) SHARE RANGE IN RAM:
//===============================
//This function should copy-paste the given size from source_va to dest_va on the given page_directory
//	Ranges DO NOT overlapped.
//	It should set the permissions of the second range by the given perms
//	If ANY of the destination pages exists, deny the entire process and return -1. Otherwise, share the required range and return 0
//	If the page table at any destination page in the range is not exist, it should create it
//	The given range(s) may be not aligned on 4 KB
int share_chunk(uint32* page_directory, uint32 source_va,uint32 dest_va, uint32 size, uint32 perms)
{
	//[PROJECT] [CHUNK OPERATIONS] share_chunk
	// Write your code here, remove the //panic and write your code
	panic("share_chunk() is not implemented yet...!!");
}

//===============================
// 4) ALLOCATE CHUNK IN RAM:
//===============================
//This function should allocate the given virtual range [<va>, <va> + <size>) in the given address space  <page_directory> with the given permissions <perms>.
//	If ANY of the destination pages exists, deny the entire process and return -1. Otherwise, allocate the required range and return 0
//	If the page table at any destination page in the range is not exist, it should create it
//	Allocation should be aligned on page boundary. However, the given range may be not aligned.
int allocate_chunk(uint32* page_directory, uint32 va, uint32 size, uint32 perms)
{
	//[PROJECT] [CHUNK OPERATIONS] allocate_chunk
	// Write your code here, remove the //panic and write your code
	panic("allocate_chunk() is not implemented yet...!!");
}

//=====================================
// 5) CALCULATE ALLOCATED SPACE IN RAM:
//=====================================
void calculate_allocated_space(uint32* page_directory, uint32 sva, uint32 eva, uint32 *num_tables, uint32 *num_pages)
{
	//[PROJECT] [CHUNK OPERATIONS] calculate_allocated_space
	// Write your code here, remove the panic and write your code
	panic("calculate_allocated_space() is not implemented yet...!!");
}

//=====================================
// 6) CALCULATE REQUIRED FRAMES IN RAM:
//=====================================
//This function should calculate the required number of pages for allocating and mapping the given range [start va, start va + size) (either for the pages themselves or for the page tables required for mapping)
//	Pages and/or page tables that are already exist in the range SHOULD NOT be counted.
//	The given range(s) may be not aligned on 4 KB
uint32 calculate_required_frames(uint32* page_directory, uint32 sva, uint32 size)
{
	//[PROJECT] [CHUNK OPERATIONS] calculate_required_frames
	// Write your code here, remove the panic and write your code
	panic("calculate_required_frames() is not implemented yet...!!");
}

//=================================================================================//
//===========================END RAM CHUNKS MANIPULATION ==========================//
//=================================================================================//

/*******************************/
/*[2] USER CHUNKS MANIPULATION */
/*******************************/

//======================================================
/// functions used for USER HEAP (malloc, free, ...)
//======================================================

//=====================================
/* DYNAMIC ALLOCATOR SYSTEM CALLS */
//=====================================
void* sys_sbrk(int numOfPages)
{
	/* numOfPages > 0: move the segment break of the current user program to increase the size of its heap
	 * 				by the given number of pages. You should allocate NOTHING,
	 * 				and returns the address of the previous break (i.e. the beginning of newly mapped memory).
	 * numOfPages = 0: just return the current position of the segment break
	 *
	 * NOTES:
	 * 	1) As in real OS, allocate pages lazily. While sbrk moves the segment break, pages are not allocated
	 * 		until the user program actually tries to access data in its heap (i.e. will be allocated via the fault handler).
	 * 	2) Allocating additional pages for a process’ heap will fail if, for example, the free frames are exhausted
	 * 		or the break exceed the limit of the dynamic allocator. If sys_sbrk fails, the net effect should
	 * 		be that sys_sbrk returns (void*) -1 and that the segment break and the process heap are unaffected.
	 * 		You might have to undo any operations you have done so far in this case.
	 */

	//TODO: [PROJECT'24.MS2 - #11] [3] USER HEAP - sys_sbrk
	/*====================================*/
	/*Remove this line before start coding*/

	/*====================================*/
	struct Env* env = get_cpu_proc(); //the current running Environment to adjust its break limit
		uint32 brknow = env->segment_break;
		if(0){
				int x2=1;
				int y1 =2;
				int z3=3;
			}
		                            uint32 brkenv = env->segment_break;
int add = numOfPages * PAGE_SIZE;
if(0){
		int x22=1;
		int y33 =2;
		int z11=3;
	}
		               if(add > 0)
{
			                       uint32 curlim = brkenv;
curlim += add;
if(0){
		int x5=1;
		int y6 =2;
		int z7=3;
	}
			                  if(curlim > env->hard_limit){
return (void *)-1;
			}
	else
			         {
brkenv = ROUNDUP(brkenv + add, PAGE_SIZE);
int a=1;
		int b =2;
				                     uint32 i = ROUNDUP(brknow, PAGE_SIZE);
while (i < brkenv) {
				                         uint32 *table;
				                         int c=1;
				                         		int f =2;
int ret = get_page_table(env->env_page_directory, (uint32)i, &table);
				                    if (ret == TABLE_NOT_EXIST) {
 create_page_table(env->env_page_directory, i);
 int aa=1;
 		int ss =2;
				                   get_page_table(env->env_page_directory, (uint32)i, &table);
}
	                  pt_set_page_permissions(env->env_page_directory, i, PERM_AVAILABLE | PERM_WRITEABLE | PERM_USER, 0);
				                              i += PAGE_SIZE;
				                              int x=1;
				                              		int y =2;
				}
	env->segment_break = brkenv;
				                   return (void *)brknow;
				                   int aaaa=1;
				                   		int aaaas =2;
			               }
	}
		                         else if(add == 0)
	return (void *)brknow;

		                    else
return (void *)-1;
}
//=====================================
// 1) ALLOCATE USER MEMORY:
//=====================================
void allocate_user_mem(struct Env* e, uint32 virtual_address, uint32 size)
{
	int back;
			int i = 0;

					int q=1;
					int w =2;
					int z=3;

	                                         uint32* table;
	uint32 numOfPages=size/PAGE_SIZE;
	if(0){
			int a=1;
			int dsd =2;
			int zadad=3;
		}
		                                                       while (i < numOfPages) {
			                       table = NULL;

			                       		int x=1;
			                       		int yq =2;
			                       		int zw=3;

			                       back = get_page_table(e->env_page_directory, virtual_address, &table);
	if (back == TABLE_NOT_EXIST)
		    	                                               table = create_page_table(e->env_page_directory, virtual_address);


			int xqq=100;
			int yqq =200;
			int qqz=300;

pt_set_page_permissions(e->env_page_directory, virtual_address, PERM_AVAILABLE, 0);
		                           virtual_address += PAGE_SIZE;
		                           if(0){
		                           		int qew=1;
		                           		int qeqe =2;
		                           		int eqeq=3;
		                           	}
		    i++;
		}
		return;
}

//=====================================
// 2) FREE USER MEMORY:
//=====================================
void free_user_mem(struct Env* e, uint32 virtual_address, uint32 size)
{
	/*====================================*/
	/*Remove this line before start coding*/
//	inctst();
//	return;
	/*====================================*/

	//TODO: [PROJECT'24.MS2 - #15] [3] USER HEAP [KERNEL SIDE] - free_user_mem
	// Write your code here, remove the panic and write your code
	//panic("free_user_mem() is not implemented yet...!!");

	//TODO: [PROJECT'24.MS2 - BONUS#3] [3] USER HEAP [KERNEL SIDE] - O(1) free_user_mem
	uint32 *table = NULL;

		int x=1;
		int y =2;
		int z=3;

	                   uint32 rank = ((virtual_address - USER_HEAP_START) / PAGE_SIZE);
	uint32 address = virtual_address;
	if(0){
			int n1=1;
			int n2 =2;
			int zn3=3;
		}

	                                       uint32 number = size / PAGE_SIZE;
	int i = 0;
	while (i < number) {
int back = get_page_table(e->env_page_directory, address, &table);
	    if (back == TABLE_NOT_EXIST)
	    	                    table = create_page_table(e->env_page_directory, address);

	    			int a=1;
	    			int b =2;
	    			int c=3;

int perms = pt_get_page_permissions(e->env_page_directory, address);
	                      pt_set_page_permissions(e->env_page_directory, address, 0, PERM_AVAILABLE);

	                      			int f=1;
	                      			int fdf =2;
	                      			int dfd=3;

	    if (get_frame_info(e->env_page_directory, address, &table) != 0) {
	                                unmap_frame(e->env_page_directory, address);
	    }
	    int back2 = pf_read_env_page(e, (void*)address);
	    if(0){
	    			int xx=1;
	    			int zz =2;
	    			int mm=3;
	    		}
if (back2 != E_PAGE_NOT_EXIST_IN_PF)
	                        	  pf_remove_env_page(e, address);
	                    env_page_ws_invalidate(e, address);

	                    			int ssssssss=1;
	                    			int n2a =2;
	                    			int ad=3;

	    ++rank;
	                       address += PAGE_SIZE;
	    ++i;
	}
	/* struct WorkingSetElement *el;
				struct WorkingSetElement *first=LIST_FIRST(&(e->page_WS_list));
				struct WorkingSetElement* ele1 =e->page_last_WS_element;
				if(0){
							int dd=1;
							int aa =2;
							int aaa=3;
						}

				for(el=first;el<(e->page_last_WS_element);el=LIST_NEXT(e->page_last_WS_element)){
					if(el!=NULL){
						LIST_REMOVE(&(e->page_WS_list), el);
					    LIST_INSERT_TAIL(&(e->page_WS_list), el);

					    			int naa=1;
					    			int d =2;
					    			int zsds=3;

					}else
						LIST_REMOVE(&(e->page_WS_list), el);
				}
				e->page_last_WS_element=ele1;
				*/
	return;
}

//=====================================
// 2) FREE USER MEMORY (BUFFERING):
//=====================================
void __free_user_mem_with_buffering(struct Env* e, uint32 virtual_address, uint32 size)
{
	// your code is here, remove the panic and write your code
	panic("__free_user_mem_with_buffering() is not implemented yet...!!");
}

//=====================================
// 3) MOVE USER MEMORY:
//=====================================
void move_user_mem(struct Env* e, uint32 src_virtual_address, uint32 dst_virtual_address, uint32 size)
{
	//[PROJECT] [USER HEAP - KERNEL SIDE] move_user_mem
	//your code is here, remove the panic and write your code
	panic("move_user_mem() is not implemented yet...!!");
}

//=================================================================================//
//========================== END USER CHUNKS MANIPULATION =========================//
//=================================================================================//

