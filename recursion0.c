#include <stdio.h>

int sum_decimals(int);
void print_sum_decimals(int);
void print_decimals_asc(int);
void print_decimals_desc(int);

int main(void)
{
	for (int i = 0; i < 15; i++)
	{
		printf("Sum of all decimals from %d = %d.\n", i, sum_decimals(i));
	}
    printf("\nPrinting sum of decimals from i to 9...\n");
    for (int i = 0; i < 15; i++)
	{
		print_sum_decimals(i);
	}
    printf("\b\b%s%s.\n\nPrinting Decimals in ascending order...\n", "", "");
    for (int i = 0; i < 11; i++)
	{
		print_decimals_asc(i);
		printf("\b\b%s%s.", "", "");
        printf("\n");
	}
	printf("Printing Decimals in descinging order...\n");
    for (int i = 0; i < 11; i++)
	{
		print_decimals_desc(i);
		printf("\b\b%s%s.", "", "");
        printf("\n");
	}
}

int sum_decimals(int start)
{
	if (start < 10)
		return (start + sum_decimals(start + 1));
	else
		return (0);
}

void print_sum_decimals(int start)
{
	if (start < 10)
        printf("%d, ", start + sum_decimals(start + 1));
}

void print_decimals_asc(int start)
{
	if (start < 10)
    {
        printf("%d, ", start);
        print_decimals_asc(start + 1);
    }
}

void print_decimals_desc(int start)
{
	if (start < 10)
    {
        print_decimals_desc(start + 1);
        printf("%d, ", start);
    }
}