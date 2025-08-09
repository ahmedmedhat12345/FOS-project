#include <inc/lib.h>

//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//

//=============================================
// [1] CHANGE THE BREAK LIMIT OF THE USER HEAP:
//=============================================

int reserved[(USER_HEAP_MAX-USER_HEAP_START)/PAGE_SIZE] = {0};

/*2023*/
void* sbrk(int increment)
{
	return (void*) sys_sbrk(increment);
}

//=================================
// [2] ALLOCATE SPACE IN USER HEAP:
//=================================
void* malloc(uint32 size)
{
	if (size == 0) return NULL;
	int x=9;
	int y=10;
	void* taken = NULL; int index;
	    struct Env* nowenv = 0;
	    int x11=9;
	    	int y22=10;
	    if (size <= DYN_ALLOC_MAX_BLOCK_SIZE) {
	        return alloc_block_FF(size);
	    } else {
	    	int x1133=9;
	    		    	int y223=10;
int exploredpagescount = 0;
uint32 address = 0;
int bb=9;
	    		    	int aa=10;
	        int pgscount = ROUNDUP(size, PAGE_SIZE) / PAGE_SIZE;
	        if (sys_isUHeapPlacementStrategyFIRSTFIT() > 0) {
	                                       size = ROUNDUP(size, PAGE_SIZE);
	                                       if(0){
	                                       			int a=1;
	                                       			int d =2;
	                                       			int km=3;
	                                       		}


 uint32 p = myEnv->hard_limit + PAGE_SIZE;
	                               while (p < USER_HEAP_MAX) {
 index = (p - USER_HEAP_START) / PAGE_SIZE;
 int kok=9;
 	    		    	int sas=10;
	                               if (reserved[index] == 0) {
	  if (exploredpagescount == 0) {
	                        address = p;
	                    }
	  int kook=9;
	   	    		    	int ll=10;
	                                  exploredpagescount++;
if (exploredpagescount == pgscount) {
	int kook3=9;
		   	    		    	int ll2=10;
	                                         taken = (void*)address;
sys_allocate_user_mem(address, size);
int cc=9;
		   	    		    	int ss=10;
	                                               index = (address - USER_HEAP_START) / PAGE_SIZE;
reserved[index] = pgscount;
	                        index++;

	                        int klkk=9;
	                        		   	    		    	int adada=10;
	                                                 int i = 0;
	   while (i < pgscount - 1) {
	                                                  reserved[index] = -1;
	     ++index;
	                            ++i;
	                            if(0){
	                            	                                       			int a1=1;
	                            	                                       			int d2 =2;
	                            	                                       			int km3=3;
	                            	                                       		}
	                        }
	                        break;
	                    }
	  } else {
	                                      address = 0;
 exploredpagescount = 0;
 if(0){
 	                                       			int a222=1;
 	                                       			int d333 =2;
 	                                       			int km999=3;
 	                                       		}
	                                        }
	                p += PAGE_SIZE;
	            }

} else {
	                                cprintf(" cant provide this placement \n");
	        }
}
	    return taken;
}

//=================================
// [3] FREE SPACE FROM USER HEAP:
//=================================
void free(void* virtual_address)
{
	//TODO: [PROJECT'24.MS2 - #14] [3] USER HEAP [USER SIDE] - free()
	// Write your code here, remove the panic and write your code
	//panic("free() is not implemented yet...!!");
	                             uint32 address = (uint32) virtual_address;
	                             int kok=1;
	                             kok*=2;
if(address >= USER_HEAP_START && address< myEnv->hard_limit)
	               	{
	int kss=1;
		                             kss*=2;
			free_block(virtual_address);
		}

		                else if(address >=(myEnv->hard_limit + PAGE_SIZE) && address<USER_HEAP_MAX)
{
		                	int aaa=1;
		                		                             aaa*=2;
			                 address=ROUNDDOWN(address,PAGE_SIZE);
uint32 rank =((address-USER_HEAP_START)/PAGE_SIZE);
int bbb=1;
		                		                             bbb*=2;
					int number = reserved[rank];
					                       uint32 filledspace= (uint32)number*PAGE_SIZE;
					                       int ccc=1;
					                       		                		                             ccc*=2;
					int i = 0;
					while (i < number) {
					                    reserved[rank] = 0;
					                    int vvv=1;
					                    		                		                             vvv*=2;
	++rank;
					    ++i;
					}
					  int ssss=1;
										                    		                		                             ssss*=2;
					                           sys_free_user_mem(address,filledspace);
	    }
		else {
			  int a1=1;
								                    		                		                             a1*=2;
		                       panic(" wrong address ");
		}
}


//=================================
// [4] ALLOCATE SHARED VARIABLE:
//=================================
void* smalloc(char *sharedVarName, uint32 size, uint8 isWritable) {
    if (size == 0) return NULL;
    uint32 address = 0;
                                   int pgscnt = ROUNDUP(size, PAGE_SIZE) / PAGE_SIZE;
    int exploredpgscount = 0;

                                      int rank;
   	     void* filled = NULL;
   	    	     uint32 x = USER_HEAP_MAX - (myEnv->hard_limit + PAGE_SIZE);
   	       	    	                    if( ROUNDUP(size, PAGE_SIZE)>= x){
   	       	    	    	            	return NULL;
   	       	    	    	            }
   	       	   size = ROUNDUP(size, PAGE_SIZE);
   	       	                           uint32 p = myEnv->hard_limit + PAGE_SIZE;
while (p < USER_HEAP_MAX) {
   	                            	rank = (p - USER_HEAP_START) / PAGE_SIZE;
 if (reserved[rank] == 0) {
   	                   if (exploredpgscount == 0) {
    address = p;
                                           	       	        }
 exploredpgscount++;
                        	       	        if (exploredpgscount == pgscnt) {
     filled = (void*)address;
   	                                  	            sys_allocate_user_mem(address, size);
   	       	      rank = (address - USER_HEAP_START) / PAGE_SIZE;
   	       	                         reserved[rank] = pgscnt;
   	       	      rank++;
   	       	int i = 0;
   	       	while (i < pgscnt - 1) {
   	       	                         reserved[rank] = -1;
   	   ++rank;
   	                           	    ++i;
   	       	}
   	       	                            break;
   	       	        }
   	       	    } else {
   address = 0;
                    	       	  exploredpgscount = 0;
   	       	    }
   	       	    p += PAGE_SIZE;
}
            	        if(sys_createSharedObject(sharedVarName,size,isWritable,filled)<0)
   	        {
   	                            	return NULL;
   	        }
   	                          return filled;
   	    }






//========================================
// [5] SHARE ON ALLOCATED SHARED VARIABLE:
//========================================
void* sget(int32 ownerEnvID, char *sharedVarName)
{
	//TODO: [PROJECT'24.MS2 - #20] [4] SHARED MEMORY [USER SIDE] - sget()
	// Write your code here, remove the panic and write your code
	//panic("sget() is not implemented yet...!!");
	int size = sys_getSizeOfSharedObject(ownerEnvID,sharedVarName);
	if (size < 0){
		return 	NULL;
	}
	                          int pgscount = ROUNDUP(size, PAGE_SIZE) / PAGE_SIZE;
    uint32 address = 0;
                                                	 int exploredpgscount = 0;
	                                       int rank;

	   	                                 void* filled = NULL;
if (sys_isUHeapPlacementStrategyFIRSTFIT() > 0) {
	                                	            size = ROUNDUP(size, PAGE_SIZE);
	                                	           uint32 p = sys_get_hard_limit() + PAGE_SIZE;
while (p < USER_HEAP_MAX) {
	   	                          rank = (p - USER_HEAP_START) / PAGE_SIZE;
	   	                                     if (reserved[rank] == 0) {
	   	     if (exploredpgscount == 0) {
	   	                                            address = p;
	   	                                       }
	                      exploredpgscount++;
if (exploredpgscount == pgscount) {
	   	                                       filled = (void*)address;
	   	    sys_allocate_user_mem(address, size);
	   	                                                  rank = (address - USER_HEAP_START) / PAGE_SIZE;
	  reserved[rank] = pgscount;
	   	                                    rank++;
	   	    int i = 0;
	   	                                  while (i < pgscount - 1) {
	   	                                	  reserved[rank] = -1;
	   	        ++rank;
	   	                                         ++i;
	   	   }
	   	                     break;
	   	                 }
	   	             } else {
	   	                                         address = 0;   exploredpgscount = 0;
	   	             }
	   	             p += PAGE_SIZE;
	   	         }
} else {
	   	                                     cprintf("  cant provide this placement \n");
	   	        }

	   	                              if(sys_getSharedObject(ownerEnvID,sharedVarName,filled) < 0)
	   	       	        {
	  	return NULL;
	   	       	        }

	   	       	     return filled;
}


//==================================================================================//
//============================== BONUS FUNCTIONS ===================================//
//==================================================================================//

//=================================
// FREE SHARED VARIABLE:
//=================================
//	This function frees the shared variable at the given virtual_address
//	To do this, we need to switch to the kernel, free the pages AND "EMPTY" PAGE TABLES
//	from main memory then switch back to the user again.
//
//	use sys_freeSharedObject(...); which switches to the kernel mode,
//	calls freeSharedObject(...) in "shared_memory_manager.c", then switch back to the user mode here
//	the freeSharedObject() function is empty, make sure to implement it.

void sfree(void* virtual_address)
{
	//TODO: [PROJECT'24.MS2 - BONUS#4] [4] SHARED MEMORY [USER SIDE] - sfree()
	// Write your code here, remove the panic and write your code
	panic("sfree() is not implemented yet...!!");
}


//=================================
// REALLOC USER SPACE:
//=================================
//	Attempts to resize the allocated space at "virtual_address" to "new_size" bytes,
//	possibly moving it in the heap.
//	If successful, returns the new virtual_address, in which case the old virtual_address must no longer be accessed.
//	On failure, returns a null pointer, and the old virtual_address remains valid.

//	A call with virtual_address = null is equivalent to malloc().
//	A call with new_size = zero is equivalent to free().

//  Hint: you may need to use the sys_move_user_mem(...)
//		which switches to the kernel mode, calls move_user_mem(...)
//		in "kern/mem/chunk_operations.c", then switch back to the user mode here
//	the move_user_mem() function is empty, make sure to implement it.
void *realloc(void *virtual_address, uint32 new_size)
{
	//[PROJECT]
	// Write your code here, remove the panic and write your code
	panic("realloc() is not implemented yet...!!");
	return NULL;

}


//==================================================================================//
//========================== MODIFICATION FUNCTIONS ================================//
//==================================================================================//

void expand(uint32 newSize)
{
	panic("Not Implemented");

}
void shrink(uint32 newSize)
{
	panic("Not Implemented");

}
void freeHeap(void* virtual_address)
{
	panic("Not Implemented");

}
