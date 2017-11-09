#include "zcash.h"
#include "ZBlock_hash.cpp"
#include "gethashprevBlk.cpp"
int validateblock(char *srcfilename, char *prevblkfilename, unsigned char* version, long int utime)
{
	char ver[] = "\x0\x0\x0\x4\x0\x0\x0\x0";
	long int zcashtime = 1477991481; // UTC time not valid before 01 NOv 2016
	char temp;
	unsigned char hash2[SHA256_DIGEST_LENGTH];
	 char hashprev[33];
	int i, flag;

	FILE *srcfile = fopen(srcfilename, "rb");
	if (srcfile == NULL)
	{
		printf("Error Opening file ");
		exit(1);
	}
	

	// check version

	int flag_ver = 0;
	int count;
	for (count = 0; count <8; count++)
	{
		if (ver[count] != version[count])
		{
			flag_ver = 1;
			break;
		}

	}
	if(flag_ver == 1)
	{
		printf("\nBlock is not of correct Version Type");
		exit(1);
	}

	//check for time
	if (utime < zcashtime)
	{
		printf("\nBlock is not of correct Type : Time mismatch");
		exit(1);
	}
	// check for current time 


	//check for size
	fseek(srcfile, 0, SEEK_END);
	int sizeoffile = ftell(srcfile);
	if(sizeoffile > 2000000)
	{
		printf("\nBlock is not of correct Type : TOO Large size");
		exit(1);
	}

	if (srcfile != NULL)
		fclose(srcfile);

	int retval = Z_SHA256D_Block_hash(srcfilename, hash2);
	if (retval == 1)
	{
		printf("ERROR calculating Hash");
		exit(1);
	}
	else {

		printf("\n Calculated hash of this blk = ");
		for (i = 0;i<32; i++)
			printf("%02x", hash2[31 - i]);
		

		gethashprevBlk(prevblkfilename, hashprev);

		printf("\n Hash of this blk from next blk = ");
		for (i = 0;i<32; i++)
			printf("%02x", (unsigned char)hashprev[31 - i]);
			// compare HASH Value 
			
		for (i = 0;i < 32; i++)
		{
			if (hash2[31 - i] != (unsigned char)hashprev[31 - i])
			{
				printf("\n\n HASH could not be validated");
				flag = 1;
				break;
			}
			
		}
		if (flag == 0)
		{
			printf("\n\n HASH validated with next block");
		}
		else
			return 1;
		
	}
	

	return 0;
}