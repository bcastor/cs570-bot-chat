/*Brandon Castor 817046315 cssc 2129
 *
 * Alexander Howes 820184866 cssc 2165
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "bots.h"

#define NUM_THREADS 7

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::ifstream;
using std::ofstream;
using std::ios;

sem_t FLAG;
static const string file_name = "QUOTE.txt";

/**
 * writes a message to a file managed by a semaphore
 * @param botid
 * @return
 */
void *chat(void *botid) {
    string buffer;
    int bid = *((int *) botid);
    int reps = 0;
    //repeat message 8 times
    while (reps != 8 ){
        if (bid % 2 == 0) {//message for even numbered threads


            sem_wait(&FLAG);//open semaphore
            cout << "thread" << bid << " is running..." << endl;
            ofstream file(file_name, ios::app);

            if (!file.is_open()) {
                cout << "File couldnt be opened" << endl;
                return 0;
            }

            file << "Bot#" << bid << ": \"Controlling complexity is the essence of computer programming.\" -- Brian Kernigan\r\n" <<endl;
            file.close();
            sem_post(&FLAG);//close semaphore
            reps++;
            sleep(2);
        }

        else {//message for odd number threads

            sem_wait(&FLAG);//open semaphore
            cout << "thread" << bid << " is running..." << endl;
            ofstream file(file_name, ios::app);

            if (!file.is_open()) {
                cout << "File couldnt be opened" << endl;
                return 0;
            }

            file << "Bot#" << bid << ": \"Computer science is no more about computers than astronomy is about telescopes.\" -- Edsger Dijkkstra\r\n" <<endl;
            file.close();
            sem_post(&FLAG);//close semaphore
            reps++;
            sleep(3);
        }
    }
}

int main() {
    sem_init(&FLAG, 0, 1);
    int thread_args[NUM_THREADS];
    pthread_t bots[NUM_THREADS];
    int i;
    int pid = getpid();

    ofstream file(file_name, ios::app);
    if (!file.is_open()) {
        cout << "File couldnt be opened" << endl;
        return 0;
    }

    file << pid << "\r\n"<< endl;
    file.close();
    //create and initialize threads 1 - 7
    for (i = 1; i <= NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&bots[i], nullptr, chat, (void *) &thread_args[i]);//pass id as argument for the thread
    }
    //join all the threads
    for (i = 0; i <= NUM_THREADS; i++) {
        pthread_join(bots[i], nullptr);
    }
    //destroy semaphore
    sem_destroy(&FLAG);
    //termination message
    cout << "Chat terminated..." << endl;
    return 0;
}
