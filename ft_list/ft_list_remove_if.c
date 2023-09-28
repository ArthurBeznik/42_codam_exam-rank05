
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

typedef struct s_list {
	struct s_list	*next;
	void			*data;
}	t_list;

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
