#include "types.h"
#include "user.h"

#define P_LOOP_CNT 0x10000000
#define C_LOOP_CNT 0x20000000


unsigned int avoid_optm = 0; // a variable used to avoid compiler optimization
void do_parent(void)
{
    unsigned int cnt = 0;
    unsigned int tmp = 0;

    while(cnt < P_LOOP_CNT)
    {
        tmp += cnt;
        cnt ++;
    }
    
    avoid_optm = tmp;
}


void do_child(void)
{
    unsigned int cnt = 0;
    unsigned int tmp = 0;

    while(cnt < C_LOOP_CNT)
    {
        tmp += cnt;
        cnt ++;
    }
    
    avoid_optm = tmp;
}

void example_test_code()
{
    int pid = 0;

    pid = fork();
    if (pid < 0)
    {
        printf(1, "fork() failed!\n");
        exit();
    }
    else if (pid == 0) // child
    {
        //sleep(100);
        do_child();
    }
    else // parent
    {
        do_parent();
        if (wait() < 0)
        {
            printf(1, "wait() failed!\n");
        }
    }
	
	printf(1, "\n");
}

int
main(int argc, char *argv[])
{
    enable_sched_trace(1);

    /* ---------------- start: add your test code ------------------- */

    example_test_code();

    /* ---------------- end: add your test code ------------------- */

    enable_sched_trace(0);
    
    exit();
}
