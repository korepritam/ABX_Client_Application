/*
 * JSONWriter.h
 *
 *  Created on: 6 Jan 2025
 *      Author: pritam
 */

#ifndef JSONWRITER_H_
#define JSONWRITER_H_

#include "CommonStructures.h"

class JSONWriter
{
	private:
		string json_filename;
		ofstream json_file;

	public:
		JSONWriter(string json_fileName_)
		{
			json_filename = json_fileName_;
			json_file.open(json_filename, std::ios::out);
		}

	    nlohmann::json ConvertToJSON(Packet packet)
	    {
	        nlohmann::json packet_json;
	        packet_json["symbol"] = packet.symbol;
	        packet_json["side"] = (packet.buy_sell_indicator == 'B') ? "Buy" : (packet.buy_sell_indicator == 'S') ? "Sell" : "Unknown";
	        packet_json["quantity"] = packet.quantity;
	        packet_json["price"] = packet.price;
	        packet_json["sequence"] = packet.packet_seq;
	        return packet_json;
	    }

        void WriteToJSONFile(Packet packet)
        {
			nlohmann::json packet_json = ConvertToJSON(packet);

			if (json_file.is_open())
			{
				json_file << packet_json.dump() << endl;
				cout << "Packet data written to " << json_filename << endl;
//				json_file.close();
			}
			else
			{
				cerr << "Error: Could not open file for writing." << endl;
			}
        }

        ~JSONWriter()
        {
        	json_file.close();
        }
};


#endif /* JSONWRITER_H_ */
