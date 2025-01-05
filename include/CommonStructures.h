/*
 * CommonStructures.h
 *
 *  Created on: 5 Jan 2025
 *      Author: pritam
 */

#ifndef COMMONSTRUCTURES_H_
#define COMMONSTRUCTURES_H_

#include "ConfigReader.h"

enum RequestPayloadFormat
{
	callType=1,
	resendSeq=2
};

class Packet
{
	public:
		string symbol;
		char buy_sell_indicator;
		int quantity;
		int price;
		int packet_seq;

		Packet(const uint8_t* data)
		{
			symbol = string(reinterpret_cast<const char*>(data), 4);
			buy_sell_indicator = data[4];
			quantity = ntohl(*reinterpret_cast<const int*>(&data[5]));
			price = ntohl(*reinterpret_cast<const int*>(&data[9]));
			packet_seq = ntohl(*reinterpret_cast<const int*>(&data[13]));
		}

		void print()
		{
			string side = (buy_sell_indicator == 'B') ? "Buy" : (buy_sell_indicator == 'S') ? "Sell" : "Unknown";
			cout << "Packet: Symbol = " << symbol << ", Side = " << side
				 << ", Quantity = " << quantity << ", Price = " << price
				 << ", Sequence = " << packet_seq << endl;
		}
};

class Request
{
	public:
		char call_type;
		char resend_seq;

		Request(char call_type, char resend_seq = 0) : call_type(call_type), resend_seq(resend_seq) {}

		//Convert the request into a binary payload
		void to_payload(char* payload)
		{
			payload[0] = call_type;
			payload[1] = resend_seq;
		}
};

#endif /* COMMONSTRUCTURES_H_ */
