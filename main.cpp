/*Brandon Castor 817046315 cssc 2129
 *
 * Alexander Howes 820184866 cssc 2165
 *
 */

#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>
#include <chrono>
#include <unistd.h>
#include <string>

using namespace std;

#define NUM_THREADS 7
FILE* file;
sem_t FLAG;
pthread_mutex_t lock;

void* chat(void* botid) {
    string buffer;
    int bid = *((int*)botid);
    int reps = 0;
    int i;
        string id = to_string(bid);
        if (bid % 2 == 0) {
            pthread_mutex_lock(&lock);
            sleep(2);
            sem_wait(&FLAG);
            cout << "thread" << bid << " is running" << endl;
            file = fopen("QUOTE.txt", "r+");
            while (1) {
                buffer = fgetc(file);
                if (feof(file))
                    break;
            }
            buffer.append("\nbot#");
            buffer.append(id);
            buffer.append(" Controlling complexity is the essence of computer programming.");
            char p[buffer.length()];
            for (i = 0; i < sizeof(p); i++) {
                p[i] = buffer[i];
            }
            fprintf(file, "%s", p);
            fclose(file);
            sem_post(&FLAG);
            reps++;
            pthread_mutex_unlock(&lock);
        }
        else {
            pthread_mutex_lock(&lock);
            sleep(3);
            sem_wait(&FLAG);
            cout << "thread" << bid << " is running" << endl;
            file = fopen("QUOTE.txt", "r+");
            while (1) {
                buffer = fgetc(file);
                if (feof(file))
                    break;
            }
            buffer.append("\nbot#");
            buffer.append(id);
            buffer.append(" Controlling complexity is the essence of computer programming.");
            char p[buffer.length()];
            for (i = 0; i < sizeof(p); i++) {
                p[i] = buffer[i];
            }
            fprintf(file, "%s", p);
            fclose(file);
            sem_post(&FLAG);
            reps++;
            pthread_mutex_unlock(&lock);
        }
}

int main() {
    int seven = 0;
    sem_init(&FLAG, 0, 1);
    pthread_t bots[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    int rc;
    int pid = getpid();
    file = fopen("QUOTE.txt", "w+");
    fprintf(file, "%i", pid);
    fclose(file);
    while (seven<7) {
        for (i = 0; i <= NUM_THREADS; i++) {
            thread_args[i] = i;
            pthread_create(&bots[i], NULL, chat, (void*)&thread_args[i]);
        }
        seven++;
    }
    for (i = 0; i <= NUM_THREADS; i++) {
        pthread_join(bots[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    sem_destroy(&FLAG);
    exit(0);
}