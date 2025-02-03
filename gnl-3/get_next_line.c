#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0)
		return (NULL);
	line = read_line(buffer, fd);
	if (line && !line[0])
		return (free(line), NULL);
	return (line);
}

char	*read_line(char *buffer, int fd)
{
	int		bytes_read;
	size_t	nb_read;
	t_gnl	*lst;

	lst = NULL;
	lst = add_elem_lst(lst, gnl_copy(buffer), 1);
	if (!lst)
		return (NULL);
	nb_read = gnl_strlen(buffer);
	decal_buffer(buffer);
	bytes_read = BUFFER_SIZE;
	while ((lst && !have_n(lst->content)) && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (empty_lst(lst, 0, 0, 0));
		nb_read += gnl_strlen(buffer);
		lst = add_elem_lst(lst, gnl_copy(buffer), 1);
		if (!lst)
			return (NULL);
		decal_buffer(buffer);
	}
	return (empty_lst(lst, 1, nb_read, 0));
}

void	decal_buffer(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = gnl_strlen(buffer);
	while (buffer[j + i])
	{
		buffer[i] = buffer[i + j];
		i++;
	}
	while (buffer[i])
		buffer[i++] = 0;
}

int	have_n(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
