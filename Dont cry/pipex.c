/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:57:44 by hyeo              #+#    #+#             */
/*   Updated: 2022/06/13 14:52:19 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*my_parsing_filename(int i, int j, char *command, char *envp[])
{
	char	*new_filename;
	char	*temp;

	new_filename = NULL;
	while (envp[i][j] != '\0')
	{
		if (envp[i][j] != ':')
		{
			temp = ft_strjoin_for_parsing(new_filename, envp[i][j]);
			free(new_filename);
			new_filename = temp;
		}
		if (envp[i][j] == ':')
		{
			temp = ft_strjoin(new_filename, command);
			free(new_filename);
			if (access(temp, F_OK) == 0)
				return (temp);
			free(temp);
			new_filename = NULL;
			temp = NULL;
		}
		j++;
	}
	temp = ft_strjoin(new_filename, command);
	free(new_filename);
	if (access(temp, F_OK) == 0)
		return (temp);
	free(temp);
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

void	infile_to_command(t_pipe *my_pipex, char *argv, char *envp[])
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
		execve_error();
	}
}

void	command_to_outfile(t_pipe *my_pipex, char *argv, char *envp[])
{
	int		childpid;

	my_pipex->command = check_command(argv);
	my_pipex->filename = search_filename(my_pipex->command[0], envp);
	if (!my_pipex->filename)
	{
		free_my_pipex(my_pipex);
		free(my_pipex);
		command_to_outfile_error();
	}
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
		execve_error();
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	*my_pipex;

	my_pipex = (t_pipe *)malloc(sizeof(t_pipe));
	if (argc != 5)
	{	
		file_number_error();
		exit(127);
	}
	if (pipe(my_pipex->fd) == -1)
		return (1);
	my_pipex->file_in = open(argv[1], O_RDONLY);
	if (my_pipex->file_in < 0)
		infile_error();
	my_pipex->file_out = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (my_pipex->file_out < 0)
		outfile_error();
	infile_to_command(my_pipex, argv[2], envp);
	free_my_pipex(my_pipex);
	command_to_outfile(my_pipex, argv[3], envp);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	close(my_pipex->fd[1]);
	close(my_pipex->fd[0]);
	free_my_pipex(my_pipex);
	free(my_pipex);
	return (0);
}
