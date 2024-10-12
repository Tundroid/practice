#include "nana.h"

/**
 * print_menu - prints app menu
 */
void print_menu(void)
{
	printf("Welcome to NaNa Car Rental!\n");
	printf("Menu\n====\n");
	printf("1. Add new car for rent\n");
	printf("2. Avail returned car\n");
	printf("3. Send returned car for repairs\n");
	printf("4. Avail repaired car\n");
	printf("5. Rent availabe car\n");
	printf("6. Print inventory\n");
	printf("7. Quit\n");
	printf("Action: ");
}

/**
 * list_insert - inserts a car node into a list
 * @head: of linked list
 * @car_node: to be inserted
 * @flag: to determine insertion order
 */
void list_insert(car_list_t **head, car_list_t *car_node, rental_list_enum_t flag)
{
	if (!*head || flag == IN_REPAIR)
	{
		car_node->next = *head;
		*head = car_node;
	}
	else if (flag != IN_REPAIR)
	{
		car_list_t *tmp = *head;
		car_list_t *prev = NULL;

		while (tmp)
		{
			bool compare = flag == AVAILABLE ? car_node->car.mileage <= tmp->car.mileage : car_node->car.exp_ret_date <= tmp->car.exp_ret_date;
			if (compare)
			{
				car_node->next = tmp;
				if (!prev)
					*head = car_node;
				else
					prev->next = car_node;
				break;
			}
			else if (!tmp->next)
			{
				tmp->next = car_node;
				break;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

/**
 * list_remove - removes a car node from a list
 * @head: of linked list
 * @plate_number: of car to be remove
 * @flag: to determine deletion order
 */
car_list_t *list_remove(car_list_t **head, char *plate_number, rental_list_enum_t flag)
{
	if (!head || !*head)
	{
		fprintf(stderr, "No or empty list!");
	}
	else
	{
		car_list_t *tmp = *head;

		if (flag == AVAILABLE)
		{
			*head = (*head)->next;
			tmp->next = NULL;
			return (tmp);
		}
		else
		{
			car_list_t *prev = NULL;

			while (tmp)
			{
				printf("\nHere...2\n");
				if (strcmp(tmp->car.plate_number, plate_number) == 0)
				{
					car_list_t *ret = tmp;

					if (!prev)
						*head = (*head)->next;
					else
						prev = tmp->next;
					ret->next = NULL;
					return (ret);
				}
			}
			fprintf(stderr, "No car matches plate number %s!\n", plate_number);
		}
	}
	return (NULL);
}

/**
 * add_new_car - adds a new car node to available list
 */
void add_new_car(void)
{
	car_list_t *car_node = malloc(sizeof(car_list_t));

	if (!car_node)
	{
		fprintf(stderr, "Could not allocate memory for new car node!\n");
		return;
	}

	printf("Enter plate number: ");
	scanf("%s", car_node->car.plate_number);
	printf("Enter milleage for %s: ", car_node->car.plate_number);
	scanf("%d", &car_node->car.mileage);

	car_node->car.exp_ret_date = -1;
	car_node->next = NULL;

	list_insert(&available_head, car_node, AVAILABLE);
	printf("*** New car %s with mileage %d added to AVAILABLE list ***\n",
		   car_node->car.plate_number, car_node->car.mileage);
}

/**
 * rent_car - moves a car from available list to rented list
 */
void rent_car(void)
{
	if (!available_head)
	{
		fprintf(stderr, "No available cars to rent!");
		return;
	}

	printf("Enter expected return date(yyyymmdd): ");
	scanf("%d", &available_head->car.exp_ret_date);

	/* NULL is passed here because the function will
	 not be searching through the list */
	car_list_t *car_node = list_remove(&available_head, NULL, AVAILABLE);

	if (car_node)
	{
		list_insert(&rented_head, car_node, RENTED);
		printf("*** Rented out car %s with mileage %d and expected return on %d ***\n",
		car_node->car.plate_number, car_node->car.mileage, car_node->car.exp_ret_date);
		printf("*** %s moved from AVAILABLE list to RENTED list ***\n",	car_node->car.plate_number);
	}
}

/**
 * return_car - adds a returned car to available / repair list
 * @flag: the destination list
 */
void return_car(rental_list_enum_t flag)
{
	if (!rented_head)
	{
		fprintf(stderr, "No rented cars to return!");
		return;
	}

	char plate_number[10];
	int mileage, old_mileage, extra_kms;
	float charge = 0.0f;

	printf("Enter plate number: ");
	scanf("%s", plate_number);

	printf("\nHere...0\n");
	car_list_t *car_node = list_remove(&rented_head, plate_number, RENTED);

	if (!car_node)
		return;

	old_mileage = car_node->car.mileage;
	printf("\nHere...1\n");

	while (true)
	{
		printf("Enter returned mileage: ");
		scanf("%d", &mileage);
		if (old_mileage < mileage)
			break;
		fprintf(stderr, "Returned mileage must be greater mileage at the time of rental!\n");
	}

	car_node->car.mileage = mileage;
	car_node->car.exp_ret_date = -1;

	list_insert(flag == AVAILABLE ? &available_head : &repair_head, car_node, flag);

	extra_kms = mileage - old_mileage - FLAT_RATE_KM_MAX;
	charge = FLAT_RATE + (extra_kms > 0 ? extra_kms * EXTRA_RATE_PER_KM : 0.0f);

	if (flag == AVAILABLE)
	{
		printf("*** %s is returned with mileage %d and available for rent out, charge is $%0.2f ***\n",
				car_node->car.plate_number, car_node->car.mileage, charge);
		printf("*** %s moved from RENTED list to AVAILABLE list ***\n",	car_node->car.plate_number);
	}
	else
	{
		printf("*** %s is returned with mileage %d but under repairs, charge is $%0.2f ***\n",
				car_node->car.plate_number, car_node->car.mileage, charge);
		printf("*** %s moved from RENTED list to IN-REPAIR list ***\n",	car_node->car.plate_number);
	}
}

/**
 * avail_rep_car - adds a repaired car to available list
 */
void avail_rep_car(void)
{
	if (!repair_head)
	{
		fprintf(stderr, "No cars in repair!");
		return;
	}

	char plate_number[10];

	printf("Enter plate number: ");
	scanf("%s", plate_number);

	car_list_t *car_node = list_remove(&repair_head, plate_number, IN_REPAIR);

	if (!car_node)
		return;

	list_insert(&available_head, car_node, AVAILABLE);
	printf("*** %s repaired and moved from IN-REPAIR list to AVAILABLE list ***\n",	car_node->car.plate_number);
}

/**
 * print_inventory - prints all car rentail inventory
 */
void print_inventory(void)
{
	char *car_list[] = {"Available Cars", "Rented Cars", "In-repair Cars"};
	car_list_t *rental_list[] = {available_head, rented_head, repair_head};

	for (int i = 0; i < 3; i++)
	{
		printf("(((%s)))\n", car_list[i]);
		printf("+--------------+----------+----------------------+\n");
		printf("| Plate Number | Milleage | Expected Return Date |\n");
		printf("+--------------+----------+----------------------+\n");
		car_list_t *h = rental_list[i];

		while (h)
		{
			printf("| %-12s | %-8d | %20d |\n", h->car.plate_number,
				   h->car.mileage, h->car.exp_ret_date);
			h = h->next;
		}
		printf("+--------------+----------+----------------------+\n");
	}
}
