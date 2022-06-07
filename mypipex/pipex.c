#include "pipex.h"

char *my_parsing_filename(char *new_argv, char *envp[])
{
	int	i;
	int	j;
	char *new_filename;
	char *temp;
	i = 0;
	j = 5;
	new_filename = NULL;
	while (envp[i] != NULL && !(envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H'))
		i++;
	while (envp[i][j] != '\0')
	{
		if (envp[i][j] != ':')
			new_filename = ft_strjoin_for_parsing(new_filename, envp[i][j]);
		if (envp[i][j] == ':')
		{
			new_filename = ft_strjoin(new_filename, "/");
			temp = ft_strjoin(new_filename, new_argv);
			if (access(temp, F_OK) == 0)
			{
				free(new_filename);
				return(temp);
			}
			new_filename = NULL;
			temp = NULL;
		}
		j++;
	}
	exit(7);
}

char **check_command(char *argv)
{
	char **command;

	command = ft_split(argv, " ");
	if (ft_strchr(command[0], "/") == 1)
	{
		if (access(command[0], F_OK) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	else
		return (command);
}

void infile_to_command(int fd[2], int file_in, char *argv, char *envp[])
{
	int childpid;
	char *filename;
	char **command;

	command = check_command(argv);
	if (!command)
		exit(4);
	if (ft_strchr(command[0], "/") == 1)
		filename = command[0];
	else
		filename = my_parsing_filename(command[0], envp);
	childpid = fork();

	if (childpid == 0)
	{
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
	dup2(file_in, 0);
	execve(filename, command, envp);

	printf("error: no such file: %s", filename);
	exit(777);
	}
}

void command_to_outfile(int fd[2], int file_out, char *argv, char *envp[])
{
	int childpid;
	char *filename;
	char **command;

	command = check_command(argv);
	if (!command)
		exit(1);
	if (ft_strchr(command[0], "/") == 1)
		filename = command[0];
	else
		filename = my_parsing_filename(command[0], envp);
	childpid = fork();
	if (childpid == 0)
	{
	dup2(fd[0], 0);
	close(fd[1]);
	dup2(file_out, 1);
	execve(filename, command, envp);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	int file_in;
	int file_out;
	int fd[2];
	if (argc != 5 )
		return (1);
	if (pipe(fd) == -1)
		return 1;
	file_in = open(argv[1], O_RDONLY);
	if (file_in < 0)
	{
		perror("hahahahahaha");
		return (1);
	}
	file_out = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (file_out < 0)
	{
		perror("hehehehehehe");
		return (1);
	}
	infile_to_command(fd, file_in, argv[2], envp);
	command_to_outfile(fd, file_out, argv[3], envp);
	close(fd[1]);
	close(fd[0]);
	return (0);
}
