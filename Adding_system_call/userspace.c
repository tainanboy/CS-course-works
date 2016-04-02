#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
         long int call = syscall(354);
         printf(“System call sys_hello returned %ld\n”, call);
         return 0;
}