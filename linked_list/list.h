#ifndef NANA_LIST_H
#define NANA_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
	int data;
	struct node_s *next;
} node_t;

void print_list(node_t *);
void free_list(node_t **);
void add_node_at_head(node_t **, int);
void add_node_at_tail(node_t **, int);
void add_node_at_index(node_t **, int, int);
void delete_node_at_head(node_t **);
void delete_node_at_tail(node_t **);
void delete_node_at_index(node_t **head, int idx);

#endif
