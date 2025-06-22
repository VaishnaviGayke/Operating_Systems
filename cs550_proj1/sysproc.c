#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int forkcounter = 0;
int waitcounter = 0;
int exitcounter = 0;

int
sys_fork(void)
{
  forkcounter++;

  return fork();
}

int
sys_exit(void)
{
  exitcounter++;
  
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  waitcounter++;

  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_shutdown(void)
{
  /* Either of the following will work. Does not harm to put them together. */
  outw(0xB004, 0x0|0x2000); // working for old qemu
  outw(0x604, 0x0|0x2000); // working for newer qemu

  return 0;
  
}

int sys_get_syscall_count(int call_type){ 

    switch (argint(0, &call_type)) {
        case 0: // for fork
            return forkcounter;
        case 1: // for wait
            return waitcounter;
        case 2: // for exit
            return exitcounter;
        default:
            return -1; // for default call_type
    }

  return -1;

}

int sys_reset_syscall_count(void){


  forkcounter = 0;
  waitcounter = 0;
  exitcounter = 0;

  return 0;
}



