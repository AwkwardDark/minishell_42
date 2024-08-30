# include "../../include/minishell.h"

void ft_extract_word(char *input)
{
	char	*content;
	int		last;
	int		i;
	
	i = 0;
	last = 0;
	while (input[i])
	{
		while (input[i] != ' ' && input[i])
			i++;
		if ()
		content = ft_strndup(input + last, i - last);
		printf("%s\n", content);
		free(content);
		content = NULL;
		if (input[i])
			i++;
		last = i;
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
		ft_extract_word(av[1]);
	return (0);
}
