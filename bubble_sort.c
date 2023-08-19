#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bubble_sort(void *, unsigned long long, size_t, short (*)(const void *, const void *));
void print_int_list(int *, unsigned long long);
void print_float_list(float *, unsigned long long);
short int_swap_asc(const void *, const void *);
short int_swap_desc(const void *, const void *);
short float_swap_asc(const void *, const void *);
short float_swap_desc(const void *, const void *);

int main(void)
{
	// For integers
	int int_list[] = {4, 1, 5, 6, -3, -34, 6, -90, 2, 3, 1, 1};
	int int_list_count = sizeof(int_list) / sizeof(int_list[0]);
	printf("\nInt List before sorting...\n");
	print_int_list(int_list, int_list_count);
	bubble_sort(int_list, int_list_count, sizeof(int_list[0]), int_swap_asc);
	printf("\nInt List after sorting...ASCENDING\n");
	print_int_list(int_list, int_list_count);
	bubble_sort(int_list, int_list_count, sizeof(int_list[0]), int_swap_desc);
	printf("\nInt List after sorting...DESCENDING\n");
	print_int_list(int_list, int_list_count);


	// For real numbers
	float float_list[] = {4.0f, 1.6f, 5.5f, 6.3f, -3.8f, -34.23f, 6.05f, -90.2f, 2.3f, 3.9f, 1.99f, 1.98f};
	int float_list_count = sizeof(float_list) / sizeof(float_list[0]);
	printf("\nFloat List before sorting...\n");
	print_float_list(float_list, float_list_count);
	bubble_sort(float_list, float_list_count, sizeof(float_list[0]), float_swap_asc);
	printf("\nFloat List after sorting...ASCENDING\n");
	print_float_list(float_list, float_list_count);
	bubble_sort(float_list, float_list_count, sizeof(float_list[0]), float_swap_desc);
	printf("\nFloat List after sorting...DESCENDING\n");
	print_float_list(float_list, float_list_count);


	return (0);
}

/**
* bubble_sort - generic bubble sort algorithm
* @list: pointer to list of elements to be sorted
* @l_size: number of elements in list
* @bytes: size of each list element in bytes
* swap: callback function to determine
*
* Description: bubble_sort sorts by swapping two adjacent element.
* The swap function takes two arguments which are pointers to two
* adjacent elements, it returns 1 for swapping and 0 otherwise. 
*/
void bubble_sort(void *list, unsigned long long l_size, size_t bytes, short (*swap)(const void *, const void *))
{
	for (unsigned long long int i = 0; i < l_size; i++)
	{
		for (unsigned long long j = 1; j < l_size; j++)
		{
			if (swap((list + j * bytes), (list + (j - 1) * bytes)))
			{
				void *tmp = malloc(bytes);
				if (tmp == NULL)
					return;
				memcpy(tmp, (list + j * bytes), bytes);
				memcpy((list + j * bytes), (list + (j - 1) * bytes), bytes);
				memcpy((list + (j - 1) * bytes), tmp, bytes);
				free(tmp);
			}
		}
	}
}

//prints list of signed integer
void print_int_list(int *list, unsigned long long list_size)
{
	printf("List = {");
	for (unsigned long long i = 0; i < list_size; i++)
		printf("%d, ", list[i]);
	printf("\b\b%s%s}\n", "", "");
}

//prints list of floats
void print_float_list(float *list, unsigned long long list_size)
{
	printf("List = {");
	for (unsigned long long int i = 0; i < list_size; i++)
		printf("%.3f, ", list[i]);
	printf("\b\b%s%s}\n", "", "");
}

//Determine swap in ascending order for any type of signed integer
short int_swap_asc(const void *a, const void *b)
{
	return (*(int *)a < *(int *)b);
}

//Determine swap in descending order for any type of signed integer
short int_swap_desc(const void *a, const void *b)
{
	return (*(int *)a > *(int *)b);
}

short float_swap_asc(const void *a, const void *b)
{
	return (*(float *)a < *(float *)b);
}

short float_swap_desc(const void *a, const void *b)
{
	return (*(float *)a > *(float *)b);
}
