# include "../../include/minishell.h"

void ft_extract_word(char *input, t_data *data)
{
	char	*content;
	int		start;
	int		end;
	int		i;
	
	i = 0;
	start = 0;
	end = 0;
	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		if (!input[i])
			break ;
		start = i;
		while (input[i] != ' ' && input[i])
		{
			if (is_quote(input[i], data))
			{
				while(input[i + 1] != data->quote_type)
					i++;
				i++;
			}
			if (is_special(input, &i))
				break ;
			i++;
		}
		end = i;
		content = ft_strndup(input + start, end - start);
		printf("%s\n", content);
		free(content);
		content = NULL;
	}
}

int main(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (ac == 2)
		ft_extract_word(av[1], data);
	return (0);
}
