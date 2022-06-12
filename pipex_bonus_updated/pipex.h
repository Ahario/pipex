#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

#include "pipex.h"

int	check(char const str, char *charset);
int	findsecond(char const *str, char *charset);
int	findfirst(char const *str, char *charset);
char	**malloc_free(char **all);
char	**ft_split(char const *s, char *c);
int ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*my_parsing_filename(int i, int j, char *command, char *envp[]);
char **check_command(char *argv);
void infile_to_command(int fd[2], int file_in, char *argv, char *envp[]);
void command_to_outfile(int fd[2], int file_out, char *argv, char *envp[]);
int main(int argc, char *argv[], char *envp[]);
int ft_strlen(char *s4);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_for_parsing(char *s1, char s2);
int ft_strchr(char *s, char *c);
void infile_error();
void outfile_error();
void command_error();
void fork_error();
void pipe_error();
void execve_error();
void command_to_outfile_error();
int search_PATH(int i, char *envp[]);
char *search_filename(char *command, char *envp[]);
void free_my_files(char *new_filename, char *temp);
void	command_to_command_2(int fd1[2], int fd2[2], char *argv, char *envp[]);
void	command_to_command_1(int fd1[2], int fd2[2], char *argv, char *envp[]);

#endif