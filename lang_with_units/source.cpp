#include "source.h"

TextPos::TextPos(int l, int c):lN(l), cN(c) 
{

}

Source::Source(const std::string& file):filename(file)
{
	inFile.open(filename);

	if (!inFile)
	{
		std::cout << "Language with units: FATAL ERROR - can't open file \"" << file << "\"\n";
		exit(1);
	}

	std::cout << "Language with units compiler\n";
	std::cout << "Compile report for file: \"" << file << "\"\n\n";
	errCount = 0;
	nextChar();
}

Source::~Source()
{
	std::cout << "Language with units: end of report. Errors found: " << errCount << '\n';
	inFile.close();
}

void Source::error(int ec, const TextPos& tp, const char* mt, const char* at)
{
	errCount++;
	/* char array for storing line with error (max MAX_LENGHT_OF_ERR_LINE 
	   characters) returned by getline() */
	char errLine[MAX_ERR_LINE_LENGTH + 1];
	int currPos = inFile.tellg();
	// move to the beginning of the line (column numeration starts with 1)
	inFile.seekg(currPos - pos.cN + 1);
	inFile.getline(errLine, MAX_ERR_LINE_LENGTH + 1);
	inFile.seekg(currPos);	// return to initial position
	std::cout << "(Line: " << tp.lN << ", column: " << tp.cN << ") ERROR ";
		std::cout << ec << ": " << mt << at << std::endl;
	std::cout << '\t' << errLine << std::endl << std::endl;
}

const TextPos& Source::getPos() const 
{ 
	// we want a start position of atom, that's why 'pos.cN - 1' is used
	static TextPos tempTextPos;
	tempTextPos.lN = pos.lN;
	tempTextPos.cN = pos.cN - 1;
	return tempTextPos; 
}

void Source::incLine()
{
	pos.lN++;
	pos.cN = 1;
}

int Source::nextChar()
{
	pos.cN++;
	return inFile.get();
}