#include "sort.h"

int main(void)
{
	// For students
	student stud_list[] = {{"Felix", 26, 2.5f},
							{"Mohammed", 30, 3.0f},
							{"Shamain", 27, 2.7}};
	int stud_list_count = sizeof(stud_list) / sizeof(stud_list[0]);
	printf("\nStudent List before sorting...\n");
	print_stud_list(stud_list, stud_list_count);
	bubble_sort(stud_list, stud_list_count, sizeof(stud_list[0]), stud_gpa_swap_asc);
	printf("\nStudent List after sorting by GPA...ASCENDING\n");
	print_stud_list(stud_list, stud_list_count);
	bubble_sort(stud_list, stud_list_count, sizeof(stud_list[0]), stud_gpa_swap_desc);
	printf("\nStudent List after sorting by GPA...DESCENDING\n");
	print_stud_list(stud_list, stud_list_count);
	bubble_sort(stud_list, stud_list_count, sizeof(stud_list[0]), stud_age_swap_asc);
	printf("\nStudent List after sorting by age...ASCENDING\n");
	print_stud_list(stud_list, stud_list_count);
	bubble_sort(stud_list, stud_list_count, sizeof(stud_list[0]), stud_age_swap_desc);
	printf("\nStudent List after sorting by age...DESCENDING\n");
	print_stud_list(stud_list, stud_list_count);
	bubble_sort(stud_list, stud_list_count, sizeof(stud_list[0]), stud_name_swap_asc);
	printf("\nStudent List after sorting by name...ASCENDING\n");
	print_stud_list(stud_list, stud_list_count);
	bubble_sort(stud_list, stud_list_count, sizeof(stud_list[0]), stud_name_swap_desc);
	printf("\nStudent List after sorting by name...DESCENDING\n");
	print_stud_list(stud_list, stud_list_count);

	return (0);
}
