#include "pipex.h"

int ft_strlen(char *s4)
{
    int i;

    i = 0;
	if (!s4)
		return (0);
    while (s4[i] != '\0')
        i++;
    return (i);
}


char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * (1));
		s1[0] = '\0';
	}
	temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (temp == NULL)
		return (NULL);
	while (*s1)
	{
		temp[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		temp[i] = *s2;
		s2++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_strjoin_for_parsing(char *s1, char s2)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * (1));
		s1[0] = '\0';
	}
	temp = malloc(sizeof(char) * (ft_strlen(s1)  + 2));
	if (temp == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		temp[i] = *s1;
		s1++;
		i++;
	}
	temp[i] = s2;
	i++;
	temp[i] = '\0';
	return (temp);
}
//int main(int argc, char *argv[], char *envp[]) change this to command process function
//{
//    char **new_argv;
//    char *new_filename;
//    int i;
//	int	j;
//	int childpid;
//
////	if (argv != 5)
////		return(0);
//	i =  1;
//	new_argv = (char **)malloc(sizeof(char *) * (argc + 1));
//	while (i != argc)
//	{
//		j = 0;
//		childpid = fork();
//		new_filename = "/bin/";
//		
//		new_argv = ft_split(argv[i], " ");
//		new_filename = ft_strjoin(new_filename, new_argv[0]);
////		printf("2222222222222222222222222\n");
////		printf("%s\n", new_argv[1]);
//		if (childpid == 0)
//		{
//			execve(new_filename, new_argv, envp);
//		}
//		wait(&childpid);
//		printf("hello\n");
//		i++;
//		free(new_argv);	
//	}
//}


char *my_parsing_filename(char *new_argv, char *envp[])
{
	int	i;
	int	j;
	char *new_filename;
	char *temp;
	i = 0;
	j = 5;
	new_filename = NULL;
	while (envp[i] != NULL && envp[i][0] != 'P' && envp[i][1] != 'A' && envp[i][2] != 'T' && envp[i][3] != 'H')
		i++;
	while (envp[i][j] != '\0')
	{
		if (envp[i][j] != ':')
		{
			new_filename = ft_strjoin_for_parsing(new_filename, envp[i][j]);
		//	printf("THIS IS ENVP : %c\n", envp[i][j]);
		}
		if (envp[i][j] == ':')
		{
			new_filename = ft_strjoin(new_filename, "/");
			temp = ft_strjoin(new_filename, new_argv);
//			printf("%s\n", temp);
			if (access(temp, F_OK) == 0)
			{
				free(new_filename);
//				printf("%s\n", temp);
				return(temp);
			}
			new_filename = NULL;
			temp = NULL;
		}
		j++;
	}
//
//	printf("%d\n", access(temp, F_OK));
	exit(1);
}

void exec(char *argv, char *envp[])
{
	char **new_argv;
	char *new_filename;

	new_argv = ft_split(argv, " ");
	new_filename = my_parsing_filename(new_argv[0], envp);
	execve(new_filename, new_argv, envp);
}

//void piping(char *argv, char *envp[])
//{
//    char **new_argv;
//    char *new_filename;
//	int childpid;
//	int fd[2];
//	
//	if (pipe(fd) == -1)
//			return ;
//	new_argv = ft_split(argv, " ");
//	new_filename = my_parsing_filename(new_argv[0], envp);
////	printf("this is new_argv : %s, and this is new_file : %s\n", new_argv[0], new_filename);
//	childpid = fork();
//
//	if (childpid)
//	{
//		dup2(fd[0], 0); // stdout, enterence, write
//				close(fd[1]);
//		waitpid(childpid, NULL, 0);
//
//	}
//	else
//	{
//		dup2(fd[1], 1); //stdin, exit, read
//				close(fd[0]);
//		execve(new_filename, new_argv, envp);
//	}
//}




int ft_strchr(char *s, char *c)
{
	char	target;
	int		i;

	i = 0;
	target = c[0];
	while (s[i] != '\0')
	{
		if (s[i] == target)
			return (1);
		i++;
	}
	return (0);
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
		exit(1);
	if (ft_strchr(command[0], "/") == 1)
		filename = command[0];
	else
		filename = my_parsing_filename(command[0], envp);
	childpid = fork();

	if (childpid == 0)
	{
	dup2(fd[1], 1);
	close(fd[0]);
	dup2(file_in, 0);
	execve(filename, command, envp);
	}
	waitpid(childpid, NULL, WNOHANG);
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
		waitpid(childpid, NULL, WNOHANG);
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
