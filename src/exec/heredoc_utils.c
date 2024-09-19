/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:41:15 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/19 15:38:38 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*Adapted version for the verifications, to suit the "$?" case*/
static int	ft_is_special_her(char c)
{
	char	*special;
	int		i;

	i = 0;
	special = "!@#$%^&*()-+=[]{}|\\;:'\"<>,./~` ";
	while (special[i])
	{
		if (c == special[i])
			return (1);
		i++;
	}
	return (0);
}

/*It calculates the length of the variable to expand*/
static int	ft_pre_exp_len(char *line, int i)
{
	int	len;

	len = 0;
	if (line[i] == '?')
		return (1);
	while (line[i] && !ft_is_special(line[i]))
	{
		len++;
		i++;
	}
	return (len);
}

/*It concatenates the new expanded value on the originale string, and deletes
the old non-expanded string*/
static char	*ft_expand_str(char *line, int *i, t_data *data)
{
	int		new_len;
	char	*pre_exp;
	char	*expanded;
	char	*new;
	char	*new_temp;

	pre_exp = ft_extract_exp(line + *i + 1, ft_pre_exp_len(line, *i + 1));
	expanded = ft_find_exp_value(pre_exp, data);
	new_len = ft_strlen(line) + ft_strlen(expanded) - ft_strlen(pre_exp) - 1;
	if (new_len == 0)
		new_len = 1;
	new_temp = ft_create_new_expansion(line, *i, expanded, new_len);
	new = ft_strjoin_expand(new_temp, line + *i + ft_strlen(pre_exp) + 1);
	free(new_temp);
	if (data->free_flag)
		free(expanded);
	free(pre_exp);
	return (new);
}

/*In Heredoc single quoted rules doesnt apply, it creates the string expanded
recursively if there are multiple dollar on a single char */
char	*ft_heredoc_expansion(char *line, int i, t_data *data)
{
	char	*new;

	new = NULL;
	while (line[i])
	{
		if (line[i] == DOLLAR && !ft_is_special_her(line[i + 1]) && line[i + 1])
		{
			new = ft_expand_str(line, &i, data);
			break ;
		}
		i++;
	}
	if (new && !new[0])
		return (free(line), new);
	if (new)
	{
		free(line);
		line = ft_strdup(new);
		free(new);
		new = NULL;
	}
	if (line && line[0] && ft_count_exp(line + i) == 0)
		return (line);
	return (ft_heredoc_expansion(line, i, data));
}
