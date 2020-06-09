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
string file = "QUOTE.txt";
ofstream fout(file);
sem_t FLAG;


void *chat(void* botid) {

    int bid = *((int*) botid);
    int reps = 0;

    while( reps != 7){
        if(bid % 2 == 0){

            sleep(2);
            sem_wait(&FLAG);
            cout << "thread" << bid << " is running" << endl;
            fout.open(file.c_str());
            fout << "bot#" << bid << " Controlling complexity is the essence of computer programming.\n" << endl;
            fout.close();
            sem_post(&FLAG);
            reps++;
        }
        else{
            sleep(3);
            sem_wait(&FLAG);
            cout << "thread" << bid << " is running" << endl;
            fout.open(file.c_str());
            fout << "bot#" << bid << " Computer science is no more about computers than astronomy is about telescopes.\n" << endl;
            fout.close();
            sem_post(&FLAG);
            reps++;
        }
    }
}

int main() {

    sem_init(&FLAG,0,1);
    pthread_t bots[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    int rc;

    fout.open(file.c_str());
    fout << getpid()  << "\n" << endl;
    fout.close();

    for (i = 0; i <= NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&bots[i], NULL, chat,(void *) &thread_args[i]);
    }

    for(i = 0; i<= NUM_THREADS; i++){
        pthread_join(bots[i],NULL);
    }

    sem_destroy(&FLAG);
    exit(0);
}