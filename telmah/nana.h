#ifndef NANA_LIB
#define NANA_LIB

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define FLAT_RATE 80.0f
#define FLAT_RATE_KM_MAX 200
#define EXTRA_RATE_PER_KM 0.15f

/**
 * struct car - singly linked list
 * @plate_number: car plate number
 * @mileage: current odometer reading
 * @exp_ret_date: expected return date of rented car
 *
 * Description: structure for rental cars
 */
typedef struct car
{
	char plate_number[10];
	int mileage;
	int exp_ret_date;
} car_t;

/**
 * struct car_list - singly linked list for rental cars
 * @car: struct car
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct car_list
{
	car_t car;
	struct car_list *next;
} car_list_t;

/**
 * enum rental_list_enum - enumeration for rental list types
 * @AVAILABE: for available cars
 * @RENTED: for rented cars
 * @IN_REPAIR: for cars in repair
 *
 * Description: singly linked list node structure
 */
typedef enum rental_list_enum
{
	AVAILABE,
	RENTED,
	IN_REPAIR
} rental_list_enum_t;

extern car_list_t *available_head;
extern car_list_t *rented_head;
extern car_list_t *repair_head;

void add_new_car(void);
void avail_rep_car(void);
void list_insert(car_list_t **, car_list_t *, rental_list_enum_t);
car_list_t *list_remove(car_list_t **, char *, rental_list_enum_t);
void rent_car(void);
void return_car(rental_list_enum_t);
void print_inventory(void);
void print_menu(void);

#endif
