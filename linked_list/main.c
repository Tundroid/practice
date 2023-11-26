#include "list.h"

int main(void)
{
	node_t *head = NULL;
	int arr[] = {4, 5, -1, 54, 12};
	int i;

	for (i = 0; i < sizeof(arr) / sizeof(int); i++)
		add_node_at_head(&head, arr[i]);
	print_list(head);
	return (0);
}