#pragma once

#include <stdio.h>
#include <string>
#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996) 

#define SERVER "127.0.0.1"
#define PORT 8888

namespace dnet {

	class net {
	public:
		net();

	public:
		
		static sockaddr_in server;
		static int client_socket;

		static int init();
		static int send(std::string message);
		static int end();

		static std::string err(int error);

	};

}
