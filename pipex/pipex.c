# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

int ft_strlen(char *s4)
{
    int i;

    i = 0;
    while (s4[i] != '\0')
        i++;
    return (i);
}


char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
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
//   printf("11111111111111111\n");
//   printf("s1 : %s s2 : %s temp : %s\n", s1, s2, temp);
	return (temp);
}

int main(int argc, char *argv[], char *envp[])
{
    char **new_argv;
    char *new_filename;
    int i;
	int childpid;

	new_argv = (char **)malloc(sizeof(char *) * (argc + 1));
	childpid = fork();

    new_filename = "/bin/";

    for(i = 1; i < argc; i++)
    {
        new_argv[i-1] = argv[i];
    }
    new_filename = ft_strjoin(new_filename, argv[1]);
    new_argv[i] = NULL;
	if (childpid == 0)
	{
    	execve(new_filename, new_argv, envp);
	}
	wait(&childpid);
	printf("hello\n");
}