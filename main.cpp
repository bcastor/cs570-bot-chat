/*
 * Brandon Castor 817046315
 * Alexander Howes 820184866 cssc 2165
 */
#include <iostream>
#include <fstream>
#include <unistd.h>

int main() {
    ofstream myfile;
    myfile.open("QUOTE.txt");
    myfile << getpid() << "\n" ;
    myfile.close();
    return 0;
}
