#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock1, lock2;

void *Foo(){
    printf("[FOO] Ставим лок на lock1\n");
    pthread_mutex_lock(&lock1);
    sleep(2);
    printf("[FOO] Ставим лок на lock2\n");
    pthread_mutex_lock(&lock2); 
    printf("[FOO] Снимаем лок на lock2\n");
    pthread_mutex_unlock(&lock2);
    printf("[FOO] Снимаем лок на lock1");
    pthread_mutex_unlock(&lock1);
    pthread_exit(NULL);
}

void *Bar(){
    printf("[BAR] Ставим лок на lock2\n");
    pthread_mutex_lock(&lock2);
    sleep(2);
    printf("[BAR] Ставим лок на lock1\n");
    pthread_mutex_lock(&lock1); 
    printf("[BAR] Снимаем лок на lock1");
    pthread_mutex_unlock(&lock1);
    printf("[BAR] Ставим лок на lock2\n");
    pthread_mutex_unlock(&lock2);
    pthread_exit(NULL);
}

int main()
{
    pthread_mutex_init(&lock1,NULL);
    pthread_mutex_init(&lock2,NULL);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,Foo,NULL);
    pthread_create(&t2,NULL,Bar,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}