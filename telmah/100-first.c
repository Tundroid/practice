#include <stdio.h>

void tellme(void) __attribute__ ((constructor));

/**
* tellme - runs before main
*/
void tellme(void)
{
	printf("You're beat! and yet, you must allow,\n");
	printf("I bore my house upon my back!\n");
}
