#include "zcash.h"

 int Z_SHA256D_Block_hash(char *srcfile, unsigned char *hash2) {
	
	
	
	unsigned char hash1[SHA256_DIGEST_LENGTH];
	
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
    fseek(ptr_myfile, 0L, SEEK_SET);	
	LenInByte= HEADERSIZE; // till solution

    unsigned char *InBytes = (unsigned char *)calloc(LenInByte, sizeof(char));
	if (InBytes == NULL)
	{
		printf("Can not allocate memory");
		exit(1);
	}
    fread(InBytes,1,LenInByte,ptr_myfile); // reading one byte 0xab
	

		//printf("%d\n", sizeof(InBytes) );

	
    SHA256_Init(&sha256_pass1);
    
    SHA256_Update(&sha256_pass1, InBytes, LenInByte);
    
    SHA256_Final(hash1, &sha256_pass1);
	
	
    
    SHA256_Init(&sha256_pass2);
    SHA256_Update(&sha256_pass2, hash1, SHA256_DIGEST_LENGTH);
    SHA256_Final(hash2, &sha256_pass2);
   
   /* int i;
	for(i=0;i<32; i++)
	printf("%02x",hash2[31-i]);
	 printf("\n");*/

	if(ptr_myfile!=NULL)
	fclose(ptr_myfile);

	free(InBytes);
	return 0;
}