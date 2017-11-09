#include "zcash.h"
#include "ZBlock_merkle.cpp"

int validatetransaction(char *srcfilename, unsigned char * merklehash)
{
	
	unsigned char merkle2[SHA256_DIGEST_LENGTH];
	
	int i, flag=0;

	int retval = Z_SHA256D_Block_Merkle(srcfilename, merkle2);
	if (retval == 1)
	{
		printf("ERROR calculating Hash");
		exit(1);
	}
	else {

		printf("\n Calculated Merkle Hash of this blk = ");
		for (i = 0;i<32; i++)
			printf("%02x", merkle2[31-i]);
		

		printf("\n Merkle Hash read from .dat file = ");
		for (i = 0;i<32; i++)
			printf("%02x", merklehash[i]);
			// compare Merkle Value 
			
		for (i = 0;i < 32; i++)
		{
			if (merkle2[i] != merklehash[31 - i])
			{
				printf("\n\n Merkle HASH transaction could not be validated");
				flag = 1;
				break;
			}
			
		}
		if (flag == 0)
		{
			printf("\n\n Transaction validated from Merkle Hash");

		}
		else
			return 1;
		
	}
	

	return 0;
}