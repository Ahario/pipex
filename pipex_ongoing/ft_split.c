#include "pipex.h"

int	check(char str, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (str == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	findsecond(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !(check(str[i], charset)))
		i++;
	return (i);
}

int	findfirst(char *str, char *charset)
{
	int	i;
	int	total;

	total = 0;
	i = 0;
	while (*str)
	{
		while (*str && check(*str, charset))
			str++;
		i = findsecond(str, charset);
		str += i;
		if (i)
			total++;
	}
	return (total);
}

char	*stringcopy(char *str, int j)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * j + 1);
	if (!dest)
		return (0);
	while (i != j && str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	int		j;
	int		total;
	char	**dest;

	i = 0;
	j = 0;
	total = findfirst(str, charset);
	dest = (char **)malloc(sizeof(char *) * total + 1);
	if (!dest)
		return (0);
	while (i < total)
	{
		while (check(*str, charset))
			str++;
		j = findsecond(str, charset);
		dest[i] = stringcopy(str, j);
		str += j;
		i++;
	}
	dest[total] = NULL;
	return (dest);
}