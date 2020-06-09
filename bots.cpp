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

using namespace std;

#define NUM_THREADS 7
ofstream myfile;
sem_t FLAG;


void *chat(void *botid) {

    long bid;
    bid = (long)botid;
    int reps = 0;

    while( reps != 7){
        if(bid % 2 == 0){

            sem_wait(&FLAG);
            cout << "thread" << bid << " is running" << endl;
            myfile.open("QUOTE.txt");
            myfile << "bot#" << bid << " Controlling complexity is the essence of computer programming.\n\r";
            myfile.close();
            sem_post(&FLAG);
            reps++;
            sleep(2);
        }
        else{

            sem_wait(&FLAG);
            cout << "thread" << bid << " is running" << endl;
            myfile.open("QUOTE.txt");
            myfile << "bot#" << bid << " Computer science is no more about computers than astronomy is about telescopes.\n\r";
            myfile.close();
            sem_post(&FLAG);
            reps++;
            sleep(3);
        }
    }
}

int main() {

    sem_init(&FLAG,0,1);
    pthread_t bots[NUM_THREADS];
    int i;

    myfile.open("QUOTE.txt");
    myfile << getpid()  << "\n\r";
    myfile.close();

    for (i = 0; i <= NUM_THREADS; i++) {

        pthread_create(&bots[i], NULL, chat,(void *) (size_t) i);
    }

    for(i = 0; i<= NUM_THREADS; i++){
        pthread_join(bots[i],NULL);
    }

    sem_destroy(&FLAG);

    return 0;
}