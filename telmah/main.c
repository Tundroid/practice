#include "nana.h"

car_list_t *available_head = NULL;
car_list_t *rented_head = NULL;
car_list_t *repair_head = NULL;


/**
 * main - check the code
 *
 * Return: Always 0.
 */
int main(void)
{
	int action;

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
				exit(0);
				break;
			default:
				printf("Invalid option\n");
				break;
		}
		printf("\n");
	}
    return (0);
}
