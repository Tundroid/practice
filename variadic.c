#include <stdio.h>
#include <stdarg.h>

void print_args(int, void (*)(int), void(*)(int), ...);
void report_negative(int);
void report_zero(int);

int main(void)
{
	void (*pa)(int, void (*)(int), void (*)(int), ...);
	void (*neg_func)(int) = report_negative;
	void (*zero_func)(int) = report_zero;
	int count = 5;

	pa = print_args;
	printf("First Call\n");
	print_args(1, neg_func, zero_func, 4);
	printf("Second Call\n");
	print_args(4, neg_func, zero_func,  4, -1, 0, 6);
	printf("Third Call\n");
	print_args(3, neg_func, zero_func, 5, -6, 7, 8, -9, 0, 9);
	printf("Fourth Call\n");
	pa(count, neg_func, zero_func, 2, 3, 4, 5, -2333);
	return (0);
}

void print_args(int n, void (*nf)(int), void (*zf)(int), ...)
{
	va_list arg_list;
	int i = 1, a_value;

	va_start(arg_list, zf);
	while (n > 0)
	{
		a_value = va_arg(arg_list, int);
		if (a_value < 0)
			nf(a_value);
		else if (a_value == 0)
			zf(a_value);
		else
			printf("Arg [%d]: %d\n", i++, a_value);
		n--;
	}
	va_end(arg_list);
}

void report_negative(int x)
{
	fprintf(stderr, "Error encountered (-ve value): %d\n", x);
}

void report_zero(int x)
{
	fprintf(stderr, "Error encountered (0 value): %d\n", x);
}
