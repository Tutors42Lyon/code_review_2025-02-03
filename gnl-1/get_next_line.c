#include "get_next_line.h"

int	malloc_buf(char **buf, int *v_buf, char **end_buf)
{
	if (BUFFER_SIZE < 0)
		return (0);
	if (*v_buf == 1)
	{
		*end_buf = malloc(sizeof(char));
		if (!(*end_buf))
			return (-1);
		*end_buf[0] = '\0';
	}
	*v_buf = 1;
	*buf = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	if (!(*buf))
		return (0);
	return (1);
}

int	treat_text(int *v_buf, char **end_buf, char **buf, char **line)
{
	if (find_bs_n_or_free(buf, 0, 0) != ft_strlen(*buf))
	{
		if (!(start_str(*buf, find_bs_n_or_free(buf, 0, 0), line)))
			return (find_bs_n_or_free(buf, 0, 1));
		*line = ft_bufjoin(end_buf, line, 1);
		if (!(*line))
			return (find_bs_n_or_free(buf, 0, 1));
		free(*end_buf);
		*end_buf = cut_str(buf, find_bs_n_or_free(buf, 0, 0));
		if (!(*end_buf))
			return (find_bs_n_or_free(line, 0, 1));
		if ((*end_buf)[0] == '\0')
		{
			free(*end_buf);
			return (1);
		}
		*v_buf = 0;
		return (1);
	}
	*end_buf = ft_bufjoin(end_buf, buf, 0);
	if (!(*end_buf))
		return (find_bs_n_or_free(buf, 0, 1));
	return (2);
}

int	read_and_write(int fd, char **end_buf, int *v_buf, char **line)
{
	int		ret[2];
	char	*buf;

	ret[0] = malloc_buf(&buf, v_buf, end_buf);
	if (ret[0] <= 0)
		return (ret[0]);
	ret[1] = 1;
	while (ret[1])
	{
		ret[1] = read(fd, buf, BUFFER_SIZE);
		if (ret[1] == -1)
			return (find_bs_n_or_free(&buf, 0, 1));
		buf[ret[1]] = '\0';
		ret[0] = treat_text(v_buf, end_buf, &buf, line);
		if (ret[0] != 2)
			return (ret[0]);
	}
	free(buf);
	if ((*end_buf)[0] != '\0')
		if (!(start_str(*end_buf, find_bs_n_or_free(end_buf, 0, 0), line)))
			return (0);
	if ((*end_buf)[0] != '\0')
		return (find_bs_n_or_free(end_buf, 1, 1));
	return (0);
}

int	clear_end_buf(char **end_buf, char **line, int *v_buf)
{
	int	i;

	i = -1;
	if ((find_bs_n_or_free(end_buf, 0, 0) != ft_strlen(*end_buf)))
	{
		*line = malloc(sizeof(char) * find_bs_n_or_free(end_buf, 0, 0) + 2);
		if (!(*line))
		{
			*v_buf = 1;
			return (find_bs_n_or_free(end_buf, -1, 1));
		}
		while (i++ < find_bs_n_or_free(end_buf, 0, 0))
			(*line)[i] = (*end_buf)[i];
		(*line)[i] = '\0';
		*end_buf = cut_str(end_buf, find_bs_n_or_free(end_buf, 0, 0));
		if (!(*end_buf))
		{
			*v_buf = 1;
			return (find_bs_n_or_free(line, -1, 1));
		}
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*end_buf = NULL;
	int			ret;
	char		*line;
	static int	v_buf = 1;

	if (fd < 0)
		return (0);
	if (v_buf == 1)
		ret = read_and_write(fd, &end_buf, &v_buf, &line);
	else
	{
		ret = clear_end_buf(&end_buf, &line, &v_buf);
		if (ret == -1)
			return (0);
		else if (ret == 0)
			return (line);
		ret = read_and_write(fd, &end_buf, &v_buf, &line);
	}
	if (ret == 0)
		free(end_buf);
	if (ret <= 0)
		return (0);
	return (line);
}
