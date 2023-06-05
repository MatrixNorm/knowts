#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void *routine()
{
    printf("process(thread) id %d, tid %ld \n", getpid(), syscall(SYS_gettid));
    sleep(60*60);
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int ret1 = pthread_create(&t1, NULL, &routine, NULL);
    int ret2 = pthread_create(&t2, NULL, &routine, NULL);
    // printf("ret1 %d\n", ret1);
    // printf("ret2 %d\n", ret2);
    printf("process id %d, tid %ld\n", getpid(), syscall(SYS_gettid));
    // XXX try without join
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}