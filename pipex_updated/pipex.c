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
			free_my_files(new_filename, temp);
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

void	infile_to_command(ft_pipe *my_pipex, char *argv, char *envp[])
{
	int		childpid;

	my_pipex->command = check_command(argv);
	my_pipex->filename = search_filename(my_pipex->command[0], envp);
	childpid = fork();
	if (childpid < 0)
		fork_error();
	if (childpid > 0)
		close(my_pipex->fd[1]);
	else if (childpid == 0)
	{
		dup2(my_pipex->fd[1], 1);
		close(my_pipex->fd[1]);
		close(my_pipex->fd[0]);
		dup2(my_pipex->file_in, 0);
		if (!my_pipex->filename)
		{
			command_error();
			exit(0);
		}
		execve(my_pipex->filename, my_pipex->command, envp);
	}
}

void	command_to_outfile(ft_pipe *my_pipex, char *argv, char *envp[])
{
	int		childpid;

	my_pipex->command = check_command(argv);
	my_pipex->filename = search_filename(my_pipex->command[0], envp);
	if (!my_pipex->filename)
		command_to_outfile_error();
	childpid = fork();
	if (childpid < 0)
		fork_error();
	if (childpid > 0)
		close(my_pipex->fd[0]);
	else if (childpid == 0)
	{
		dup2(my_pipex->fd[0], 0);
		close(my_pipex->fd[0]);
		close(my_pipex->fd[1]);
		dup2(my_pipex->file_out, 1);
		execve(my_pipex->filename, my_pipex->command, envp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	ft_pipe *my_pipex;

	my_pipex = (ft_pipe*)malloc(sizeof(ft_pipe));
	if (argc != 5)
		return (1);
	if (pipe(my_pipex->fd) == -1)
		return (1);
	my_pipex->file_in = open(argv[1], O_RDONLY);
	if (my_pipex->file_in < 0)
		infile_error();
	my_pipex->file_out = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (my_pipex->file_out < 0)
		outfile_error();
	infile_to_command(my_pipex, argv[2], envp);
	command_to_outfile(my_pipex, argv[3], envp);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	close(my_pipex->fd[1]);
	close(my_pipex->fd[0]);
	free(my_pipex->command);
	free(my_pipex->filename);
	free(my_pipex);
	while(1)
		sleep(1);
	return (0);
}
