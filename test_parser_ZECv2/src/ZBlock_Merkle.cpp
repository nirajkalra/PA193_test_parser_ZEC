// This function takes input transaction and calculates Merkle Hash
#include "zcash.h"

 int Z_SHA256D_Block_Merkle(char *srcfile, unsigned char *merkle2) {
	
	
	
	unsigned char merkle1[SHA256_DIGEST_LENGTH];
	
	FILE *ptr_myfile;
	
    SHA256_CTX sha256_pass1, sha256_pass2;

    ptr_myfile=fopen(srcfile,"r");
		if (!ptr_myfile)
		{
			printf("Unable to open file!");
			return 1;
		}

     fseek(ptr_myfile, 0L, SEEK_END);  // to check the input legnth of file
     unsigned int LenInByte; 
    LenInByte = ftell(ptr_myfile);
    fseek(ptr_myfile, 1488L, SEEK_SET);	
	LenInByte= LenInByte-1488; // till solution

    unsigned char *InBytes = (unsigned char *)calloc(LenInByte, sizeof(char));
	if (InBytes == NULL)
	{
		printf("Can not allocate memory");
		exit(1);
	}
    fread(InBytes,1,LenInByte,ptr_myfile); // reading one byte 0xab
	

		//printf("%d\n", sizeof(InBytes) );

	
    SHA256_Init(&sha256_pass1);  // initializing sha
    
    SHA256_Update(&sha256_pass1, InBytes, LenInByte); 
    
    SHA256_Final(merkle1, &sha256_pass1);
// First hash of transaction is calculation	
	
    
    SHA256_Init(&sha256_pass2);
    SHA256_Update(&sha256_pass2, merkle1, SHA256_DIGEST_LENGTH);
    SHA256_Final(merkle2, &sha256_pass2);
   
   /* int i;
	for(i=0;i<32; i++)
	printf("%02x",merkle2[31-i]);
	 printf("\n");*/

	if(ptr_myfile!=NULL)
	fclose(ptr_myfile);

	free(InBytes);
	return 0;
}
