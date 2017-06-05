/*
 * network.c
 *
 *  Created on: June 5, 2017
 *      Author: stpalmer
 */

#include <khepera/khepera.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include <arpa/inet.h>

#define MAXDATASIZE 100 //max number of bytes obtained at once

char port[] = "22222";
int sockfd;
int arrayLen;
struct addrinfo hints, *servinfo, *p;
char s[INET6_ADDRSTRLEN];
int sockfd, numbytes;
int size;
int j = 0;

void *get_in_addr(struct sockaddr *sa){
	if (sa->sa_family == AF_INET){
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int findSockAddr(int argc, char *argv[]){
	int rv;

	if (argc != 3){
		fprintf(stderr, "usage: client hostname\n");
		exit(1);
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) !=0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return -1;
	}

	for(p = servinfo; p!= NULL; p = p->ai_next){
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
			perror("client:socket");
			continue;
		}
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1){
			close(sockfd);
			perror("client: connect");
			continue;
		}
		break;
	}

	if (p== NULL){
		fprintf(stderr, "client: failed to connect\n");
		return -2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
	printf("client: connecting to %s\n", s);
	freeaddrinfo(servinfo);
	return sockfd;
}

int get_message_size(){
	unsigned char tempBuf[255];

	int bytesRemain = 4;
	int size = 0;
	printf("starting my_recv\n");
	while (bytesRemain>0){
			int num_recv = recv(sockfd, tempBuf, 1, 0);

			if (num_recv == 0){
				printf("ERROR: Disconnected: %d\n", bytesRemain);
				return -1;//error
			}
			else{
				bytesRemain--;	//
				size = size|(tempBuf[0]<<(bytesRemain*8));
			}
	}
	printf("Size: %d\n", size);
	return size;
}

int get_message(int size, unsigned char buffer[], int buffSize){
	printf("my_read\n");
	unsigned char recvTempBuf[buffSize];

	while(j< size){
		int i = 0;
		int bytesRecved = recv(sockfd, recvTempBuf, buffSize-1, 0);

		if(bytesRecved <= 0)
			return bytesRecved;
		while(i<bytesRecved){
			buffer[j] = recvTempBuf[i];
			i++;
			j++;
		}
	}
	buffer[j+1] = '\0';
	printf("message: %s\n", buffer);
	return 0;
}



int main(int argc, char *argv[]){

	char val = 0;

	if (findSockAddr(argc, argv) < 0){
			printf("connection error\n");
			return -1;
	}
	else {
		while(1){
			int size = get_message_size();
			if(size <= 0)
				break;

			unsigned char messageBuffer[size];
			if(get_message(size, messageBuffer, size) <= 0)
				break;
			val = messageBuffer[0];

			switch(val){
				case 0:
					printf("Requesting name\n");
					break;
				case 1:
					printf("Disconnection\n");
					break;
				case 2:
					printf("Right wheel speed\n");
					break;
				case 3:
					printf("Left wheel speed\n");
					break;
			}
		}
	}
	return 0;
}
