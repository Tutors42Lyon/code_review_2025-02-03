#include "get_next_line.h"
#include <unistd.h>

size_t	size_to_sep(char *buffer)
{
	size_t	i;

	// write (1,"b1",2);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i++] == '\n')
			return (i);
	}
	// write (1,"b2",2);
	return (0);
}

int	next_line_buffer(char *buffer, int type)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = size_to_sep(buffer);
	if (type == 2)
		while (j <= BUFFER_SIZE)
			buffer[j++] = 0;
	if (!i)
	{
		while (i <= BUFFER_SIZE)
			buffer[i++] = 0;
	}
	else
	{
		while (buffer[j + i])
		{
			buffer[j] = buffer[j + i];
			j++;
		}
		while (j <= BUFFER_SIZE)
			buffer[j++] = 0;
	}
	return (1);
}

char	*read_line(int fd, char	*buffer)
{
	char		*line;
	char		*bufline;
	ssize_t		bytes_read;

	bufline = ft_strdup_n(buffer, ft_strlen(buffer), 0);
	if (!bufline && next_line_buffer(buffer,2))
		return (NULL);
	if (size_to_sep(bufline))
	{
		next_line_buffer(buffer,1);
		return (ft_strdup_n(bufline, size_to_sep(bufline), 2));
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0 && !f_secure(NULL, bufline) && next_line_buffer(buffer,2))
		return (NULL);
	buffer[bytes_read] = 0;
	line = ft_strdup_n(buffer, size_to_sep(buffer), 1);
	if (!line && !f_secure(NULL, bufline) && next_line_buffer(buffer,2))
		return (NULL);
	line = ft_strjoin(bufline, line, buffer);
	next_line_buffer(buffer,1);
	if (!line || (size_to_sep(line) || bytes_read < BUFFER_SIZE))
		return (line);
	else
		return (ft_strjoin(line, read_line(fd, buffer), buffer));
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0)
		return (NULL);
	line = read_line(fd, buffer);
	if (line && !line[0])
	{
		free(line);
		next_line_buffer(buffer, 2);
		return (NULL);
	}
	return (line);
}
