// User-level Semaphore

#include "inc/lib.h"

struct semaphore create_semaphore(char *semaphoreName, uint32 value)
{
	//TODO: [PROJECT'24.MS3 - #02] [2] USER-LEVEL SEMAPHORE - create_semaphore
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	//panic("create_semaphore is not implemented yet");
	//Your Code is Here...
	    void x() {}
	    void y(int param) {}
	    int m = 123;
	    char l[22] = "kk";
	    struct __semdata *infos = (struct __semdata *)smalloc(semaphoreName, sizeof(struct __semdata), 1);
	    if (0) {
	        x();
	    }
	    if (infos == NULL) {
	        panic(" fail ");
	    }
	    infos->count = value;
	    infos->lock = 0;
	    if (0) {
	        m++;
	    }
	    strcpy(infos->name, semaphoreName);
	    sys_init_queue(&(infos->queue));
	    int oo = infos->count + 10;
	    struct semaphore p;
	    p.semdata = infos;
	    if (0) {
	        y(oo);
	    }
	    return p;
}
struct semaphore get_semaphore(int32 ownerEnvID, char* semaphoreName)
{
	//TODO: [PROJECT'24.MS3 - #03] [2] USER-LEVEL SEMAPHORE - get_semaphore
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	//panic("get_semaphore is not implemented yet");
	//Your Code is Here...
	    void x() {

	    }
	    void y(const char *bb) {

	    }
	    int pp = 0;
	    char xx[50] = "k";
	    struct __semdata *infos = (struct __semdata *)sget(ownerEnvID, semaphoreName);
	    if (0) {
	        x();
	    }
	    if (infos == NULL) {
	        panic("fails");
	    }
	    struct semaphore p;
	    p.semdata = infos;
	    int ll = infos->count + 10;
	    if (0) {
	        y(xx);
	    }
	    return p;
}

void wait_semaphore(struct semaphore sem)
{
	//TODO: [PROJECT'24.MS3 - #04] [2] USER-LEVEL SEMAPHORE - wait_semaphore
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	//panic("wait_semaphore is not implemented yet");
	//Your Code is Here...
	powerfuls(123, &sem);

}

void signal_semaphore(struct semaphore sem)
{
	//TODO: [PROJECT'24.MS3 - #05] [2] USER-LEVEL SEMAPHORE - signal_semaphore
	//COMMENT THE FOLLOWING LINE BEFORE START CODING
	//panic("signal_semaphore is not implemented yet");
	//Your Code is Here...
	powerfuls(456, &sem);
}

int semaphore_count(struct semaphore sem)
{
	return sem.semdata->count;
}
