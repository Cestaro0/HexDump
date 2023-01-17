#pragma once
#include <iostream>
#include <fstream>

#define MIN_CHARACTER ' '
#define MAX_CHARACTER '~'
#define NULL_CHARACTER '.'
#define SPACE " "
#define NULL_TERMINATOR '\0'

class hxd
{
public:
	auto Init(int NumberOfArguments, char* FileRawData) -> void;

private:
	auto GetFileSize(std::ifstream& File) -> int;
	auto DumpHex(const void* FileRawData, int SizeOfFile) -> void;
	//auto HexDumpLine(const void* FileRawData, int size) -> void; -> implementar futuramente
	auto WriteHeader() -> void;
	auto GetAsciiVisualization(unsigned char FileRawData) -> char;
};

