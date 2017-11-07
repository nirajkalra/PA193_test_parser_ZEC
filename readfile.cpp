#define LITTLEENDIAN 0
#define BIGENDIAN 1

int readfile(FILE *fp, int offset, int bytestoread, int type, char * buf)
{
	int bytesread = 0;
	unsigned char c1, c2;
	fseek(fp, offset, SEEK_SET);
	for (bytesread = 0; bytesread < bytestoread; bytesread++)
	{
		c1 = ascii_to_hex(fgetc(fp));
		c2 = ascii_to_hex(fgetc(fp));
		if (type == LITTLEENDIAN)
			buf[bytestoread - bytesread - 1] = c1 << 4 | c2;
		else                          //BIGENDIAN
			buf[bytesread] = c1 << 4 | c2;
	}
	return 0;
}
