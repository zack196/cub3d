#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	dup = my_malloc(sizeof (char) * (ft_strlen(str) + 1), 0);
	i = -1;
	while (str[++i])
		dup[i] = str[i];
	dup[i] = 0;
	return (dup);
}
