#include "sort.h"

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
