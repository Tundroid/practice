#include "list.h"

int main(void)
{
	node_t *head = NULL;
	int arr0[] = {4, 5, -1, 54, 12};
	int arr1[] = {7, 3, -14, 254, 152};
	int i;

	for (i = 0; i < sizeof(arr0) / sizeof(int); i++)
		add_node_at_head(&head, arr0[i]);
	print_list(head);
	for (i = 0; i < sizeof(arr1) / sizeof(int); i++)
		add_node_at_tail(&head, arr1[i]);
	print_list(head);
	add_node_at_index(&head, 5, 1);
	print_list(head);
	add_node_at_index(&head, 5, 6);
	print_list(head);
	delete_node_at_index(&head, 0);
	print_list(head);
	delete_node_at_head(&head);
	print_list(head);
	delete_node_at_tail(&head);
	print_list(head);
	free_list(&head);
	print_list(head);
	return (0);
}