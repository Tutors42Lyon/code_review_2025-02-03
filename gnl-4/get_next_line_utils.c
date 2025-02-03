#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dest;

	if (!s)
		return (NULL);
	dest = (char *)malloc(ft_strlen(s)+1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len ++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	char			*str;
	int				i;

	if (s == NULL)
		return (NULL);
	ch = (unsigned char)c;
	i = 0;
	str = (char *)s;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return (&str[i]);
		i ++;
	}
	if (str[i] == ch)
		return (&str[i]);
	return (NULL);
}

size_t	process_s2(const char *s2)
{
	size_t	len_s2;
	char	*pointer_n;

	len_s2 = 0;
	pointer_n = NULL;
	if (s2)
	{
		pointer_n = ft_strchr(s2, '\n');
		while (s2[len_s2] && s2[len_s2] != '\n')
			len_s2 ++;
		if (pointer_n)
			len_s2 ++;
	}
	return (len_s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	len_s1 = 0;
	len_s2 = 0;
	str = NULL;
	if (s1)
		len_s1 = ft_strlen(s1);
	if (s2)
		len_s2 = process_s2(s2);
	str = (char *)malloc(len_s1 + len_s2 + 1);
	if (!str)
		return (NULL);
	while (s1 && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] && j < len_s2)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
