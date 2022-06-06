#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

int ft_strlen(char *s4);
char	*ft_strjoin(char *s1, char *s2);
int	check(char str, char *charset);
int	findsecond(char *str, char *charset);
int	findfirst(char *str, char *charset);
char	*stringcopy(char *str, int j);
char	**ft_split(char *str, char *charset);
char	*my_parsing_filename(char *new_argv, char *envp[]);
void piping(char *argv, char *envp[]);
char	*ft_strjoin_for_parsing(char *s1, char s2);
void exec(char *argv, char *envp[]);

#endif
