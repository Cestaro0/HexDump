#include "hxd.h"

auto hxd::Init(int NumberOfArguments, char* FileRawData) -> void
{
	if (NumberOfArguments < 2)
	{
		printf("Erro: Considere usar o exemplo: HDump.exe Arquivo.exe\n");
	}

	std::ifstream File(FileRawData, std::ios::binary);

	if (File.fail())
	{
		printf("Erro: O arquivo falhou ao abrir\n");
	}

	int SizeOfFile = GetFileSize(File);
	char* BinaryFile = reinterpret_cast<char*>(malloc(SizeOfFile * sizeof(char)));

	if (!File.read(BinaryFile, SizeOfFile))
	{
		printf("Erro: Nao foi possivel ler os dados");
	}

	DumpHex(BinaryFile, SizeOfFile);
}

auto hxd::DumpHex(const void* FileRawData, size_t SizeOfFile) -> void
{
	char AsciiVisualization[17];
	size_t i, j;
	AsciiVisualization[16] = '\0';

	for (i = 0; i < SizeOfFile; ++i)
	{
		printf("%02X ", ((unsigned char*)FileRawData)[i]);

		if (((unsigned char*)FileRawData)[i] >= ' ' && ((unsigned char*)FileRawData)[i] <= '~')
		{
			AsciiVisualization[i % 16] = ((unsigned char*)FileRawData)[i];
		}
		else
		{
			AsciiVisualization[i % 16] = '.';
		}

		if ((i + 1) % 8 == 0 || (i + 1) == SizeOfFile)
		{
			printf(" ");
			if ((i + 1) % 16 == 0)
			{
				printf("|  %s \n", AsciiVisualization);
			}
			else if (i + 1 == SizeOfFile)
			{
				AsciiVisualization[(i + 1) % 16] = '\0';
				if ((i + 1) % 16 <= 8)
				{
					printf(" ");
				}
				for (j = (i + 1) % 16; j < 16; ++j)
				{
					printf("   ");
				}
				printf("|  %s \n", AsciiVisualization);
			}
		}
	}
}

auto hxd::GetFileSize(std::ifstream& File) -> int
{
	File.seekg(0, std::ios::end);

	int sizeFile = static_cast<int>(File.tellg());

	File.seekg(0, std::ios::beg);

	return sizeFile;
}