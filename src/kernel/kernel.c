void print(char *text, int length);

extern int main()
{
	char text[] = "Test";
	print(text, 4);
	return 0;
}

void print(char *text, int length)
{
	volatile char *buff = (volatile char *)0xb8000;
	int i = 0;
	for (i = 0; i < length; i++)
	{
		*buff++ = text[i];
		*buff++ = 0x02;
	}
	return;
}
