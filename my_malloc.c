#include "cub3d.h"

void	my_free(t_g_data **g_data)
{
	t_g_data	*tmp;

	while (*g_data)
	{
		tmp = *g_data;
		*g_data = (*g_data)->next;
		free(tmp->data);
		free(tmp);
	}
}

void	*my_malloc(size_t size, int free_mode)
{
	static t_g_data	*g_data;
	t_g_data		*new;

	if (!free_mode)
	{
		new = malloc(sizeof (t_g_data));
		if (!new)
		    return (my_free(&g_data), exit(1), NULL);
		new->data = malloc(size);
		if (!new->data)
		    return (my_free(&g_data), exit(1), NULL);
		new->next = g_data;
		return (new->data);
	}
	else
		return (my_free(&g_data), NULL);
}

