//============================================================================
// Name        : ABX_Client_Application.cpp
// Author      : Pritam Kore
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ABXClient.h"

int main()
{
	ConfigReader::getInstance("ABX_Client_Config.cfg");
	ABXClient client(ConfigReader::getInstance()->getValueString("SERVER_IP"), ConfigReader::getInstance()->getInt("SERVER_PORT"));


    if (!client.create_connection())
    {
        return EXIT_FAILURE;
    }

    int choice;
	cout << "Enter Choice : 1:callType 2:resendReq" << endl;	cin >> choice;

    if(choice == 1)
    {
		Request all_packet_request(RequestPayloadFormat::callType);
		if (client.send_request(all_packet_request)) {
			cout << "Send Request done: type " << (int)RequestPayloadFormat::callType << endl;
			client.handle_response();
		}
		else {
			cerr << "Send Request Not done: type " << (int)RequestPayloadFormat::callType << endl;
		}
    }
    else if(choice == 2)
    {
		char resend_seq;
		cout << "Enter the sequence number to resend: "; cin >> resend_seq;
		Request request(RequestPayloadFormat::resendSeq, resend_seq);
		if (client.send_request(request))
		{
			cout << "Send Request done: type " << (int)RequestPayloadFormat::resendSeq << endl;
		}
		else
		{
			cerr << "Send Request Not done: type " << (int)RequestPayloadFormat::resendSeq << endl;
		}
    }
    else
    {
    	cout << "Invalid Choice:" << choice << endl;
    }

	client.close_connection();

	return EXIT_SUCCESS;
}
