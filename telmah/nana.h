#ifndef NANA_LIB
#define NANA_LIB

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
void avail_ret_car(void);
void list_insert(car_list_t **, car_list_t *, rental_list_enum_t);
car_list_t *list_remove(car_list_t **, char *, rental_list_enum_t);
void rent_car(void);
void repair_ret_car(void);
void print_inventory(void);
void print_menu(void);
// size_t print_list(const list_t *h);
// size_t list_len(const list_t *h);
// list_t *add_node(list_t **head, const char *str);
// list_t *add_node_end(list_t **head, const char *str);
// void free_list(list_t *head);

#endif
