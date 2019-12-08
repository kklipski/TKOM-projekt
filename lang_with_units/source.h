#pragma once

#include <fstream>
#include <iostream>

#define MAX_ID_LENGTH 31

/* how many characters can be written to a buffer by getline() 
   function used in error() method of Source class */
#define MAX_ERR_LINE_LENGTH 100	

struct TextPos	// struct for storing position in file
{
	int lN;	// line
	int cN;	// column

	TextPos(int l = 1, int c = 1);
};

class Source
{
	int errCount;
	const std::string filename;
	std::ifstream inFile;
	TextPos pos;	// position in source file (information for user)

public:
	Source(const std::string &file);
	~Source();
	void error(int errCode, const TextPos& tP, const char* genMsg = "", const char* addMsg = "");
	const TextPos& getPos() const;
	void incLine();
	int nextChar();
};