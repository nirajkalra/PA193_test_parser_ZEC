
#include <string.h>
void hex2bin(char chex, char *cbin)
{
	
	switch (chex)
	{
	case '0':
		strncpy(cbin, "0000", 4); break;
	case '1':
		strncpy(cbin, "0001", 4); break;
	case '2':
		strncpy(cbin, "0010", 4); break;
	case '3':
		strncpy(cbin, "0011", 4); break;
	case '4':
		strncpy(cbin, "0100", 4); break;
	case '5':
		strncpy(cbin, "0101", 4); break;
	case '6':
		strncpy(cbin, "0110", 4); break;
	case '7':
		strncpy(cbin, "0111", 4); break;
	case '8':
		strncpy(cbin, "1000", 4); break;
	case '9':
		strncpy(cbin, "1001", 4); break;
	case 'A':
		strncpy(cbin, "1010", 4); break;
	case 'B':
		strncpy(cbin, "1011", 4); break;
	case 'C':
		strncpy(cbin, "1100", 4); break;
	case 'D':
		strncpy(cbin, "1101", 4); break;
	case 'E':
		strncpy(cbin, "1110", 4); break;
	case 'F':
		strncpy(cbin, "1111", 4); break;
	case 'a':
		strncpy(cbin, "1010", 4); break;
	case 'b':
		strncpy(cbin, "1011", 4); break;
	case 'c':
		strncpy(cbin, "1100", 4); break;
	case 'd':
		strncpy(cbin, "1101", 4); break;
	case 'e':
		strncpy(cbin, "1110", 4); break;
	case 'f':
		strncpy(cbin, "1111", 4); break;
	default:
		printf("\n Invalid hexa digit %c ", chex);
		exit(1);
	}
}