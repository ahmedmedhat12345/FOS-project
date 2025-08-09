/*
 * channel.c
 *
 *  Created on: Sep 22, 2024
 *      Author: HP
 */
#include "channel.h"
#include <kern/proc/user_environment.h>
#include <kern/cpu/sched.h>
#include <inc/string.h>
#include <inc/disk.h>
struct spinlock x;
//===============================
// 1) INITIALIZE THE CHANNEL:
//===============================
// initialize its lock & queue
void init_channel(struct Channel *chan, char *name)
{
	strcpy(chan->name, name);
	init_queue(&(chan->queue));
}

//===============================
// 2) SLEEP ON A GIVEN CHANNEL:
//===============================
// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
// Ref: xv6-x86 OS code
void sleep(struct Channel *chan, struct spinlock* lk)
{
     struct Env* presentprocess = get_cpu_proc();
    if (presentprocess == 0) {
        panic(" cant sleep. cant get cur process ");
    }
    presentprocess->env_status = ENV_BLOCKED;
             presentprocess->channel = chan;
                 release_spinlock(lk);
acquire_spinlock(&ProcessQueues.qlock);
                       acquire_spinlock(&x);
enqueue(&(chan->queue), presentprocess);
                       release_spinlock(&x);
sched();
    release_spinlock(&ProcessQueues.qlock);
acquire_spinlock(lk);
}

//==================================================
// 3) WAKEUP ONE BLOCKED PROCESS ON A GIVEN CHANNEL:
//==================================================
// Wake up ONE process sleeping on chan.
// The qlock must be held.
void wakeup_one(struct Channel *chan)
{
	if (queue_size(&(chan->queue)) != 0) {
		                 acquire_spinlock(&ProcessQueues.qlock);
struct Env* wakeenv = dequeue(&(chan->queue));
		         wakeenv->env_status = ENV_READY;
wakeenv->channel = NULL;
		                      sched_insert_ready0(wakeenv);
		release_spinlock(&ProcessQueues.qlock);
	}
}

//====================================================
// 4) WAKEUP ALL BLOCKED PROCESSES ON A GIVEN CHANNEL:
//====================================================
// Wake up all processes sleeping on chan.
// The queues lock must be held.
void wakeup_all(struct Channel *chan)
{
	 for (; queue_size(&(chan->queue)) != 0; )
	    {
acquire_spinlock(&ProcessQueues.qlock);
	        struct Env* wenv = dequeue(&(chan->queue));
wenv->env_status = ENV_READY;
	        wenv->channel = NULL;
	               sched_insert_ready0(wenv);
release_spinlock(&ProcessQueues.qlock);
	    }
}
