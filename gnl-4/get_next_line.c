#include "get_next_line.h"

static int	update_line(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
	tmp = NULL;
	if (!*line)
		return (0);
	return (1);
}

static int	update_remainder(char *buf, char **remainder, char **tmp_remainder)
{
	char	*pointer_n;

	pointer_n = NULL;
	pointer_n = ft_strchr(buf, '\n');
	if (pointer_n && (pointer_n[1]))
	{
		*tmp_remainder = *remainder;
		*remainder = ft_strdup(pointer_n + 1);
		free(*tmp_remainder);
		tmp_remainder = NULL;
		if (!*remainder)
			return (0);
	}
	return (1);
}

static int	read_l(t_line *line, char **res, int fd)
{
	ssize_t	caracters_read;
	char	*tmp_remainder;

	caracters_read = 1;
	while (!line->pointer_n && caracters_read > 0)
	{
		caracters_read = read(fd, line->buf, BUFFER_SIZE);
		if (caracters_read <= 0)
		{
			if (*res != NULL && caracters_read != -1)
				return (1);
			return (0);
		}
		line->buf[caracters_read] = '\0';
		line->pointer_n = ft_strchr(line->buf, '\n');
		if (!update_remainder(line->buf, &line->remainder, &tmp_remainder))
			return (free(*res), *res = NULL, 0);
		if (!update_line(res, line->buf))
			return (free(line->remainder), line->remainder = NULL, 0);
	}
	return (1);
}

static int	handle_remainder(t_line *line, char **res)
{
	char	*tmp_remainder;

	line->pointer_n = ft_strchr(line->remainder, '\n');
	if (line->pointer_n && (line->pointer_n[1]))
	{
		*res = ft_strjoin(*res, line->remainder);
		if (!*res)
			return (free(line->remainder), line->remainder = NULL, 0);
		tmp_remainder = line->remainder;
		line->remainder = ft_strdup(line->pointer_n + 1);
		free(tmp_remainder);
		tmp_remainder = NULL;
		if (!line->remainder)
			return (free(*res), *res = NULL, 0);
	}
	else
	{
		*res = ft_strdup(line->remainder);
		free(line->remainder);
		line->remainder = NULL;
		if (!*res)
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_line	line;
	char			*res;

	res = NULL;
	line.pointer_n = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(line.remainder), line.remainder = NULL, NULL);
	if (line.remainder && !handle_remainder(&line, &res))
		return (NULL);
	if (!read_l(&line, &res, fd))
		return (free(res), free(line.remainder), NULL);
	return (res);
}
