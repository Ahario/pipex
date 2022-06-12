#include "pipex.h"

int search_PATH(int i, char *envp[])
{
	if(envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
		return (0);
	return(1);
}

char *search_filename(char *command, char *envp[])
{
	int			i;
	int			j;
	char	*filename;

	i = 0;
	j = 5;

	if (ft_strchr(command, "/") == 1)
		filename = command;
	else
		filename = my_parsing_filename(i, j, command, envp);
	return(filename);
}

void free_my_files(char *new_filename, char *temp)
{
	free(new_filename);
	free(temp);
}