#include "zcash.h"

int filehex2bin(char *srcfilename , char *destfilename, int sizetoread)
{
	FILE *destfile = fopen(destfilename, "wb");
	if (destfile == NULL)
	{
		printf("Error Opening file ");
		exit(1);
	}
	FILE *srcfile = fopen(srcfilename, "rb");
	if (srcfile == NULL)
	{
		printf("Error Opening file ");
		exit(1);
	}

	
	int count, bincount;
	char cread;
	char cbin[4];
	for (count = 0; count < sizetoread; count++)
	{
		cread = fgetc(srcfile);
		hex2bin(cread, cbin);

		for (bincount = 0; bincount < 4; bincount++)
		{
			fputc(cbin[bincount], destfile);
		}
	}
	if(destfile!=NULL)
	fclose(destfile);

	if (srcfile !=  NULL)
	fclose(srcfile);
	return 0;
}