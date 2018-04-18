#include <stdio.h>

#ifndef LENGTH
#define LENGTH 50
#endif

int main()
{
	int pos;
	char c;
	FILE* fin  = fopen("in", "r");
	FILE* fout = fopen("out", "w");

	pos = 0;
	for (c = fgetc(fin); c != EOF; c = fgetc(fin))
	{
		if (c == 10)
		{
			//pos = 0;
			continue;
		}
		else pos++;
	
		fputc(c, fout);
	
		if (pos >= LENGTH)
		if (c == ' ' || c == '\t')
		{
			pos = 0;
			fputc('\n', fout);
		}	
	}
	fclose(fout);
}
