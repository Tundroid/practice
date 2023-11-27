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

void free_list(node_t **head)
{
	node_t *tmp;

	printf("Freeing list...\n");
	while (head && *head)
	{
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
	printf("Done 100%%!\n");
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
	node->next = *head;
	*head = node;
}

void add_node_at_tail(node_t **head, int data)
{
	node_t *node, *tmp;

	if (!head)
		return;
	if (!*head)
	{
		add_node_at_head(head, data);
		return;
	}
	node = malloc(sizeof(node_t));
	if (!node)
		return;
	node->data = data;
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}

void add_node_at_index(node_t **head, int data, int idx)
{
	node_t *node, *tmp;
	int i = 0;

	if (!head)
		return;
	tmp = *head;
	if (idx == 0)
	{
		add_node_at_head(head, data);
		return;
	}
	while (tmp)
	{
		if (i++ == idx - 1)
		{
			node = malloc(sizeof(node_t));
			if (!node)
				return;
			node->data = data;
			node->next = tmp->next;
			tmp->next = node;
			return;
		}
		tmp = tmp->next;
	}
	printf("Invalid index\n");
}
