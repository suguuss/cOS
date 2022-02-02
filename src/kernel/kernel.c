#include "print.h"
#include <stdint.h>

extern int main()
{
	uint8_t *text = "Welcome to the cOS Kernel !";
	print(text);

	return 0;
}