//
//  CommandProcessor.hpp
//  Database 1.0
//
//  Created by Saman Givian on 7/7/22.
//

#ifndef CommandProcessor_hpp
#define CommandProcessor_hpp
#include "InputProcesser.hpp"//;
#include "BPTree.hpp"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "/Users/samangivian/stdc++.h"
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

void CommandExecuter(InputProcesser:: InputBuffer* UserInput, BPTree *BPTreePtr, int * ReleationCounterPtr, record_node * RecordNodesPtr[100][100]);
std::vector<std::string> InputTokenizer(InputProcesser:: InputBuffer *user_input);
std:: vector<std::string> StringVectorizer(std::string s);
std::string AddressTokenizer(std::string s);
std::vector<std::string> SplitStringByNewLine( std::string str);
void disply_help();
#endif /* CommandProcessor_hpp */
