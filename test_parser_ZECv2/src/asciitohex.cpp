#include "zcash.h"

int ascii_to_hex(char c)
{
	int num = (int)c;
	if (num > 47 && num < 58)
	{
		return num - 48;
	}
	if ((num > 96 && num < 103))
	{
		return num - 87;
	}

	if ((num > 64 && num < 71))
	{
		return num - 55;
	}
	else
	{
		printf("Not a valid input in file only 0-9 ans A-F accepted");
		//exit(1);
	}
	return num;
}