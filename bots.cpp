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
FILE* file;
sem_t FLAG;


void *chat(void *botid) {
    string buffer;
    long bid;
    bid = (long)botid;
    string id = to_string(bid);
    int reps = 0;

    while( reps != 8){
        if(bid % 2 == 0){

            sem_wait(&FLAG);
            cout << "thread" << bid << " is running" << endl;
            file = fopen("QUOTE.txt", "r+");
            while (1){
                buffer = fgetc(file);
                if (feof(file))
                    break;
            }
            buffer.append("\nbot#");
            buffer.append(id);
            buffer.append(" Controlling complexity is the essence of computer programming.\n\r");

            char p[buffer.length()];
            for (int i = 0; i < sizeof(p); i++){
                p[i] = buffer[i];
            }
            fprintf(file, "%s", p);
            fclose(file);
            sem_post(&FLAG);
            reps++;
            sleep(2);
        }
        else{

            sem_wait(&FLAG);
            cout << "thread" << bid << " is running" << endl;
            file = fopen("QUOTE.txt", "r+");
            while (1){
                buffer = fgetc(file);
                if (feof(file))
                    break;
            }
            buffer.append("\nbot#");
            buffer.append(id);
            buffer.append(" Computer science is no more about computers than astronomy is about telescopes.\n\r");

            char p[buffer.length()];
            for (int i = 0; i < sizeof(p); i++){
                p[i] = buffer[i];
            }
            fprintf(file, "%s", p);
            fclose(file);
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
    int pid = getpid();

    file = fopen("QUOTE.txt", "w+");
    fprintf(file, "%i",pid);
    fclose(file);

    for (i = 0; i <= NUM_THREADS; i++) {

        pthread_create(&bots[i], NULL, chat,(void *) (size_t) i);
    }

    for(i = 0; i<= NUM_THREADS; i++){
        pthread_join(bots[i],NULL);
    }

    sem_destroy(&FLAG);

    cout << "Chat terminated..." << endl;
    exit(0);

}