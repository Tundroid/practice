#include "list.h"

void print_list(node_t *head)
{
	node_t *tmp = head;

	printf("Printing list...\n\n");
	while (tmp)
	{
		printf("[%d] -> ", tmp->data);
		tmp = tmp->next;
	}
	printf("NULL\n\nDone printing!\n");
}

void add_node_at_head(node_t **head, int data)
{
	node_t *node;

	if (!head)
		return;
	node = malloc(sizeof(node_t));
	if (!node)
		return;
	node->data = data;
	if (*head)
		node->next = *head;
	else
		node->next = NULL;
	*head = node;
}