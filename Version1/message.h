#ifndef MESSAGE_H
#define MESSAGE_H
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

// message buffer
struct message_buffer {  
    int message_signal_type; 
};


#endif