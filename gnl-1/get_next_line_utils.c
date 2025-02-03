#include "get_next_line.h"

int	ft_strlen(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_bufjoin(char **buf1, char **buf2, int boolean)
{
	char	*dest;
	int		i;

	i = -1;
	dest = malloc(sizeof(char) * ft_strlen(*buf1) + ft_strlen(*buf2) + 1);
	if (dest)
	{
		while ((*buf1)[i++ + 1] != '\0')
			dest[i] = (*buf1)[i];
		i = -1;
		while ((*buf2)[i++ + 1] != '\0')
			dest[i + ft_strlen(*buf1)] = (*buf2)[i];
		dest[i + ft_strlen(*buf1)] = '\0';
	}
	if (boolean == 0)
		free(*buf1);
	else
		free(*buf2);
	if (!dest)
		return ((char *) 0);
	return (dest);
}

int	find_bs_n_or_free(char **str, int j, int boolean)
{
	int	i;

	if (!(*str))
		return (0);
	if (boolean == 0)
	{
		i = 0;
		while ((*str)[i] != '\n' && (*str)[i] != '\0')
			i++;
		return (i);
	}
	free(*str);
	return (j);
}

char	*cut_str(char **str, int n)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * (ft_strlen(*str) - n));
	if (!dst)
	{
		free(*str);
		return (0);
	}
	while ((*str)[i + n + 1] != '\0')
	{
		dst[i] = (*str)[i + n + 1];
		i++;
	}
	dst[i] = '\0';
	free(*str);
	return (dst);
}

int	start_str(char *str, int n, char **dst)
{
	int		i;

	if (find_bs_n_or_free(&str, 0, 0) == ft_strlen(str))
		n -= 1;
	i = 0;
	*dst = malloc(sizeof(char) * n + 2);
	if (!(*dst))
		return (0);
	while (i <= n)
	{
		(*dst)[i] = str[i];
		i++;
	}
	(*dst)[i] = '\0';
	return (1);
}
