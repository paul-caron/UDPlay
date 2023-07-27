// UDP client instrument for CSOUND server
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// for canonical mode switch on and off
#include <termios.h>

#include <iostream>
#include <string>

#define PORT	 123
#define INSTRUMENT "2"
#define DURATION "1"

int main() {
	int sockfd;
	struct sockaddr_in	 servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	//set up terminal in non canonical mode
	struct termios oldTermios, newTermios;
	tcgetattr(0, &oldTermios);
	newTermios = oldTermios;
	newTermios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSAFLUSH, &newTermios);

        //messaging routine
	auto sendNote = [&servaddr,&sockfd](const std::string freq){
		std::string msg = "$i " INSTRUMENT " 0 " DURATION " ";
		msg = msg + freq;
		const char * msg_c = msg.c_str();
		sendto(sockfd,
			msg_c, msg.size(),
               		0, (const struct sockaddr *) &servaddr,
                       	sizeof(servaddr));
		std::cout << msg << std::endl;
	};

        //key press event loop
	char key = 0;
	while(key != 27){
		std::cin >> std::noskipws >> key;
		switch(key){
			case 'q': sendNote("130.8");break;
			case '2': sendNote("138.59");break;
			case 'w': sendNote("146.83");break;
			case '3': sendNote("155.56");break;
			case 'e': sendNote("164.81");break;
			case 'r': sendNote("174.61");break;
			case '5': sendNote("185.00");break;
			case 't': sendNote("196.00");break;
			case '6': sendNote("207.65");break;
			case 'y': sendNote("220.00");break;
			case '7': sendNote("233.08");break;
			case 'u': sendNote("246.94");break;
			case 'i': sendNote("261.63");break;
			case '9': sendNote("277.18");break;
			case 'o': sendNote("293.66");break;
			case '0': sendNote("311.13");break;
			case 'p': sendNote("329.63");break;
			case '[': sendNote("349.23");break;
			case '=': sendNote("369.99");break;
			case ']': sendNote("392.00");break;

		}
	}

	//put back the terminal in its original canonical state
	tcsetattr(0, TCSANOW, &oldTermios);

	//close the socket
	close(sockfd);
	return 0;
}
