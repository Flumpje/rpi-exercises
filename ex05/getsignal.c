/******************************************************************************
 * File:         getsignal.c
 * Version:      1.0
 * Date:         2019-12-14
 * Author:       W. Meijer
 * Description:  OPS exercise 5: To send or not to send. only one gets it
 ******************************************************************************/

// include crap
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

//global stuff
char nummer = '0';

// proto
void newHandler(int sig);

// where it al happens
int main(int argc, char *argv[])
{
    struct sigaction act, oldact;
    int sig;
    
    // define shr 
    memset(&act, '\0', sizeof(act));
    act.sa_handler = newHandler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    // install SHR
    printf("%d\n",sigaction(SIGINT, &act, &oldact));
    
    //print pid
    printf("My pid is: %ld\n", (long)getpid());

    while(1)
    {
        write(1, &nummer, 1);
        sleep(1);
    }

    // restore stuff
    sigaction(SIGINT, &oldact, NULL);

    return 0;
}

// SHR newHandler
void newHandler(int sig) 
{
    printf("Signal caught: %d\n", sig);
    nummer++;
    if (nummer > '9') nummer = '0';
}