
#include "syscall.h"
#include "types.h"
#include "user.h"

int main() {
    
    // To get invocation counts and verify results use get_syscall_count 
    int forkcalls = get_syscall_count(0);
    int waitcalls = get_syscall_count(1);
    int exitcalls = get_syscall_count(2);

    // Print fork, wait and exit calls
    printf(1, "Fork Calls: %d\n", forkcalls);
    printf(1, "Wait Calls: %d\n", waitcalls);
    printf(1, "Exit Calls: %d\n", exitcalls);

    return 0;
}