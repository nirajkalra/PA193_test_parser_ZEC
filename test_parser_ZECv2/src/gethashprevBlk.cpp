#include "zcash.h"

int gethashprevBlk(char *prevblkfilename,  char *hash)
{
	int bytestoread = 32;
	int fpos = 8;
	char prevblkhex[] = "prevblkhex.bin";
	filedat2hex(prevblkfilename, prevblkhex);
	FILE *prevblkfile;
	prevblkfile = fopen(prevblkhex, "r");
	if (!prevblkfile)
	{
		printf("Unable to open file!");
		return 1;
	}
	
	readfile(prevblkfile, fpos, bytestoread, BIGENDIAN, hash);

	if (prevblkfile != NULL)
		fclose(prevblkfile);

	return 0;

}