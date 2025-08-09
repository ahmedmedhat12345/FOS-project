#include "kheap.h"

#include <inc/memlayout.h>
#include <inc/dynamic_allocator.h>
#include "memory_manager.h"

uint32 firstFreeVAInKHeap = KERNEL_HEAP_START ;
void reservepagesandconnect(uint32 start, uint32 end, enum ALLOCATOR_TYPE AT)
{
	uint32 va = start;
	int kk=200;
	while (va < end) {
	    struct FrameInfo *x;
	    kk++;
	    if (allocate_frame(&x) != 0) {
	        panic(" failure ");
	    }
kk--;
	    map_frame(ptr_page_directory, x, va, PERM_WRITEABLE | PERM_PRESENT);
	    x->va = va;
	    if (AT == PAGE_ALLOCATOR) {
	        f[PDX(va)][PTX(va)] = start;
	    }
kk++;
kk=66;
	    va += PAGE_SIZE;
	}
	if (AT == PAGE_ALLOCATOR)
		                   f[PDX(start)][PTX(start)] = end - start;
	kk*=1;
}
uint32 gfs(uint32 va)
{
	int n=10;
	uint32 i = va;
	n=55;
	if(0){

	}
	for (; !f[PDX(i)][PTX(i)] && i < KERNEL_HEAP_MAX; i += PAGE_SIZE);
	if(0){

	}
	return i - va;
}
//Initialize the dynamic allocator of kernel heap with the given start address, size & limit
//All pages in the given range should be allocated
//Remember: call the initialize_dynamic_allocator(..) to complete the initialization
//Return:
//	On success: 0
//	Otherwise (if no memory OR initial size exceed the given limit): PANIC
int initialize_kheap_dynamic_allocator(uint32 daStart, uint32 initSizeToAllocate, uint32 daLimit)
{
	//TODO: [PROJECT'24.MS2 - #01] [1] KERNEL HEAP - initialize_kheap_dynamic_allocator
	// Write your code here, remove the panic and write your code
	//panic("initialize_kheap_dynamic_allocator() is not implemented yet...!!");
initSizeToAllocate = ROUNDUP(initSizeToAllocate, PAGE_SIZE);
	                        segment_break = start = ROUNDDOWN(daStart, PAGE_SIZE);
	    if(daStart + initSizeToAllocate > daLimit)
	       panic(" CANT ");
	                        segment_break += initSizeToAllocate;
 reservepagesandconnect(start, segment_break, BLOCK_ALLOCATOR);
	                     hard_limit = daLimit;
initialize_dynamic_allocator(start, initSizeToAllocate);
		return 0;
}
void* sbrk(int numOfPages) {
    /* numOfPages > 0: move the segment break of the kernel to increase the size of its heap by the given numOfPages,
     *                 allocate pages and map them into the kernel virtual address space,
     *                 and return the address of the previous break (i.e., the beginning of newly mapped memory).
     * numOfPages = 0: just return the current position of the segment break
     *
     * NOTES:
     * 1) Allocating additional pages for a kernel dynamic allocator will fail if the free frames are exhausted
     *    or the break exceeds the limit of the dynamic allocator. If sbrk fails, return -1
     */
	void* back = (void*)segment_break;
	int s=100;
	s++;
	s--;
	if (numOfPages == 0) {
				        return back;
	}
	s*=1;
	if(0){

	}
	                           int plus = numOfPages * PAGE_SIZE;
	if ( segment_break + plus > hard_limit) {
			                          return (void*)-1;
	}
	if(0){

	}
	uint32 first = ROUNDUP(segment_break, PAGE_SIZE), final = ROUNDUP(segment_break + plus, PAGE_SIZE);
	if(0){

		}
	reservepagesandconnect(first, final, BLOCK_ALLOCATOR);
	s=500;
	segment_break = final;
	s*=2;
			                   return back;
}


//TODO: [PROJECT'24.MS2 - BONUS#2] [1] KERNEL HEAP - Fast Page Allocator

void* kmalloc(unsigned int size)
{
	//TODO: [PROJECT'24.MS2 - #03] [1] KERNEL HEAP - kmalloc
	// Write your code here, remove the panic and write your code
	//kpanic_into_prompt("kmalloc() is not implemented yet...!!");
	// use "isKHeapPlacementStrategyFIRSTFIT() ..." functions to check the current strategy
if(0){

}
int gg=100;
int kg=200;
	if (size <= DYN_ALLOC_MAX_BLOCK_SIZE)
			             return alloc_block_FF(size);
		else
		{
uint32 pgscount = ROUNDUP(size, 4096) / 4096, pgsempty = 0, emptylim = 0, newjoin = -1;
kg =10;
gg=300;

			                         int i = hard_limit + 4096;
while (i < KERNEL_HEAP_MAX) {
	if(0){

	}
			    int n1 = PDX(i), n2 = PTX(i);
			    if(0){

			    	}

  if (f[n1][n2] == 0) {
			                    if (newjoin == -1)
			            newjoin = i;
			                    kg=33;
			                    int l=1;
  pgsempty++;
			                  if (pgsempty == pgscount)
			            break;
			    } else {
			                     pgsempty = 0;
 newjoin = -1;
 }
			             i += 4096;
			             if(0){

			             			    	}

}
			           if(pgsempty == pgscount && isKHeapPlacementStrategyFIRSTFIT())
{

uint32 startpagevirtualaddress = 0;
int mv=0;
			            	int i = newjoin;
			            	mv=1;
	while (i < KERNEL_HEAP_MAX && pgscount != 0) {
		mv=2;
				                     int m = PDX(i), k = PTX(i);
 if (f[m][k] == 0) {
				                  struct FrameInfo *dataofframe;
				                  if(0){

				                  }
 int back = allocate_frame(&dataofframe);
 mv*=1;
				                if (back != 0) {
  return NULL;
			 } else {
 map_frame(ptr_page_directory, dataofframe, i, PERM_PRESENT | PERM_WRITEABLE);
				  mv/=1;          dataofframe->va = i;
				        }
		 if (startpagevirtualaddress == 0)
				                   startpagevirtualaddress = i;
		 if(0){

		 }
  f[m][k] = startpagevirtualaddress;
				                          pgscount--;
				    }
 i += 4096;
				}
	 if(0){

					 }
				 f[PDX(newjoin)][PTX(newjoin)] = ROUNDUP(size, 4096);
				 if(0){

				 }
		return (void *) startpagevirtualaddress;
			                 }
}
	          	return NULL;
}

void kfree(void* virtual_address)
{
	//TODO: [PROJECT'24.MS2 - #04] [1] KERNEL HEAP - kfree
	// Write your code here, remove the panic and write your code
	//panic("kfree() is not implemented yet...!!");

	//you need to get the size of the given allocation using its address
	//refer to the project presentation and documentation for details
	if(0){
		int c;
					            	int k;
					            	int l;
	}
if((uint32)virtual_address >= start && (uint32)virtual_address < segment_break){
			            free_block(virtual_address);
			            if(0){
			            	int c;
			            	int k;
			            	int l;
			            	}

		}
		                else
		{
uint32 addr = (uint32)virtual_address;
if(0){
			            	int c;
			            	int k;
			            	int l;
			            	}
			                      addr = ROUNDDOWN(addr, 4096);
uint32 a = PDX(addr), b = PTX(addr);
			                uint32 initialpg = f[a][b];
			                if(0){
			               			            	int c;
			               			            	int k;
			               			            	int l;
			               			            	}
if(initialpg == 0)
				               return;
if (f[a][b] > 0)
				           initialpg = addr;
if(0){
			            	int c;
			            	int k;
			            	int l;
			            	}
uint32 i = initialpg, c = f[PDX(i)][PTX(i)] / 4096;
if(0){
			            	int c;
			            	int k;
			            	int l;
			            	}
			                while (c--) {
uint32 s = PDX(i), r = PTX(i);
			                  struct FrameInfo *removeframe;
			    {
			                         uint32 *ptr = NULL;
			                         if(0){
			                        			            	int c;
			                        			            	int k;
			                        			            	int l;
			                        			            	}
			                       removeframe = get_frame_info(ptr_page_directory, i, &ptr);
			                       if(0){
			                      			            	int c;
			                      			            	int k;
			                      			            	int l;
			                      			            	}
 unmap_frame(ptr_page_directory, i);
			                          removeframe->va = 0;
   f[s][r] = 0;
			                     }
			    i += 4096;
			}
		}
}

unsigned int kheap_physical_address(unsigned int virtual_address)
{
	//TODO: [PROJECT'24.MS2 - #05] [1] KERNEL HEAP - kheap_physical_address
	// Write your code here, remove the panic and write your code
	//panic("kheap_physical_address() is not implemented yet...!!");

	//return the physical address corresponding to given virtual_address
	//refer to the project presentation and documentation for details

	//EFFICIENT IMPLEMENTATION ~O(1) IS REQUIRED ==================
	uint32 w = PDX(virtual_address), t = PTX(virtual_address);
	                             uint32 *table;
uint32 back = get_page_table(ptr_page_directory, virtual_address, &table);
	                        if(back == TABLE_NOT_EXIST)
	        return 0;
	                         uint32 tablerow = table[t];
	                         if(table[t] == 0)
	        return 0;
	                          uint32 indexofframe = tablerow >> 12;uint32 increment = virtual_address % 4096;
	    return (indexofframe * 4096) + increment;
}

unsigned int kheap_virtual_address(unsigned int physical_address)
{
	 if(0){
				            	int n1;
				            	int n2;
				            	int n3;
				            	}
uint32 address = to_frame_info(physical_address)->va;
if(0){
			            	int c;
			            	int k;
			            	int l;
			            	}
	              if (address) {
return address + (physical_address & 0xFFF);
	} else {
	                      return 0;
	}
	              if(0){
	             			            	int c2;
	             			            	int k2;
	             			            	int l2;
	             			            	}
}

//=================================================================================//
//============================== BONUS FUNCTION ===================================//
//=================================================================================//
// krealloc():

//	Attempts to resize the allocated space at "virtual_address" to "new_size" bytes,
//	possibly moving it in the heap.
//	If successful, returns the new virtual_address, if moved to another loc: the old virtual_address must no longer be accessed.
//	On failure, returns a null pointer, and the old virtual_address remains valid.

//	A call with virtual_address = null is equivalent to kmalloc().
//	A call with new_size = zero is equivalent to kfree().

void *krealloc(void *virtual_address, uint32 new_size)
{
	//TODO: [PROJECT'24.MS2 - BONUS#1] [1] KERNEL HEAP - krealloc
	// Write your code here, remove the panic and write your code
	//panic("krealloc() is not implemented yet...!!");
	                   uint32 szofmeta = 2 *sizeof(uint32);
	                   if(0){
	                  			            	int c;
	                  			            	int k;
	                  			            	int l;
	                  			            	}
	if (!virtual_address)
			               return kmalloc(new_size);
	 if(0){
				            	int ss;
				            	int ks;
				            	int lk;
				            	}

		if (!new_size)
			             return kfree(virtual_address), NULL;

		 if(0){
					            	int c=1;
					            	int k=100;
					            	int l=66;
					            	}
uint8 x = (uint32)virtual_address >= start && (uint32)virtual_address < segment_break, tiny = new_size <= DYN_ALLOC_MAX_BLOCK_SIZE;
                   new_size = !tiny ? ROUNDUP(new_size, PAGE_SIZE) : new_size;
if (x ^ tiny)
		{
			                void* back = kmalloc(new_size);
	if (back)
			{
			                     	uint32 sz = -1;
		if (x)
					sz = get_block_size(virtual_address);
memcpy(back, virtual_address, MIN(sz - szofmeta, new_size));
			                              	kfree(virtual_address);
			}
	 if(0){
				            	int aa=100;
				            	int awdwa=66;
				            	int kdk=5;
				            	}
return back;
		}
if (x)
		{
			                        void* back2 = realloc_block_FF(virtual_address, new_size);
			                        if(0){
			                       			            	int k=1;
			                       			            	k*=2;
			                       			            	k*=10;
			                       			            	}
			                        return (get_block_size(back2) == new_size) ? back2 : NULL;
			return NULL;
		}
uint32 appstorage = f[PDX(virtual_address)][PTX(virtual_address)], vastartspace = appstorage + gfs((uint32)virtual_address + appstorage);
if(0){
			                       			            	int k=1;
			                       			            	k*=2;
			                       			            	k*=10;
			                       			            	}
		if (new_size <= vastartspace)
		{
			 if(0){
						                       			            	int k=1;
						                       			            	k*=2;
						                       			            	k*=10;
						                       			            	}
			       void* start = virtual_address + MIN(appstorage, new_size),* end = virtual_address + MAX(appstorage, new_size);
if (new_size > appstorage)
				           for (void* va = start; va < end; va += PAGE_SIZE)
		{
					             f[PDX(va)][PTX(va)] = (int)virtual_address;
					             if(0){
					            			                       			            	int ffk=1;
					            			                       			            	ffk*=2;
					            			                       			            	ffk*=10;
					            			                       			            	}
struct FrameInfo* framedetail = NULL;
				                  	allocate_frame(&framedetail);
				                  	 if(0){
				                  				                       			            	int aak=1;
				                  				                       			            	aak*=2;
				                  				                       			            	aak*=10;
				                  				                       			            	}
	map_frame(ptr_page_directory, framedetail,(uint32) va, PERM_WRITEABLE);
				          }
else if (new_size < appstorage)
				             for (void* va = start; va < end; va += PAGE_SIZE)
				{
	f[PDX(va)][PTX(va)] = 0;
					           unmap_frame(ptr_page_directory,(uint32) va);
}
		                	f[PDX(virtual_address)][PTX(virtual_address)] = new_size;

		                	 if(0){
		                	    	int a=5;
		                			a*=2;
		                		a*=10;
		                				                       			            	}

return virtual_address;
		}
	              	else
		{
void* back3 = kmalloc(new_size);
if(0){
		                	    	int a=5;
		                			a*=2;
		                		a*=10;
		                				                       			            	}
			          if (back3)
			{
for (void* start = virtual_address, *aim = back3; start < virtual_address + appstorage; start += PAGE_SIZE, aim += PAGE_SIZE)
				         {
	if(0){
			                	    	int b=50;
			                			b*=2;
			                		b*=10;
			                				                       			            	}
uint32* table = NULL;
if(0){
			                	    	int vv=50;
			                			vv*=2;
			                		vv*=10;
			                				                       			            	}

			struct FrameInfo* ptr_frame_info = get_frame_info(ptr_page_directory,(uint32) start, &table);

			if(0){
						                	    	int avv=50;
						                			avv*=2;
						                		avv*=10;
						                				                       			            	}
					                map_frame(ptr_page_directory, ptr_frame_info, (uint32)aim, table[PTX(start)] & 0xFFF);
	}
				kfree(virtual_address);
			                      }
			return back3;
}
}
