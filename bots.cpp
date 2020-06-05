/*
 * Brandon Castor 817046315 cssc 2129
 * Alexander Howes 820184866 cssc 2165
 */
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 7
//makes the bot send a message and display its id
void *chat(void *botid){
    long bid;
    bid = (long)botid;
    cout << "Hello, i'm a bot #" << bid << endl;
    pthread_exit(NULL);
}

int main() {


    ofstream myfile;
    myfile.open("QUOTE.txt");
    myfile << getpid() << "\n";
    myfile.close();

    pthread_t bots[NUM_THREADS];
    int rc;
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        cout << "creating bot# " << i << endl;
        //creates a thread called bot and displays a message upon creation
        rc = pthread_create(&bots[i], NULL, chat, (void *) (size_t) i);

        if (rc) {
            cout << "ERROR: unable to create bot," << rc << endl;
            exit(-1);
        }
    }

    pthread_exit(NULL);
}
