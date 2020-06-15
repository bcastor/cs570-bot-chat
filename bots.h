

#ifndef A1___570_BOTS_H
#define A1___570_BOTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 7

/**
 * Manages a thread to write to a file using a semaphore,
 * delays even thread by 2 seconds and odd threads by 3 seconds.
 * @param botid
 * @return
 */
void *chat(void *botid);



#endif //A1___570_BOTS_H
