/*
 * ABXClient.cpp
 *
 *  Created on: 5 Jan 2025
 *      Author: pritam
 */

#include "ABXClient.h"
#include "GlobalMembers.h"

ABXClient::~ABXClient()
{
    if (sockfd != -1) close(sockfd);
}

bool ABXClient::create_connection()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error: Could not create socket." << std::endl;
        return false;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        cerr << "Error: Could not connect to server." << endl;
        close(sockfd);
        return false;
    }

    cout << "Client Connected to ABX server with socket|IP|port:" << sockfd << ","<< server_ip << "," << port << endl;

    return true;
}

void ABXClient::close_connection()
{
    close(sockfd);
    cout << "ABX server socket closed:" << sockfd << endl;
}

bool ABXClient::send_request(Request& request)
{
    uint8_t payload[2];
    request.to_payload(payload);
    cout << "Sent request Payload: CallType = " << payload[0] << ", ResendSeq = " << payload[1] << endl;

    int sent = send(sockfd, payload, sizeof(payload), 0);
    if(sent < 0)
    {
        cerr << "Error: Could not send request." << endl;
        return false;
    }

//    cout << "Sent request: CallType = " << (int)request.call_type << ", ResendSeq = " << request.resend_seq_str << endl;

    return true;
}

// Handle the response from the server
int ABXClient::handle_response(vector<int>& SEQ_VEC)
{
    char buffer[1024];  // Buffer to store received data
    int received = recv(sockfd, buffer, sizeof(buffer), 0);
	if (received < 0)
	{
		cerr << "Error: Could not receive data." << endl;
//		break;
	}
	else if (received == 0)
	{
		cout << "Server closed the connection." << endl;
//		break;
	}
	else
	{
		int index = 0;
		while (index + 17 <= received)
		{
			Packet packet(&buffer[index]);
			packet.Print();
			GetJSONWriter()->WriteToJSONFile(packet);
			SEQ_VEC.push_back(packet.packet_seq);
			index += 17;
		}

	}
	return received;
}
