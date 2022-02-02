void print(char *text);

extern int main()
{
	char *text = "Welcome to the cOS Kernel !\n\n\n\n";
	print(text);
	return 0;
}

/**
 * @brief Prints a string to the screen
 *
 * @param text   - The string to print
 */
void print(char *text)
{
	volatile char *buff = (volatile char *)0xb8000;
	int i = 0;

	while (text[i] != 0)
	{
		*buff++ = text[i++];
		*buff++ = 0x02;
	}
	return;
}
