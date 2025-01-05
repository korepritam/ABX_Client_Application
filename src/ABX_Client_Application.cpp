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

	client.close_connection();

	return EXIT_SUCCESS;
}
