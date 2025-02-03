#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
int		ft_strlen(char const *str);
char	*ft_bufjoin(char **buf1, char **buf2, int boolean);
int		find_bs_n_or_free(char **str, int j, int boolean);
char	*cut_str(char **str, int n);
int		start_str(char *str, int n, char **dst);
#endif
