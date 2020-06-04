/*
 * Brandon Castor 817046315
 * Alexander Howes 820184866 cssc 2165
 */
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

#define NUM_THREADS 7

void *chat(void *proccid){
    long pid;
    pid = (long)proccid;
    cout << "Hello, i'm a bot #" << pid << endl;
    pthread_exit(nullptr);
}

void bots(){

    pthread_t bots[NUM_THREADS];
    int rc;

    for(int i = 0; i < NUM_THREADS; i++){
        rc = pthread_create(&bots[i], nullptr, chat, (void *)  (size_t)i);

        if (rc){
            cout << "ERROR: unable to create bot," << rc << endl;
            exit(-1);
        }
    }

    pthread_exit(nullptr);
}

int main() {


    ofstream myfile;
    myfile.open("QUOTE.txt");
    myfile << getpid() << "\n" ;
    myfile.close();

    bots();

    return 0;
}
