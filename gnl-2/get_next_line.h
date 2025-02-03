#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# elif BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdlib.h>

char	*get_next_line(int fd);

char	*ft_strjoin(char *s1, char *s2, char *buffer);
char	*ft_strdup_n(char *s, size_t n, int type);
size_t	ft_strlen(const char *s);
int		f_secure(void *s, void *t);
int		next_line_buffer(char *buffer, int type);

#endif