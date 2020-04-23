/*
  Author: Cesar Francisco Barraza Aguilar
  ID: A01176786
  Date: 14/Apr/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

/*
  error
  Helper for printing an error and exiting.
  @param msg Message to display before exiting.
*/
void error(const char *msg) {
  perror(msg);
  exit(1);
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, char** argv) {
  int sockfd = 0, newsockfd = 0, portno = 0;
  socklen_t clilen = 0;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  // make sure we have correct number of arguments
  if (argc < 2) {
    fprintf(stderr, "usage %s port\n", argv[0]);
    exit(1);
  }

  // attempt to create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }

  // make sure server address is cleared
  bzero((char*)&serv_addr, sizeof(serv_addr));

  // set up server address information
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  // attempt to bind the server address info to the socket
  if (
    bind(
      sockfd,
      (struct sockaddr*)&serv_addr,
      sizeof(serv_addr)
    ) < 0
  ) {
    error("ERROR on binding");
  }

  // start listening for connections
  listen(sockfd, 5);

  // attempt prepare socket for client connection
  clilen = sizeof(cli_addr);
  newsockfd = accept(
    sockfd, 
    (struct sockaddr*)&cli_addr, 
    &clilen
  );
  if (newsockfd < 0) {
    error("ERROR on accept");
  }

  // clear message buffer
  bzero(buffer,256);

  // attempt to read client socket stream
  if (read(newsockfd, buffer,255) < 0) { 
    error("ERROR reading from socket");
  }

  // show message from client
  printf("Here is the message: %s\n", buffer);

  // reply to client
  if (write(newsockfd, "I got your message", 18) < 0) {
    error("ERROR writing to socket");
  }

  // close client and server sockets
  close(newsockfd);
  close(sockfd);
  return 0; 
}
