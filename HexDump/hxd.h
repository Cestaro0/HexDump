#pragma once
#include <iostream>
#include <fstream>

class hxd
{
public:
	auto Init(int NumberOfArguments, char* FileRawData) -> void;

private:
	auto GetFileSize(std::ifstream& File) -> int;
	auto DumpHex(const void* FileRawData, size_t SizeOfFile) -> void;
};

