/**
 * @file main.c
 * @brief Car rental management system with linked lists.
 *
 * This program manages car rentals using three linked lists:
 * - Available cars (ordered by mileage)
 * - Rented cars (ordered by return date)
 * - Cars in repair
 *
 * The user can perform operations like adding, renting, returning, and transferring cars between lists.
 * Charges are computed for returned cars, and lists are saved/loaded from text files upon exit/start.
 *
 * Dependencies:
 * - nana.h: Header file that contains structure definitions, constants and functions prototypes.
 * - util.c: C source file that contains function implementations.
 *
 * @version 1.0
 * @date 2024-10-12
 * @author Telmah Tantoh
 */

#include "nana.h"

/**
 * main - check the code
 *
 * Return: Always 0.
 */
int main(void)
{
	
car_list_t **rental_list[] = {&available_head,
							  &rented_head,
							  &repair_head};
	int action;
	printf("1. %p\n", available_head);
	printf("2. %p\n", &available_head);
	printf("3. %p\n", rental_list[0]);

	printf("Loading data from file(s)...\n");
	load_from_file();
	printf("Loading complete 100%%!\n");

	printf("\n========================================");
	printf("\n*** Welcome to Nana Car Rental v1.0! ***");
	printf("\n========================================\n");

	while (true)
	{
		print_menu();
		scanf("%d", &action);
		printf("\n");
		switch (action)
		{
		case 1:
			add_new_car();
			break;
		case 2:
			return_car(AVAILABLE);
			break;
		case 3:
			return_car(IN_REPAIR);
			break;
		case 4:
			avail_rep_car();
			break;
		case 5:
			rent_car();
			break;
		case 6:
			print_inventory();
			break;
		case 7:
			printf("Saving data to file(s)...\n");
			serialize();
			printf("Saving complete 100%%!");
			exit(0);
			break;
		default:
			fprintf(stderr, "\a/!\\ Invalid option!\n");
			break;
		}
		printf("\n");
	}
	return (0);
}
