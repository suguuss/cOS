extern int main()
{
	char text[] = "Test";

	volatile char *buff = (volatile char *)0xb8000;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		*buff++ = text[i];
		*buff++ = 0x02;
	}

	return 0;
}