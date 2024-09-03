#include "../../include/minishell.h"

int	ft_parenthesis_syntax(char *input)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] && input[i] == O_PAREN)
		{
			count++;
			i++;
		}
		if (input[i] && input[i] == C_PAREN)
		{
			count--;
			i++;
		}
		if (input[i] && input[i] != O_PAREN && input[i] != C_PAREN)
			i++;
		if (count < 0)
			break ;
	}
	if (count < 0)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	if (ac == 2)
		printf("%d\n", ft_parenthesis_syntax(av[1]));
	return (0);
}
