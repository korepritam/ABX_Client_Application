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
	vector<int> SEQ_VEC;

	ABXClient client(ConfigReader::getInstance()->getValueString("SERVER_IP"), ConfigReader::getInstance()->getInt("SERVER_PORT"));

    if (!client.create_connection())
    {
        return EXIT_FAILURE;
    }

    Request all_packet_request((int)RequestPayloadFormat::callType);
	if (client.send_request(all_packet_request))
	{
		cout << "Send Request done: type " << (int)RequestPayloadFormat::callType << endl;
//		client.handle_response(SEQ_VEC);
		int recv_bytes = 1;
		while(recv_bytes > 0)
			recv_bytes = client.handle_response(SEQ_VEC);
	}
	else
	{
		cerr << "Send Request Not done: type " << (int)RequestPayloadFormat::callType << endl;
	}


	cout << "Printing Seq Number:";
	for(auto &seq : SEQ_VEC) cout << seq << ",";
	cout << endl;

    if (!client.create_connection())
    {
        return EXIT_FAILURE;
    }

    int seq_counter = 1, idx_counter = 0, last_counter = SEQ_VEC.back();
    while(idx_counter < SEQ_VEC.size() && seq_counter<last_counter)
    {
    	if(SEQ_VEC[idx_counter] == seq_counter) {
    		idx_counter++;
    		seq_counter++;
    	}
    	else if(SEQ_VEC[idx_counter] > seq_counter) {
    		Request resend_request((int)RequestPayloadFormat::resendSeq, seq_counter);
    		if (client.send_request(resend_request))
    		{
    			cout << "Send Request done: type " << (int)RequestPayloadFormat::resendSeq << endl;
    			client.handle_response(SEQ_VEC);
    		}
    		else
    		{
    			cerr << "Send Request Not done: type " << (int)RequestPayloadFormat::resendSeq << endl;
    			return EXIT_FAILURE;
    		}
    		seq_counter++;
    	}
    }

    sort(SEQ_VEC.begin(),SEQ_VEC.end());
	cout << "Printing Final Seq Number:";
	for(auto &seq : SEQ_VEC) cout << seq << ",";
	cout << endl;

	client.close_connection();

	return EXIT_SUCCESS;
}
