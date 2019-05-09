#include "netbuffer.h"
#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

static void handle_client(int fd);

int main(int argc, char *argv[]) {
  
  if (argc != 2) {
    fprintf(stderr, "Invalid arguments. Expected: %s <port>\n", argv[0]);
    return 1;
  }
  
  run_server(argv[1], handle_client);
  
  return 0;
}

void handle_client(int fd) {
	net_buffer_t recvBuf = nb_create(fd, MAX_LINE_LENGTH);
	char buf[MAX_LINE_LENGTH + 1] = {0};
	
	send_string(fd, "Welcome to Echo Server.\r\n");
	
	int acc = 0;
	while(1){
		nb_read_line(recvBuf, buf);
		send_string(fd, buf);
		acc++;
	}
	send_string(fd, "Goodbye.\r\n");
	nb_destroy(recvBuf);
}

// void handle_client(int fd) {
//   // Creat a net buffer (fd)
// // Creates a new buffer for handling data read from a socket.
//   net_buffer_t myBuffer = nb_create(fd, MAX_LINE_LENGTH+1);
//   char myOutput[MAX_LINE_LENGTH+1];
//   int result =nb_read_line(myBuffer, myOutput);

//   println("echo: %s", myOutput);
  
//   // read from the client FD in a while loop
  
  
  
//   // TODO To be implemented
// }
