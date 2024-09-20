/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:37:07 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/20 15:43:52 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It extracts the old char to expand*/
char	*ft_extract_exp(char *str, int len)
{
	char	*pre_exp;

	pre_exp = ft_calloc(sizeof(char), len + 1);
	if (!pre_exp)
		return (ft_error(7), NULL);
	pre_exp = ft_strncpy(pre_exp, str, len);
	return (pre_exp);
}

/*It creates the new char with the new key value expanded*/
char	*ft_create_new_expansion(char *str, int i, char *expanded, int new_len)
{
	char	*temp;
	char	*new;

	temp = ft_calloc(sizeof(char), new_len + 1);
	if (!temp)
		return (NULL);
	temp = ft_strncpy(temp, str, i);
	new = ft_strjoin_expand(temp, expanded);
	free(temp);
	return (new);
}

/*Once the key value found, it will concatenate token->content with ft_strjoin
and all the intermediate caltulations will be freed*/
static char	*ft_calc_expand(char *str, t_data *data, t_index *x, t_token *curr)
{
	char	*pre_exp;
	char	*expanded;
	char	*new_temp;
	char	*new;
	int		new_len;

	pre_exp = ft_extract_exp(str + x->i + 1, curr->pre_expand[x->j]);
	expanded = ft_find_exp_value(pre_exp, data);
	free(pre_exp);
	new_len = ft_strlen(str) + ft_strlen(expanded) - curr->pre_expand[x->j] - 1;
	if (new_len == 0)
		new_len = 1;
	new_temp = ft_create_new_expansion(str, x->i, expanded, new_len);
	new = ft_strjoin_expand(new_temp, str + x->i + curr->pre_expand[x->j] + 1);
	free(new_temp);
	if (ft_strlen(expanded) > 1)
		x->i += ft_strlen(expanded) - 1;
	free(str);
	str = ft_strdup(new);
	free (new);
	if (data->free_flag)
		free(expanded);
	if (x->j < curr->exp_tab_len)
		(x->j)++;
	return (str);
}

/*It uses the pre_expansion array to extract the char to expand, it will search
on the env list and it will calculate the new length to allocate*/
char	*ft_str_to_exp(char *str, t_data *data, t_token *curr)
{
	t_index	x;
	int		*tab;

	x.i = 0;
	x.j = 0;
	tab = curr->pre_expand;
	while (str[x.i])
	{
		if (str[x.i] == DOLLAR && tab[x.j] != -1)
			str = ft_calc_expand(str, data, &x, curr);
		if (str[x.i] && str[x.i] == '$' && \
			x.j < curr->exp_tab_len && tab[x.j] == -1)
		{
			x.i++;
			x.j++;
		}
		else if (str[x.i] && str[x.i] != DOLLAR)
			x.i++;
	}
	return (str);
}

/*If theres a valid expand on the content, the old content will be free and
if the envviroment variable exits, it will expand on the new char. Otherwise
a null string will replace*/
void	ft_expand(t_token *lst, t_data *data)
{
	t_token	*current;
	char	*result;

	current = lst;
	while (current)
	{
		if (current->token_type == WORD && ft_count_exp(current->content) > 0)
		{
			result = ft_str_to_exp(current->content, data, current);
			if (result)
			{
				current->content = ft_strdup(result);
				free(result);
			}
		}
		if (((current->token_type == R_IN) || (current->token_type == R_OUT) || \
		(current->token_type == APPEND)) && ft_count_exp(current->redir) > 0)
			ft_aux_exp_redir(result, current, data);
		free(current->pre_expand);
		current = current->next;
	}
}
