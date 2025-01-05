/*
 * GlobalMembers.h
 *
 *  Created on: 6 Jan 2025
 *      Author: pritam
 */

#ifndef GLOBALMEMBERS_H_
#define GLOBALMEMBERS_H_

#include "ConfigReader.h"
#include "JSONWriter.h"
#include "ABXClient.h"

void InitializeGlobalMembers();
void DestroyGlobalMembers();

void PrintSeqVector();
void SortSeqVector();

JSONWriter * GetJSONWriter();
ABXClient * GetABXClient();
vector<int> &GetSeqVector();

#endif /* GLOBALMEMBERS_H_ */
