#include "hxd.h"

auto main(int argc, char* argv[]) -> int
{
	hxd* DoHxD = new hxd();
	DoHxD->Init(argc, argv[1]);

	return 0;
}