#include "sort.h"

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

//prints list of students
void print_stud_list(student *list, unsigned long long list_size)
{
	printf("Student List\n============\n");
	printf("|%5s|%10s|%5s|%6s|\n", "ID", "Name", "Age", "GPA");
	for (unsigned long long int i = 0; i < list_size; i++)
		printf("|%4ld.|%10s|%5d|%6.2f|\n", i + 1, list[i].name, list[i].age, list[i].gpa);
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

short stud_gpa_swap_asc(const void *a, const void *b)
{
	return (((student *)a)->gpa < ((student *)b)->gpa);
}

short stud_gpa_swap_desc(const void *a, const void *b)
{
	return (((student *)a)->gpa > ((student *)b)->gpa);
}

short stud_age_swap_asc(const void *a, const void *b)
{
	return (((student *)a)->age < ((student *)b)->age);
}

short stud_age_swap_desc(const void *a, const void *b)
{
	return (((student *)a)->age > ((student *)b)->age);
}

short stud_name_swap_asc(const void *a, const void *b)
{
	return (strcmp(((student *)a)->name, ((student *)b)->name) <= 0);
}

short stud_name_swap_desc(const void *a, const void *b)
{
	return (strcmp(((student *)a)->name, ((student *)b)->name) > 0);
}

