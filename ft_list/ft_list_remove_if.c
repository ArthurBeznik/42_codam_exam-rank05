
/*

struct s_list {
	struct s_list *next;
	void *data;
}	t_list;

ft_list_remove_if(t_list **begin_list, void *data_ref, void (*cmp)())

remove the elements of the list where the data is equal to the data_ref

cmp takes in two void *, and returns 0 if they are equal, 1 otherwise.

*/

#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

typedef struct s_list {
	struct s_list	*next;
	void			*data;
}	t_list;

int	cmp(void *data, void *ref) {
	if (data == ref)
		return 0;
	return 1;
}

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *)) {
    t_list *current = *begin_list;
    t_list *prev = NULL;

    while (current) {
        if (cmp(current->data, data_ref) == 0) {
            // Data matches, remove the element
            if (prev) {
                prev->next = current->next;
                free(current);
                current = prev->next;
            } else {
                // Removing the first element of the list
                *begin_list = current->next;
                free(current);
                current = *begin_list;
            }
        } else {
            // Data doesn't match, move to the next element
            prev = current;
            current = current->next;
        }
    }
}

int	main(void) {
	t_list *list = malloc(sizeof(t_list));

	list->data = "1";
	list->next = NULL;

	t_list	*one = malloc(sizeof(t_list));
	one->data = "2";
	one->next = NULL;

	t_list *two = malloc(sizeof(t_list));
	two->data = "1";
	two->next = NULL;

	t_list *three = malloc(sizeof(t_list));
	three->data = "3";
	three->next = NULL;

	list->next = one;
	list->next->next = two;
	list->next->next->next = three;

	t_list *tmp = list;
	printf("START\n");
	while (tmp) {
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}

	ft_list_remove_if(&list, "1", *cmp);

	printf("\nEND\n");
	while (list) {
		printf("%s\n", list->data);
		list = list->next;
	}

	return 0;
}
