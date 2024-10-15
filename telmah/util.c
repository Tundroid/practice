#include "nana.h"

/**
 * print_menu - prints app menu
 */
void print_menu(void)
{
	printf("\n<<< Menu >>>\n============\n");
	printf("1. Add new car for rent\n");
	printf("2. Avail returned car\n");
	printf("3. Send returned car for repairs\n");
	printf("4. Avail repaired car\n");
	printf("5. Rent availabe car\n");
	printf("6. Print inventory\n");
	printf("7. Quit\n");
	printf("\nnana@Rental$ ");
}

/**
 * list_insert - inserts a car node into a list
 * @head: of linked list
 * @car_node: to be inserted
 * @flag: to determine insertion order
 */
void list_insert(car_list_t **head, car_list_t *car_node, rental_list_enum_t flag)
{
	if (!head)
	{
		fprintf(stderr, "\a/!\\ No list!");
	}
	else if (!*head || flag == IN_REPAIR)
	{
		car_node->next = *head;
		*head = car_node;
	}
	else
	{
		car_list_t *tmp = *head;
		car_list_t *prev = NULL;

		while (tmp)
		{
			bool compare = flag == AVAILABLE ? car_node->car.mileage <= tmp->car.mileage
											 : car_node->car.exp_ret_date <= tmp->car.exp_ret_date;

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
		fprintf(stderr, "\a/!\\ No or empty list!");
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
				if (strcmp(tmp->car.plate_number, plate_number) == 0)
				{
					car_list_t *ret = tmp;

					if (!prev)
						*head = (*head)->next;
					else
						prev->next = tmp->next;
					ret->next = NULL;
					return (ret);
				}
				prev = tmp;
				tmp = tmp->next;
			}
			fprintf(stderr, "\a/!\\ No car matches plate number %s in list!\n", plate_number);
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
		fprintf(stderr, "\a/!\\ Could not allocate memory for new car node!\n");
		return;
	}

	prompt_plate_number(car_node->car.plate_number);

	while (true)
	{
		printf("Enter milleage for %s: ", car_node->car.plate_number);
		scanf("%d", &car_node->car.mileage);
		if (car_node->car.mileage >= 0)
			break;
		fprintf(stderr, "\a/!\\ Mileage cannot be negative!\n");
	}

	car_node->car.exp_ret_date = -1;
	car_node->next = NULL;

	list_insert(&available_head, car_node, AVAILABLE);
	printf("\n*** New car %s with mileage %d added to AVAILABLE list ***",
		   car_node->car.plate_number, car_node->car.mileage);
}

/**
 * rent_car - moves a car from available list to rented list
 */
void rent_car(void)
{
	if (!available_head)
	{
		fprintf(stderr, "\a/!\\ No available cars to rent!");
		return;
	}

	prompt_date(&available_head->car.exp_ret_date);

	/* NULL is passed here because the function will
	 not be searching through the list bur rather removes the head if available */
	car_list_t *car_node = list_remove(&available_head, NULL, AVAILABLE);

	if (car_node)
	{
		list_insert(&rented_head, car_node, RENTED);
		printf("\n*** Rented out car %s with mileage %d and expected return on %d ***",
			   car_node->car.plate_number, car_node->car.mileage, car_node->car.exp_ret_date);
		printf("\n*** %s moved from AVAILABLE list to RENTED list ***", car_node->car.plate_number);
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
		fprintf(stderr, "\a/!\\ No rented cars to return!");
		return;
	}

	char plate_number[PLATE_BUFFER_LEN];
	int mileage, old_mileage, extra_kms;
	float charge = 0.0f;

	prompt_plate_number(plate_number);

	car_list_t *car_node = list_remove(&rented_head, plate_number, RENTED);

	if (!car_node)
		return;

	old_mileage = car_node->car.mileage;

	while (true)
	{
		printf("Enter returned mileage: ");
		scanf("%d", &mileage);
		if (old_mileage < mileage)
			break;
		fprintf(stderr, "\a/!\\ Returned mileage must be greater than mileage at the time of rental!\n");
	}

	car_node->car.mileage = mileage;
	car_node->car.exp_ret_date = -1;

	list_insert(flag == AVAILABLE ? &available_head : &repair_head, car_node, flag);

	extra_kms = mileage - old_mileage - FLAT_RATE_KM_MAX;
	charge = FLAT_RATE + (extra_kms > 0 ? extra_kms * EXTRA_RATE_PER_KM : 0.0f);

	if (flag == AVAILABLE)
	{
		printf("\n*** %s is returned with mileage %d and available for rent out, charge is $%0.2f ***",
			   car_node->car.plate_number, car_node->car.mileage, charge);
		printf("\n*** %s moved from RENTED list to AVAILABLE list ***", car_node->car.plate_number);
	}
	else
	{
		printf("\n*** %s is returned with mileage %d but under repairs, charge is $%0.2f ***",
			   car_node->car.plate_number, car_node->car.mileage, charge);
		printf("\n*** %s moved from RENTED list to IN-REPAIR list ***", car_node->car.plate_number);
	}
}

/**
 * avail_rep_car - adds a repaired car to available list
 */
void avail_rep_car(void)
{
	if (!repair_head)
	{
		fprintf(stderr, "\a/!\\ No cars in repair!");
		return;
	}

	char plate_number[PLATE_BUFFER_LEN];

	prompt_plate_number(plate_number);

	car_list_t *car_node = list_remove(&repair_head, plate_number, IN_REPAIR);

	if (!car_node)
		return;

	list_insert(&available_head, car_node, AVAILABLE);
	printf("\n*** %s repaired and moved from IN-REPAIR list to AVAILABLE list ***",
		   car_node->car.plate_number);
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

/**
 * serialize - convert rental car linked lists to csv
 */
void serialize(void)
{
	char *filenames[] = {"AVAILABLE.txt", "RENTED.txt", "REPAIR.txt"};
	char *car_list[] = {"Available Cars", "Rented Cars", "In-repair Cars"};
	car_list_t *rental_list[] = {available_head, rented_head, repair_head};
	char line_buffer[30]; // 30 because max of plate # is 8, milleage is 10, date is 8, 3 commas and \0
	char *header = "Plate Number, Mileage, Expected Return Date\n";

	char *data;

	for (int i = 0; i < 3; i++)
	{
		car_list_t *h = rental_list[i];
		car_list_t *tmp;

		printf("Saving %s ...\n", car_list[i]);

		data = malloc(strlen(header) + 1);
		strcpy(data, header);

		while (h)
		{
			tmp = h;

			bzero(line_buffer, sizeof(line_buffer));
			sprintf(line_buffer, "%s,", h->car.plate_number);
			sprintf(line_buffer + strlen(line_buffer), "%d,", h->car.mileage);
			sprintf(line_buffer + strlen(line_buffer), "%d\n", h->car.exp_ret_date);

			data = realloc(data, strlen(data) + strlen(line_buffer) + 1);
			strcat(data, line_buffer);

			h = h->next;
			free(tmp);
		}
		save_to_file(data, filenames[i]);
		free(data);
	}
}

/**
 * save_to_file - write serialized data to text file as csv
 * @data: to be saved
 * @filename: of text file
 */
void save_to_file(const char *data, const char *filename)
{
	ssize_t _open;

	if (filename)
	{
		_open = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
		if (data)
			write(_open, data, strlen(data));
		close(_open);
	}
}

/**
 * load_from_file - loads csv data from txt files
 */
void load_from_file(void)
{
	char line_buffer[50];
	FILE *file;

	for (int i = 0; i < 3; i++)
	{
		printf("Loading %s ...\n", car_list[i]);

		if ((file = fopen(filenames[i], "r")))
		{
			fgets(line_buffer, 50, file); // skip headers

			while (fgets(line_buffer, 50, file))
			{
				car_list_t *car_node = malloc(sizeof(car_list_t));

				if (!car_node)
				{
					fprintf(stderr, "\a/!\\ Could not allocate memory for car node!\n");
					return;
				}

				bzero(car_node->car.plate_number, PLATE_BUFFER_LEN);
				strcpy(car_node->car.plate_number, strtok(line_buffer, ",\n"));

				if (exists(car_node->car.plate_number))
				{
					fprintf(stderr, "/!\\ Duplicate encountered, %s already exists!\n",
							car_node->car.plate_number);
					fprintf(stderr, "Skipping... %s\n", car_node->car.plate_number);
					continue;
				}

				car_node->car.mileage = atoi(strtok(NULL, ",\n"));
				car_node->car.exp_ret_date = atoi(strtok(NULL, ",\n"));

				list_insert(rental_list[i], car_node, i);
			}
			fclose(file);
		}
	}
}

/**
 * prompt_plate_number - prompts and validate plate number from user
 * @plate_number: pointer to where input will be stored
 */
void prompt_plate_number(char *plate_number)
{
	while (true)
	{
		char c;
		int i = 0;
		bool alpha_check = false;
		bool number_check = false;
		bool failed = false;
		char buffer[1024];

		printf(PROMPT_PLATE_NUMBER);
		scanf("%s", buffer);

		bzero(plate_number, PLATE_BUFFER_LEN);

		while ((c = buffer[i]))
		{
			if (i < PLATE_BUFFER_LEN - 1)
			{
				if (isalpha(c))
				{
					alpha_check = true;
					c = toupper(c);
				}
				else if (isdigit(c))
				{
					number_check = true;
				}

				if (!isalnum(c))
				{
					failed = true;
					fprintf(stderr, "/!\\ Input must be Aa-Az and 0-9!\n");
					break;
				}

				plate_number[i++] = c;
			}
			else
			{
				failed = true;
				fprintf(stderr, "/!\\ Input exceeds length limit of 8 characters!\n");
				break;
			}
		}

		if (!failed)
		{
			if (strlen(plate_number) < 2)
				fprintf(stderr, "/!\\ Input length below limit of 2 characters!\n");
			else if (alpha_check && !number_check)
				fprintf(stderr, "/!\\ Input missing at least a number!\n");
			else if (!alpha_check && number_check)
				fprintf(stderr, "/!\\ Input missing at least a letter!\n");
			else if (exists(plate_number))
				fprintf(stderr, "/!\\ Duplicate encountered, %s already exists!\n", plate_number);
			else
				break;
		}
	}
}

/**
 * prompt_date - prompts and validate date from user
 * @date: pointer to where input will be stored
 */
void prompt_date(int *date)
{
	while (true)
	{
		int day, month, year;

		printf("Enter expected return date (yyyymmdd): ");
		scanf("%d", date);

		day = *date % 100;
		month = (*date - day) / 100 % 100;
		year = ((*date - day) / 100 - month) / 100;

		if (day < 1 || day > 31)
		{
			fprintf(stderr, "Day %d is invalid!\n", day);
		}
		else if (month < 1 || month > 12)
		{
			fprintf(stderr, "Month %d is invalid!\n", month);
		}
		else if (year < 1000 || year > 9999)
		{
			fprintf(stderr, "Year %d is invalid!\n", year);
		}
		else
		{
			if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
			{
				fprintf(stderr, "Month %d has only 30 days!\n", month);
			}
			else if (month == 2)
			{
				if (day > 29)
				{
					fprintf(stderr, "Month %d can have only up to 29 days!\n", month);
				}
				else
				{
					if (!is_leap_year(year) && day > 28)
					{
						fprintf(stderr, "Month %d can have only up to 28 days in a leap year (%d)\n", month, year);
						continue;
					}
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}

/**
 * is_leap_year - checks if @year is leap
 * @year: to check for leapness
 *
 * Return: true is @year is leap, otherwise, false
 */
bool is_leap_year(int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

/**
 * exists - checks in @plate_number exists in any of the lists
 * @plate_number: to be check in all three lists
 *
 * Return: true if @plate_number exists, otherwise, false
 */
bool exists(char *plate_number)
{
	for (int i = 0; i < 3; i++)
	{
		car_list_t *tmp = rental_list[i];

		while (tmp)
		{
			if (strcmp(tmp->car.plate_number, plate_number) == 0)
				return (true);
			tmp = tmp->next;
		}
	}
	return (false);
}