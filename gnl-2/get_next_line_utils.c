#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	f_secure(void *s, void *t)
{
	if (!s)
	{
		if (t)
		{
			free(t);
		}
		return (0);
	}
	return (1);
}

char	*ft_strjoin(char *s1, char *s2, char *buffer)
{
	size_t	size[3];
	char	*str;

	size[2] = 0;
	if ((!f_secure(s1, s2) || !f_secure(s2, s1)) && next_line_buffer(buffer,2))
		return (NULL);
	size[0] = ft_strlen(s1);
	size[1] = ft_strlen(s2);
	str = malloc(sizeof(char) * (size[0] + size[1] + 1));
	if (str == NULL && !f_secure(NULL, s1) && !f_secure(NULL, s2) && next_line_buffer(buffer,2))
		return (NULL);
	while (size[2] < size[0])
	{
		str[size[2]] = s1[size[2]];
		size[2]++;
	}
	while (size[2] < size[0] + size[1])
	{
		str[size[2]] = s2[size[2] - size[0]];
		size[2]++;
	}
	str[size[2]] = 0;
	f_secure(NULL,s1);
	f_secure(NULL,s2);
	return (str);
}

char	*ft_strdup_n(char *s, size_t n, int type)
{
	char	*str;
	size_t	i;

	i = 0;
	if (n == 0 && type == 1)
		n = ft_strlen(s);
	str = malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	if (type == 2)
		f_secure(NULL, s);
	return (str);
}
