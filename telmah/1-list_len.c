#include "lists.h"

/**
* list_len - prints a linked list
* @h: linked list
*
* Return: number of nodes
*/
size_t list_len(const list_t *h)
{
	size_t nodes = 0;

	while (h != NULL)
	{
		h = h->next;
		nodes++;
	}
	return (nodes);
}
