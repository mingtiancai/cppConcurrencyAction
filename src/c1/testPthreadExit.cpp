#include <iostream>
#include <pthread.h>
#include <unistd.h>

void *process(void *data)
{
    while (1)
    {
        printf("xxx---------->I'm is Son thread...\n");
        sleep(1);
    }
}

int main()
{
    pthread_t pid;
    printf("xxx---------->%s(), line = %d\n", __FUNCTION__, __LINE__);
    pthread_create(&pid, nullptr, process, nullptr);
    pthread_detach(pid); //主进程和线程分离，子线程自行回收和释放资源
    pthread_exit(nullptr);
    return 0;
}