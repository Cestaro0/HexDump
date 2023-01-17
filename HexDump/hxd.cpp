#include "hxd.h"

auto hxd::Init(int NumberOfArguments, char* FilePath) -> void
{
	if (NumberOfArguments < 2)
	{
		printf("Erro: Considere usar o exemplo: HexDump.exe Arquivo.exe\n");
	}

	std::ifstream File(FilePath, std::ios::binary);

	if (File.fail())
	{
		printf("Erro: O arquivo falhou ao abrir\n");
	}

	int SizeOfFile = GetFileSize(File);
	char* FileRawData = reinterpret_cast<char*>(malloc(SizeOfFile * sizeof(char)));

	if (!File.read(FileRawData, SizeOfFile))
	{
		printf("Erro: Nao foi possivel ler os dados\n");
	}

	DumpHex(FileRawData, SizeOfFile);
}

auto hxd::GetFileSize(std::ifstream& File) -> int
{
	File.seekg(0, std::ios::end);

	int sizeFile = static_cast<int>(File.tellg());

	File.seekg(0, std::ios::beg);

	return sizeFile;
}

auto hxd::DumpHex(const void* FileRawData, int SizeOfFile) -> void
{
	char AsciiVisualization[17];
	AsciiVisualization[16] = '\0';

	int offset = 0;

	for (int i = 0; i < SizeOfFile; i++)
	{
		offset = i + 1;

		if (i == 0)
		{
			WriteHeader();	//gambiarra :P
			printf("%08X  |  ", i);
		}

		printf("%02X ", ((unsigned char*)FileRawData)[i]);

		AsciiVisualization[i % 16] = GetAsciiVisualization(((unsigned char*)FileRawData)[i]);

		if (offset % 8 == 0)
		{
			printf(SPACE);
		}

		if (offset % 16 == 0)
		{
			printf("|  %s \n", AsciiVisualization);

			if (offset < SizeOfFile)
			{
				printf("%08X  |  ", offset);
			}
		}
	}
}

/*auto hxd::HexDumpLine(const void* FileRawData, int size) -> void
{
	char AsciiVisualization[17] = { 0 };
	AsciiVisualization[16] = NULL_TERMINATOR;

	int offset = 0;

	for (int i = 0; i < size; i++)
	{
		offset = i + 1;

		if (i == 0)
		{
			WriteHeader();	//gambiarra :P
			printf("%08X  |  ", i);
		}

		printf("%02X ", ((unsigned char*)FileRawData)[i]);

		AsciiVisualization[i % 16] = GetAsciiVisualization(((unsigned char*)FileRawData)[i]);
		
		if (offset % 8 == 0)
		{
			printf(SPACE);
		}

		if (offset % 16 == 0)
		{
			printf("|  %s \n", AsciiVisualization);
			
			if (offset < size)
			{
				printf("%08X  |  ", offset);
			}
		}
	}
} -> implementar futuramente*/


auto hxd::WriteHeader() -> void			
{
	printf("\nOffset h");
	printf("     ");

	for (int i = 0; i < 16; i++)
	{
		printf("%02X ", i);
		if ((i + 1) % 8 == 0)
		{
			printf(SPACE);
		}
	}

	printf("   ");
	
	for (int i = 0; i < 16; i++)
	{
		printf("%X", i);
	}

	printf("\n\n");
}

auto hxd::GetAsciiVisualization(unsigned char FileRawData) -> char
{
	char HexToAscii = NULL_CHARACTER;

	if (((unsigned char)FileRawData) >= MIN_CHARACTER && ((unsigned char)FileRawData) <= MAX_CHARACTER)
	{
		HexToAscii = ((unsigned char)FileRawData);
	}

	return HexToAscii;
}