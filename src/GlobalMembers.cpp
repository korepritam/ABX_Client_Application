/*
 * GlobalMembers.cpp
 *
 *  Created on: 6 Jan 2025
 *      Author: pritam
 */

#include "GlobalMembers.h"
#include "ConfigReader.h"
#include "ABXClient.h"
#include "JSONWriter.h"

JSONWriter *JSON_Writer = nullptr;
ABXClient *client = nullptr;
vector<int> SEQ_VEC;

void InitializeGlobalMembers()
{
	ConfigReader::getInstance("ABX_Client_Config.cfg");
	JSON_Writer = new JSONWriter(ConfigReader::getInstance()->getValueString("JSON_FILENAME"));
	client = new ABXClient(ConfigReader::getInstance()->getValueString("SERVER_IP"), ConfigReader::getInstance()->getInt("SERVER_PORT"));
}

void DestroyGlobalMembers()
{
	client->close_connection();
	delete client;
	client = nullptr;

	delete JSON_Writer; JSON_Writer = nullptr;
}

void PrintSeqVector()
{
	cout << "Printing Seq Number:";
	for(auto &seq : GetSeqVector()) cout << seq << ",";
	cout << endl;
}

void SortSeqVector()
{
	sort(GetSeqVector().begin(),GetSeqVector().end());
}

JSONWriter * GetJSONWriter() 	{return JSON_Writer;}
ABXClient * GetABXClient()		{return client;}
vector<int> &GetSeqVector()		{return SEQ_VEC;}
