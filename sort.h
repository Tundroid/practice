#ifndef MOLe_Sort_LIB
#define MOLe_Sort_LIB

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student
{
	char *name;
	int age;
	float gpa;
} student;

void bubble_sort(void *, unsigned long long, size_t, short (*)(const void *, const void *));
void print_int_list(int *, unsigned long long);
void print_float_list(float *, unsigned long long);
void print_stud_list(student *, unsigned long long);
short int_swap_asc(const void *, const void *);
short int_swap_desc(const void *, const void *);
short float_swap_asc(const void *, const void *);
short float_swap_desc(const void *, const void *);
short stud_gpa_swap_asc(const void *, const void *);
short stud_gpa_swap_desc(const void *, const void *);
short stud_age_swap_asc(const void *, const void *);
short stud_age_swap_desc(const void *, const void *);
short stud_name_swap_asc(const void *, const void *);
short stud_name_swap_desc(const void *, const void *);

#endif
