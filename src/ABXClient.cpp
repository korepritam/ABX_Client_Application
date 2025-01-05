/*
 * ABXClient.cpp
 *
 *  Created on: 5 Jan 2025
 *      Author: pritam
 */

#include "ABXClient.h"

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

    cout << "Client Connected to ABX server with socket|IP|port:" << sockfd << server_ip << "," << port << endl;

    return true;
}

void ABXClient::close_connection()
{
    close(sockfd);
    cout << "ABX server socket closed:" << sockfd << endl;
}

bool ABXClient::send_request(Request& request)
{
    char payload[2];
    request.to_payload(payload);

    int sent = send(sockfd, payload, sizeof(payload), 0);
    if(sent < 0)
    {
        cerr << "Error: Could not send request." << endl;
        return false;
    }

    cout << "Sent request: Call Type = " << (int)request.call_type << ", Resend Seq = " << (int)request.resend_seq << endl;

    return true;
}
