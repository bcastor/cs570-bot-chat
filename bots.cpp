/*Brandon Castor 817046315 cssc 2129
 *
 * Alexander Howes 820184866 cssc 2165
 *
 */

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <semaphore.h>
#include <chrono>
#include <unistd.h>
#include <string>


using namespace std;

#define NUM_THREADS 7
FILE* file;
sem_t FLAG;


void *chat(void *botid) {
    string buffer;
    int bid = *((int*)botid);
    string id = to_string(bid);
    int reps = 0;

    while( reps != 8){
        if(bid % 2 == 0){

            sleep(2);
            sem_wait(&FLAG);
            cout << "thread" << bid << " is running..." << endl;
            file = fopen("QUOTE.txt", "r+");
            while (1){

                if (feof(file)){
                    break;
                }
                buffer = fgetc(file);
            }
            buffer.append("Bot#");
            buffer.append(id);
            buffer.append(": Controlling complexity is the essence of computer programming.");

            char p[buffer.length()];
            for (int i = 0; i < buffer.length(); i++){
                p[i] = buffer[i];
            }
            fprintf(file, "%s\n", p);
            fclose(file);
            sem_post(&FLAG);
            reps++;
        }
        else{
            sleep(3);
            sem_wait(&FLAG);
            cout << "thread" << bid << " is running..." << endl;
            file = fopen("QUOTE.txt", "r+");
            while (1){
                buffer = fgetc(file);
                if (feof(file))
                    break;
            }
            buffer.append("Bot#");
            buffer.append(id);
            buffer.append(": Computer science is no more about computers than astronomy is about telescopes.");

            char p[buffer.length()];
            for (int i = 0; i < buffer.length(); i++){
                p[i] = buffer[i];
            }
            fprintf(file, "%s\n", p);
            fclose(file);
            sem_post(&FLAG);
            reps++;
        }
    }
}

int main() {

    sem_init(&FLAG, 0, 1);
    int thread_args[NUM_THREADS];
    pthread_t bots[NUM_THREADS];
    int i;
    int pid = getpid();

    file = fopen("QUOTE.txt", "w+");
    fprintf(file, "%i\n", pid);
    fclose(file);

    for (i = 0; i <= NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&bots[i], NULL, chat, (void *) &thread_args[i]);
    }

    for (i = 0; i <= NUM_THREADS; i++) {
        pthread_join(bots[i], NULL);
    }

    sem_destroy(&FLAG);

    cout << "Chat terminated..." << endl;
    exit(0);
}