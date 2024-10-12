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

    // list_t *new;
    // list_t hello = {"World", 5, NULL};
    // size_t n;

    // head = &hello;
    // new = malloc(sizeof(list_t));
    // if (new == NULL)
    // {
    //     printf("Error\n");
    //     return (1);
    // }
    // new->str = strdup("Hello");
    // new->len = 5;
    // new->next = head;
    // head = new;
    // n = print_list(head);
    // printf("-> %lu elements\n", n);

    // printf("\n");
    // free(new->str);
    // new->str = NULL;
    // n = print_list(head);
    // printf("-> %lu elements\n", n);

    // free(new);
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
			case 3:
				return_car(action = 2 ? AVAILABE : IN_REPAIR);
			break;
			case 4:
			break;
			case 5:
				rent_car();
				break;
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
