#include "lists.h"

/**
* add_node_end - adds a node to the end of a linked list
* @head: of linked list
* @str: string to node add to list
*
* Return: address of new node or null on failure
*/
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *node = malloc(sizeof(list_t));
	list_t *tmp = *head;

	if (node != NULL)
	{
		node->str = strdup(str);
		node->len = strlen(str);
		if (*head == NULL)
		{
			*head = node;
		}
		else
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = node;
		}
	}
	return (node);
}
