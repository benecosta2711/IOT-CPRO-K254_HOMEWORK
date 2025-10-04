#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cause_stack_overflow(int depth)
{
    char buffer[1024];
    printf("Stack depth: %d | Address: %p\n", depth, (void*)buffer);
    cause_stack_overflow(depth + 1);
}

void cause_memory_leak_and_oom()
{
    long long total_allocated_kb = 0;

    while(1)
    {
        void *buffer = malloc(1024);

        if(buffer == NULL)
        {
            printf("Total allocated: %lld KB\n", total_allocated_kb);
            break;
        }

        total_allocated_kb++;
    }    

    
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "%s <stack_overflow|memory_leak|out_of_memory>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "stack_overflow") == 0) {
        printf("Cause stack overflow...\n");
        cause_stack_overflow(0);
    } else if (strcmp(argv[1], "memory_leak") == 0 || strcmp(argv[1], "out_of_memory") == 0) {
        printf("Cause memory leak lead to out of memory...\n");
        cause_memory_leak_and_oom();
    } else {
        fprintf(stderr, "Parameter error\n");
        return 1;
    }

    return 0;
}