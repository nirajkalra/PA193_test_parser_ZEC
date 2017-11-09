// ZcashParser.cpp : Defines the entry point for the console application.
//

#include "asciitohex.cpp"
#include "hex2int.cpp"
#include "hex2bin.cpp"
#include "filehex2bin.cpp"
#include "filedat2hex.cpp"
#include "readfile.cpp"
#include "validateblock.cpp"
#include "validatetransaction.cpp"
#include "zcash.h"



struct ZBLOCK{

	unsigned char version[4];	// 4 bytes
	unsigned char hashPrevBlock[32];		// 32 bytes
	unsigned char hashMerkleRoot[32];	// 32 bytes
	unsigned char hashReserved[32];		// 32 bytes
	long int nTime;					// 4 bytes
	int nBits;				// 4 bytes
	unsigned char nNonce[32];			// 32 bytes
	int solutionsize;			// 3 bytes
	unsigned char solution[1344];		// 1344 bytes
	};


void fillbuffer(unsigned char *tval , char * buf, int length)
{
	int mbyte;
	for (mbyte = 0; mbyte < length; mbyte++)
		tval[mbyte] = buf[mbyte];
}


void stdoutprint(struct ZBLOCK zblock)
{
	int i;

	printf("\n VERSION = ");
	for(i = 0; i < 4; i++)
	printf("%02X ", zblock.version[i]);

	printf("\n HASHPREVBLOCK = ");
	for (i = 0; i < 32; i++)
		printf("%02X ", zblock.hashPrevBlock[i]);

	printf("\n HASHMERKLEROOT = ");
	for (i = 0; i < 32; i++)
		printf("%02X ", zblock.hashMerkleRoot[i]);

	printf("\n HASHRESERVED = ");
	for (i = 0; i < 32; i++)
		printf("%02X ", zblock.hashReserved[i]);

	time_t now = zblock.nTime;
	struct tm *ptm = gmtime(&now);
	printf("\n UTC TIME: %s", asctime(ptm));

	printf("\n NBITS = ");
	printf("%d ", zblock.nBits);

	printf("\n NONCE = ");
	for (i = 0; i < 32; i++)
		printf("%02X ", zblock.nNonce[i]);

	printf("\n SOLUTIONSIZE = ");
	printf("%d ", zblock.solutionsize);

	printf("\n SOLUTION = ");
	for (i = 0; i < 1344; i++)
		printf("%02X ", zblock.solution[i]);
		
}

int main()
{

	//lOCAL vARIABLES
	int fpos = 0;
	
	struct ZBLOCK  zblock;
	

	char blkfiledat[] = "blk00013_102038.dat";
	char nxtblkfiledat[] = "blk00013_102039.dat";  //next block
	char blkfilehex[] = "blkhex.bin";
	char blkfilebin[] = "blkbin.bin";
	unsigned char hashPrevBlock[32];
	int nTransactions;
	int retval;
		
	filedat2hex(blkfiledat, blkfilehex);
	filehex2bin(blkfilehex, blkfilebin, 1487 * 2);
	
	//parseheader(blkfilehex, &zblock);
	int bytestoread;
	FILE *zblockfile;    // has the hex file to parse
	zblockfile = fopen(blkfilehex, "rb");

	if (zblockfile == NULL)
	{
		printf("Error reading Block file");
		return 1;
	}

	char *buffer = (char*)malloc(60 * sizeof(char));
	if (buffer == NULL)
	{
		printf("Error allocating memory for buffer");
		return 1;
	}

	//read version
	bytestoread = 4;
	readfile(zblockfile, fpos, bytestoread, LITTLEENDIAN, buffer);
	fillbuffer((zblock).version, buffer, bytestoread);
	fpos = fpos + bytestoread * 2;  // multiply *2 since two nibbles are read as one byte
	memset(buffer, 0, 60);

	//read hashPreviousBlock
	bytestoread = 32;
	readfile(zblockfile, fpos, bytestoread, LITTLEENDIAN, buffer);
	fillbuffer((zblock).hashPrevBlock, buffer, bytestoread);
	fpos = fpos + bytestoread * 2;
	memset(buffer, 0, 60);


	//read hashMerkleRoot
	bytestoread = 32;
	readfile(zblockfile, fpos, bytestoread, LITTLEENDIAN, buffer);
	fillbuffer((zblock).hashMerkleRoot, buffer, bytestoread);
	fpos = fpos + bytestoread * 2;
	memset(buffer, 0, 60);

	//read Reserved
	bytestoread = 32;
	readfile(zblockfile, fpos, bytestoread, LITTLEENDIAN, buffer);
	fillbuffer((zblock).hashReserved, buffer, bytestoread);
	fpos = fpos + bytestoread * 2;
	memset(buffer, 0, 60);

	//read time
	bytestoread = 4;
	readfile(zblockfile, fpos, bytestoread, LITTLEENDIAN, buffer);
	zblock.nTime = hex2int(buffer, 4);
	
	fpos = fpos + bytestoread * 2;
	memset(buffer, 0, 60);

	//read nbits
	bytestoread = 4;
	readfile(zblockfile, fpos, bytestoread, LITTLEENDIAN, buffer);
	zblock.nBits = hex2int(buffer, 4);
	fpos = fpos + bytestoread * 2;
	memset(buffer, 0, 60);

	//read nNonce
	bytestoread = 32;
	readfile(zblockfile, fpos, bytestoread, LITTLEENDIAN, buffer);
	fillbuffer((zblock).nNonce, buffer, bytestoread);
	fpos = fpos + bytestoread * 2;
	memset(buffer, 0, 60);

	//read solutionsize
	bytestoread = 3;
	readfile(zblockfile, fpos, bytestoread, LITTLEENDIAN, buffer);
	zblock.solutionsize = hex2int(buffer, 2);
	fpos = fpos + bytestoread * 2;
	memset(buffer, 0, 60);

	//read Solution
	bytestoread = 1344;

	char * largebuf = (char*)malloc(bytestoread * sizeof(char));
	if (largebuf == NULL)
	{
		printf("ERROR :Unable to allocate Memory for Solution");
		exit(-1);
	}

	readfile(zblockfile, fpos, bytestoread, BIGENDIAN, largebuf);
	fillbuffer((zblock).solution, largebuf, bytestoread);
	fpos = fpos + bytestoread * 2;
	memset(largebuf, 0, 1344);
	
	//read number of Transactions 
	bytestoread = 1;
	readfile(zblockfile, fpos, bytestoread, BIGENDIAN, buffer);
	nTransactions = hex2int(buffer,1);
	fpos = fpos + bytestoread * 2;
	
	
	//VAlidate Block
	 retval = validateblock(blkfiledat, nxtblkfiledat, (zblock).version, zblock.nTime);
	 //VAlidate transaction using Merkle root hash
	 retval = validatetransaction(blkfiledat, zblock.hashMerkleRoot);

	if (largebuf != NULL) 
		free(largebuf);

	if (zblockfile != NULL)
		fclose(zblockfile);

	stdoutprint(zblock);
	printf("\n\n No of Transactions = %d\n", nTransactions);
    return 0;
}

