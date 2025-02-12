/*
 * ABXClient.h
 *
 *  Created on: 5 Jan 2025
 *      Author: pritam
 */

#ifndef ABXCLIENT_H_
#define ABXCLIENT_H_

#include "CommonStructures.h"

class ABXClient
{
	private:
		string server_ip;
		int port;
		int sockfd;

	public:
		ABXClient(const std::string& server_ip, int port) : server_ip(server_ip), port(port), sockfd(-1) {}
		~ABXClient();
		bool create_connection();				// Establish the connection to the server
		void close_connection();				// Close the connection
		bool send_request(Request& request);	// Send the request to the server
		int handle_response(vector<int>& SEQ_VEC);		// Handle the response from the server
};


#endif /* ABXCLIENT_H_ */
