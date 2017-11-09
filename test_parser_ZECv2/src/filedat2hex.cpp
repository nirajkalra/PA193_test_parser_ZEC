#include "zcash.h"

int filedat2hex(char *srcfilename, char *destfilename)
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
	char c1, c2, dummy;
	while (!feof(srcfile))
	{
		dummy = 0x00;
		dummy = fgetc(srcfile);
		c1 = (dummy & 0xf0) >> 4;
		c2 = (dummy & 0x0f);
		if (c1 < 10)
			c1 = c1 + 48;
		else
			c1 = c1 + 55;
		if (c2 < 10)
			c2 = c2 + 48;
		else
			c2 = c2 + 55;
		fputc(c1, destfile);
		fputc(c2, destfile);
		fflush(destfile);

	}
	
	if (destfile !=  NULL)
		fclose(destfile);

	if (srcfile !=  NULL)
		fclose(srcfile);

	return 0;
}
