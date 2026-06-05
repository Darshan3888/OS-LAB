#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#ifdef _WIN32
#include <windows.h>
#include <process.h>

/* Minimal pthread and semaphore wrappers for Windows to allow compilation
   when native pthreads/semaphores are unavailable. */
typedef HANDLE pthread_t;

struct _thread_start {
    void *(*start_routine)(void *);
    void *arg;
};

static unsigned __stdcall _thread_func(void *v) {
    struct _thread_start *ts = (struct _thread_start *)v;
    ts->start_routine(ts->arg);
    free(ts);
    return 0;
}

int pthread_create(pthread_t *thread, const void *attr,
                   void *(*start_routine)(void *), void *arg) {
    struct _thread_start *ts = malloc(sizeof(*ts));
    if (!ts) return -1;
    ts->start_routine = start_routine;
    ts->arg = arg;
    *thread = (HANDLE)_beginthreadex(NULL, 0, _thread_func, ts, 0, NULL);
    return *thread ? 0 : -1;
}

int pthread_join(pthread_t thread, void **retval) {
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    return 0;
}

typedef HANDLE sem_t;

int sem_init(sem_t *s, int pshared, unsigned value) {
    (void)pshared;
    *s = CreateSemaphore(NULL, value, LONG_MAX, NULL);
    return *s ? 0 : -1;
}

int sem_wait(sem_t *s) {
    return WaitForSingleObject(*s, INFINITE) == WAIT_OBJECT_0 ? 0 : -1;
}

int sem_post(sem_t *s) {
    return ReleaseSemaphore(*s, 1, NULL) ? 0 : -1;
}

int sem_destroy(sem_t *s) {
    return CloseHandle(*s) ? 0 : -1;
}
#endif
#include <unistd.h>

#define N 5

sem_t chopstick[N];

void *philosopher(void *num) {

    int id = *(int *)num;

    printf("Philosopher %d is thinking\n", id);

    sleep(1);

    // Pick left chopstick
    sem_wait(&chopstick[id]);

    // Pick right chopstick
    sem_wait(&chopstick[(id + 1) % N]);

    printf("Philosopher %d is eating\n", id);

    sleep(2);

    printf("Philosopher %d has finished eating\n", id);

    // Put down left chopstick
    sem_post(&chopstick[id]);

    // Put down right chopstick
    sem_post(&chopstick[(id + 1) % N]);

    pthread_exit(NULL);
}

int main() {

    pthread_t ph[N];
    int i, id[N];

    // Initialize semaphores
    for(i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    // Create philosopher threads
    for(i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &id[i]);
    }

    // Wait for all philosophers
    for(i = 0; i < N; i++) {
        pthread_join(ph[i], NULL);
    }

    // Destroy semaphores
    for(i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}
