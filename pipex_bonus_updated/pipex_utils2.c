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

void	command_to_command_1(int fd1[2], int fd2[2], char *argv, char *envp[])
{
	int		childpid;
	char	*filename;
	char	**command;

	command = check_command(argv);
	filename = search_filename(command[0], envp);
	childpid = fork();
	if (childpid < 0)
		fork_error();
	if (childpid > 0)
	{
		close(fd1[1]);
	}
	else if (childpid == 0)
	{
		dup2(fd1[1], 0);
		dup2(fd2[0], 1);
		close(fd1[1]);
		close(fd2[0]);
		if (!filename)
		{
			command_error();
			exit(0);
		}
		execve(filename, command, envp);
	}
}

void	command_to_command_2(int fd1[2], int fd2[2], char *argv, char *envp[])
{
	int		childpid;
	char	*filename;
	char	**command;

	command = check_command(argv);
	filename = search_filename(command[0], envp);
	childpid = fork();
	if (childpid < 0)
		fork_error();
	if (childpid > 0)
	{
		close(fd2[1]);
	}
	else if (childpid == 0)
	{
		dup2(fd2[1], 0);
		dup2(fd1[0], 1);
		if (!filename)
		{
			command_error();
			exit(0);
		}
		execve(filename, command, envp);
	}
}
