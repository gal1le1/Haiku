#include "message.h"

int counter = 0;

struct message_buffer message;

int msg_id_generator(){
    int msg_id;
    key_t key;
    key = ftok("/etc/passwd", 'F');
    if(key == -1){
        perror("Key");
        exit(1);
    } 

    msg_id = msgget(key, 0666 | IPC_CREAT);

    if(msg_id == -1){
        perror("msgget");
        exit(1);
    }
    return msg_id;
}


int main(int argc, char const *argv[]){

    int msgid, random_number;
    msgid = msg_id_generator();
    
    int haiku_category[2][2];
    haiku_category[0][0] = SIGINT;
    // haiku_category[0][1] = "japanese";
    haiku_category[1][0] = SIGQUIT;
    // haiku_category[1][1] = 'western';

    while(counter < 100){
        if(msgrcv(msgid, &message, sizeof(message), 0, 0) == -1){
            perror("msgrcv");
            exit(1);
        }
        if(message.message_signal_type[0] == haiku_category[0][0]){ // japanese
            printf("Japanese\n");
        }
        else if(message.message_signal_type[0] == haiku_category[1][0]){ // western
            printf("Western\n");
        }

        counter += 1;
    }
    
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}