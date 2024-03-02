#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <signal.h>
#include <sys/wait.h>
#include "a2_helper.h"
int ok = 0;
int ok14 = 0;
sem_t *sem_3_1, *sem_4_1, *sem6, *sem_exista;
sem_t *sem1, *sem2, *sem3, *sem4, *sem5;

void *p8(void *arg)
{
    info(BEGIN, 8, 0);
    info(END, 8, 0);
    return NULL;
}
void *p7(void *arg)
{
    info(BEGIN, 7, 0);
    info(END, 7, 0);
    return NULL;
}
void *t6(void *arg)
{
    int i = *(int *)arg;
    if (i == 14)
    {
        info(BEGIN, 6, 14);
        sem_wait(sem1);
        sem_wait(sem2);
        sem_wait(sem3);
        sem_wait(sem4);
        sem_wait(sem5);
        info(END, 6, 14);
        sem_post(sem_exista);
        sem_post(sem_exista);
        sem_post(sem_exista);
        sem_post(sem_exista);
        sem_post(sem_exista);
    }
    else if (i == 1 || i == 5 || i == 2 || i == 3 || i == 4)
    {

        info(BEGIN, 6, i);
        if (i == 1)
        {
            sem_post(sem1);
            sem_wait(sem_exista);
        }
        if (i == 2)
        {
            sem_post(sem2);
            sem_wait(sem_exista);
        }
        if (i == 3)
        {
            sem_post(sem3);
            sem_wait(sem_exista);
        }
        if (i == 4)
        {
            sem_post(sem4);
            sem_wait(sem_exista);
        }
        if (i == 5)
        {
            sem_post(sem5);
            sem_wait(sem_exista);
        }
        info(END, 6, i);
    }
    else
    {
        info(BEGIN, 6, i);
        info(END, 6, i);
    }
    return NULL;
}
void *p6(void *arg)
{
    info(BEGIN, 6, 0);
    pthread_t thr[42];
    int aux = 14, altaux = 41;
    int nrtr = 0, ok14 = 1;

    pthread_create(&thr[14], NULL, t6, (void *)&(aux));
    nrtr++;
    for (int i = 1; i <= 36; i = i + 5)
    {
        int i0 = i, i1 = i + 1, i2 = i + 2, i3 = i + 3, i4 = i + 4;
        if (i0 != 14)
        {
            pthread_create(&thr[i0], NULL, t6, (void *)&(i0));
            nrtr++;
        }
        if (i1 != 14)
        {
            pthread_create(&thr[i1], NULL, t6, (void *)&(i1));
            nrtr++;
        }
        if (i3 != 14)
        {
            pthread_create(&thr[i3], NULL, t6, (void *)&(i3));
            nrtr++;
        }
        if (i4 != 14)
        {
            pthread_create(&thr[i4], NULL, t6, (void *)&(i4));
            nrtr++;
        }
        if (i2 != 14)
        {
            pthread_create(&thr[i2], NULL, t6, (void *)&(i2));
            nrtr++;
        }

        if (i == 1 && nrtr == 6 && ok14 == 1)
        {
            //  sem_post(sem_exista);
            //  sem_wait(sem6);
            //       info(END, 6, 14);
            //       sem_post(sem_exista);
            //       sem_post(sem_exista);
            //      sem_post(sem_exista);
            //      sem_post(sem_exista);
            //       sem_post(sem_exista);
            nrtr--;
            ok14 = 0;
        }
        if (ok14 == 0)
        {
            if (i == 1)
            {
                if (i0 != 14)
                {
                    pthread_join(thr[i0], NULL);
                }
                if (i1 != 14)
                {
                    pthread_join(thr[i1], NULL);
                }
                if (i2 != 14)
                {
                    pthread_join(thr[i2], NULL);
                }
                if (i3 != 14)
                {
                    pthread_join(thr[i3], NULL);
                }
            }
            else
            {
                if (i0 != 14)
                    pthread_join(thr[i0], NULL);
                if (i1 != 14)
                    pthread_join(thr[i1], NULL);
                if (i2 != 14)
                    pthread_join(thr[i2], NULL);
                if (i3 != 14)
                    pthread_join(thr[i3], NULL);
            }
        }
    }
    pthread_create(&thr[41], NULL, t6, (void *)&(altaux));
    pthread_join(thr[41], NULL);
    info(END, 6, 0);
    return NULL;
}
void *p5(void *arg)
{
    info(BEGIN, 5, 0);

    pid_t pid8;

    pid8 = fork();
    if (pid8 == 0)
    {
        p8(NULL);
        exit(0);
    }
    waitpid(pid8, NULL, 0);

    info(END, 5, 0);
    return NULL;
}
void *t4(void *arg)
{
    int i = *(int *)arg;
    if (i == 1)
    {
        sem_wait(sem_4_1);
    }
    else
    {
        info(BEGIN, 4, i);
    }
    if (i == 3)
    {
        pthread_t thr;
        int j = 4;
        pthread_create(&thr, NULL, t4, (void *)&(j));
        pthread_join(thr, NULL);
    }
    if (i == 1)
    {
        info(BEGIN, 4, i);
        info(END, 4, i);
        sem_post(sem_3_1); 
    }
    else
        info(END, 4, i);
    return NULL;
}
void *p4(void *arg)
{
    info(BEGIN, 4, 0);

    pthread_t thr[5];
    int i = 1;
    pthread_create(&thr[1], NULL, t4, (void *)&(i));
    pthread_join(thr[1], NULL);
    ok = 1;

    i++;
    pthread_create(&thr[2], NULL, t4, (void *)&(i));
    pthread_join(thr[2], NULL);
    i++;

    pthread_create(&thr[3], NULL, t4, (void *)&(i));
    pthread_join(thr[3], NULL);

    pid_t pid5;

    pid5 = fork();
    if (pid5 == 0)
    {
        p5(NULL);
        exit(0);
    }
    waitpid(pid5, NULL, 0);
    info(END, 4, 0);
    return NULL;
}
void *t3(void *arg)
{
    int i = *(int *)arg;
    if (i == 3)
    {
        sem_wait(sem_3_1);
        info(BEGIN, 3, i);
        info(END, 3, i);
    }
    else if (i == 1)
    {
        info(BEGIN, 3, i);
        info(END, 3, i);
        sem_post(sem_4_1);
    }
    else
    {
        info(BEGIN, 3, i);
        info(END, 3, i);
    }

    return NULL;
}
void *p3(void *arg)
{
    info(BEGIN, 3, 0);

    pthread_t thr[6];
    int i = 1;
    pthread_create(&thr[1], NULL, t3, (void *)&(i));
    pthread_join(thr[1], NULL);
    i++;

    pthread_create(&thr[2], NULL, t3, (void *)&(i));
    pthread_join(thr[2], NULL);
    i++;

    pid_t pid4, pid7;

    pid4 = fork();
    if (pid4 == 0)
    {
        p4(NULL);
        exit(0);
    }

    pthread_create(&thr[3], NULL, t3, (void *)&(i));

    pthread_join(thr[3], NULL);

    i++;

    pthread_create(&thr[4], NULL, t3, (void *)&(i));
    pthread_join(thr[4], NULL);
    i++;
    pthread_create(&thr[5], NULL, t3, (void *)&(i));
    pthread_join(thr[5], NULL);
    i++;

    waitpid(pid4, NULL, 0);

    pid7 = fork();
    if (pid7 == 0)
    {
        p7(NULL);
        exit(0);
    }

    waitpid(pid7, NULL, 0);

    info(END, 3, 0);
    return NULL;
}
void *p2(void *arg)
{
    info(BEGIN, 2, 0);

    pid_t pid3;

    pid3 = fork();
    if (pid3 == 0)
    {
        p3(NULL);
        exit(0);
    }
    waitpid(pid3, NULL, 0);
    info(END, 2, 0);
    return NULL;
}
void *p1(void *arg)
{

    info(BEGIN, 1, 0);

    pid_t pid2, pid6;

    pid2 = fork();
    if (pid2 == 0)
    {
        p2(NULL);
        exit(0);
        //  printf("abcdefgh\n");
    }
    waitpid(pid2, NULL, 0);
    //  printf("sunt la waitpid2\n");

    pid6 = fork();
    if (pid6 == 0)
    {
        p6(NULL);
        exit(0);
    }
    //   printf("ies din if cu pid6\n");

    waitpid(pid6, NULL, 0);
    info(END, 1, 0);
    //  printf("sunt la waitpid6\n");
    return NULL;
    //  printf("sunt la waitpid6\n");
}
int main()
{
    init();
    sem_4_1 = sem_open("sem_4_1", O_CREAT, 0777, 0);
    sem_3_1 = sem_open("sem_3_1", O_CREAT, 0777, 0);
    sem6 = sem_open("sem6", O_CREAT, 0777, 0);
    sem1 = sem_open("sem1", O_CREAT, 0777, 0);
    sem2 = sem_open("sem2", O_CREAT, 0777, 0);
    sem3 = sem_open("sem3", O_CREAT, 0777, 0);
    sem4 = sem_open("sem4", O_CREAT, 0777, 0);
    sem5 = sem_open("sem5", O_CREAT, 0777, 0);
    sem_exista = sem_open("sem_exista", O_CREAT, 0777, 0);

    p1(NULL);

    sem_close(sem_exista);
    sem_close(sem_4_1);
    sem_close(sem_3_1);
    sem_close(sem6);
    sem_close(sem5);
    sem_close(sem4);
    sem_close(sem3);
    sem_close(sem2);
    sem_close(sem1);
    unlink("/dev/shm/sem.sem_4_1");
    unlink("/dev/shm/sem.sem_3_1");
    unlink("/dev/shm/sem.sem6");
    unlink("/dev/shm/sem.sem5");
    unlink("/dev/shm/sem.sem4");
    unlink("/dev/shm/sem.sem3");
    unlink("/dev/shm/sem.sem2");
    unlink("/dev/shm/sem.sem1");
    unlink("/dev/shm/sem.sem_exista");

    return 0;
}
// gcc -Wall a2.c a2_helper.c -o a2 -lpthread
//  ./a2
