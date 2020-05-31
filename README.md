# Haiku
## Introduction
The main goal of this project is to write a program that generates ”Haiku”
poems. Haiku is a specific type of Japanese poem which has 17 syllables divided
into three lines of 5, 7 and 5 syllables. Haiku is typically written on the subject
of nature. The word haiku (pronounced hahy-koo) is derived from the Japanese
word hokku meaning starting verse.

## Version 1
There are 2 dedicated programs (client.c and server.c) and 1 header file (mes-
sage.h) for version 1. Client must send signals (SIGINT and SIGQUIT) to
server, server has to receive the signal and print the type of poem for each sig-
nal (japanese for SIGINT and western for SIGQUIT).
Message queues used to send signal from client to server. There is message id generator()
function used in both programs to create and access the queue. Additionally,
there is message buffer structure in both programs which contains message type
and message signal type variables.
In client.c, there is sig handler() function , which receives signal, initialises the
received signal to message signal type and sends it to the message queue and
increments the global variable counter by one. This process takes place until
counter is equal to 100, after, program stops running.
In server.c, queue is accessed with the help of msg id generator() function.
There is 2D array haiku category which contains SIGINT and SIGQUIT on
itself. Server receives signal from queue using msgrcv() system call. When re-
ceived signal is equal to haiku category[0][0] (means SIGINT signal), it prints
”japanese” type, when it’s equal to haiku category[1][0] (means SIGQUIT sig-
nal), it prints ”western” type, after, the global variable counter is incremented
by one. This process takes place until counter is equal to 100 and then program
stops running.
#### Compiling
```bash
Compile client.c: gcc client.c -o client
Compile server.c: gcc server.c -o server
Execute client: ./client
Execute server: ./server
```

## Version 2

There are 2 dedicated programs (writer.c and reader.c) and 1 header file (mes-
sage.h) for version 2. Additionally, there 2 directories (japanese and western)
that contain .txt files and there is 1 haiku poem for each file. Writer must take
the poems from these 2 directories and sent them to reader via message queue.
Reader must take all the poems from queue and write 3 random poems to .txt
files for each category.
Message queues used to send data from writer to reader. There is msg id generator()
function used in both programs to create and access the queue. There is also
message buffer structure in message.h (message.h is included in both programs)
which contains message type and haiku array.
In writer.c, 2 message buffer structures are declared (message jap, message western).
There is haiku to arr() function which receives pointer to message buffer struc-
ture and type of message as an parameter. There is haikuAmount integer de-
clared inside this function() that holds the number of haiku based on category of
haiku. If arguments of this function are structure message jap and type 1, func-
tion enters the japanese directory, takes all the poems from .txt files inside that
directory and writes to message-> haiku array and if arguments are structure
message western and type 2, function enters the western directory, takes all the
poems from .txt files inside that directory and writes to message-> haiku array.
In main() function, this function is called twice (for japanese and western). It
means both structures are full now with its poems. So, all the data are sent to
the same queue with the help of msgsnd() system call.
In reader.c, 2 message buffer structures are declared (message jap and mes-
sage western). There is read haiku() function which receives haiku category as
parameter. If category is 1, it receives the data of message jap structure from
the queue, generates 3 different random haikus using generate random number()
function and writes them to the ”japanese.txt” file. Same when category is 2,
it receives the data of message western structure from the queue, generates 3
different random haikus using generate random number() function and writes
them to the ”western.txt” file. If there is no such .txt files, it will automatically
create it. In main() function, this function is called twice (category 1, category 2). 
When the work is completed, queue is emptied using msgctl() system call.

#### Compiling
```bash
Compile writer.c: gcc writer.c -o writer
Compile reader.c: gcc reader.c -o reader
Execute writer: ./writer
Execute reader: ./reader
```

## Version 3
In version 3 our previous 2 versions are combined into 1 version. In this
version, the main point is to print a haiku of a given type when the matching
signal is received. As in version 1, the client program stays the same. But on
the server, there are some changes. In version3 two different message-ids are
used by the server. The first one is used to communicate with the client and
the second one is used to send haikus that read from .txt file to reader program.
Then in the main function haikus are read from the text files into the array.
After these arrays are sent to reader program over second message-id. Inside 
the while function server just waits for and respond from the client and accord-
ing to the response’s category, it calls read haiku(int category) method. Inside
read haiku() method it reads the message queue according to its category and
prints 3 randomly chosen haiku then prints them to terminal.

#### Compiling
```bash
Compile writer.c: gcc client.c -o client
Compile reader.c: gcc server.c message.c reader.c writer.c -o server
Execute client: ./client
Execute server: ./server
```
