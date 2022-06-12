#include "pipex.h"

char	*my_parsing_filename(int i, int j, char *command, char *envp[])
{
	char	*new_filename;
	char	*temp;

	while (envp[i] != NULL && search_PATH(i, envp))
		i++;
	while (envp[i][j] != '\0')
	{
		if (envp[i][j] != ':')
			new_filename = ft_strjoin_for_parsing(new_filename, envp[i][j]);
		if (envp[i][j] == ':')
		{
			new_filename = ft_strjoin(new_filename, "/");
			temp = ft_strjoin(new_filename, command);
			if (access(temp, F_OK) == 0)
			{
				free(new_filename);
				return (temp);
			}
			new_filename = NULL;
			temp = NULL;
		}
		j++;
	}
	free_my_files(new_filename, temp);
	return (NULL);
}

char	**check_command(char *argv)
{
	char	**command;

	command = ft_split(argv, " ");
	if (ft_strchr(command[0], "/") == 1)
	{
		if (access(command[0], F_OK) == 0)
		{
			return (command);
		}
		free(command);
		return (NULL);
	}
	else
		return (command);
}

void	infile_to_command(int fd[2], int file_in, char *argv, char *envp[])
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
		close(fd[1]);
	else if (childpid == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		dup2(file_in, 0);
		if (!filename)
		{
			command_error();
			exit(0);
		}
		execve(filename, command, envp);
	}
}

void	command_to_outfile(int fd[2], int file_out, char *argv, char *envp[])
{
	int		childpid;
	char	*filename;
	char	**command;

	command = check_command(argv);
	filename = search_filename(command[0], envp);
	if (!filename)
		command_to_outfile_error();
	childpid = fork();
	if (childpid < 0)
		fork_error();
	if (childpid > 0)
		close(fd[0]);
	else if (childpid == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		dup2(file_out, 1);
		execve(filename, command, envp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{

	int	file_in;
	int	file_out;
	int progress;
	int	fd1[2];
	int fd2[2];

	progress = 3;
	if (argc < 5)
		return (1);
	if (pipe(fd1) == -1 || pipe(fd2))
		return (1);
	file_in = open(argv[1], O_RDONLY);
	if (file_in < 0)
		infile_error();
	file_out = open(argv[argc-1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (file_out < 0)
		outfile_error();
	infile_to_command(fd1, file_in, argv[2], envp);
	while (progress != argc - 2)
	{
		command_to_command_1(fd1, fd2, argv[progress], envp);
		command_to_command_2(fd1, fd2, argv[progress], envp);
		progress++;
	}
	command_to_outfile(fd1, file_out, argv[argc-2], envp);
	waitpid(-1, NULL, 0);
	return (0);
}
