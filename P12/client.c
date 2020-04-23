/*
  Author: Cesar Francisco Barraza Aguilar
  ID: A01176786
  Date: 14/Apr/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

/*
  error
  Helper for printing an error and exiting.
  @param msg Message to display before exiting.
*/
void error(const char* msg) {
  perror(msg);
  exit(0);
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  int sockfd = 0, portno = 0;
  struct sockaddr_in serv_addr;
  struct hostent* server;
  char buffer[256];

  // make sure we have correct number of arguments
  if (argc < 3) {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }

  // attempt to create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }

  // start server setup for connection
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }

  // make sure server address is cleared
  bzero((char*)&serv_addr, sizeof(serv_addr));

  // set server socket family the same as client socket
  serv_addr.sin_family = AF_INET;

  // copy the address from the server into the serv_addr structure
  bcopy(
    (char*)server->h_addr, 
    (char*)&serv_addr.sin_addr.s_addr,
    server->h_length
  );
  
  // convert port to the appropriate format
  portno = atoi(argv[2]);
  serv_addr.sin_port = htons(portno);

  // attempt connection to the server
  if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR connecting");
  }

  // ask user to input messae
  printf("Please enter the message: ");

  // clear message buffer
  bzero(buffer,256);

  // get message from input console
  fgets(buffer,255,stdin);

  // attempt to write the message bytes into the client socket
  if (write(sockfd, buffer, strlen(buffer)) < 0) {
    error("ERROR writing to socket"); 
  }

  // clear buffer before reading response
  bzero(buffer, 256);

  // wait until server responds
  if (read(sockfd, buffer, 255) < 0) {
    error("ERROR reading from socket");
  }

  // print message to console and close socket
  printf("%s\n", buffer);
  close(sockfd);
  return 0;
}
