long hex2int(char *a, int len)
{
	unsigned char c1, c2;
	int i;
	//unsigned long val = 0, num = 0;

	for (i = 0;i < len;i++)
	{
		c1 = 0; c2 = 0;
		c1 = (a[i] >> 4) & 0X0F;
		num = num + c1* (pow(16, (len * 2) - 1 - i * 2));

		c2 = a[i] << 4;
		c2 = c2 >> 4 & 0X0F;
		num = num + c2* (pow(16, (len * 2) - 2 - i * 2));

	}
	return num;
}
