#include "cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	res = (char *)my_malloc((ft_strlen(s1) + 1) * sizeof (char) , 0);
	i = 0;
	while (*s1)
	{
		res[i] = *s1;
		s1++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
