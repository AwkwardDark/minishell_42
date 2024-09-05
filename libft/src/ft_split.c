/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:22:57 by pierre            #+#    #+#             */
/*   Updated: 2024/09/05 16:01:33 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "stdio.h"

static int	ft_count_words(char const *s, char c)
{
	int	n;
	int	words;

	words = 0;
	n = 0;
	while (s[n])
	{
		if (n != 0)
		{
			if (s[n] == c && s[n - 1] != c)
				words++;
		}
		n++;
	}
	if (n != 0)
	{
		if (s[n - 1] != c)
			words++;
	}
	return (words);
}

static int	ft_alloc(int idx_ptr, int size, char const *s, char **strs)
{
	int	n;

	n = 0;
	strs[idx_ptr] = (char *)malloc(sizeof(char) * (size + 1));
	if (strs[idx_ptr] == NULL)
		return (idx_ptr);
	while (n < size)
	{
		strs[idx_ptr][n] = s[n];
		n++;
	}
	strs[idx_ptr][n] = '\0';
	return (-1);
}

static int	ft_alloc_words(char const *s, char c, char **strs)
{
	int	idx_ptr;
	int	n;
	int	len;

	idx_ptr = 0;
	n = 0;
	len = 0;
	while (s[n])
	{
		if (n != 0 && s[n] == c && s[n - 1] != c)
		{
			if (ft_alloc(idx_ptr, len, &s[n - len], strs) >= 0)
				return (idx_ptr);
			idx_ptr++;
			len = 0;
		}
		if (s[n] != c)
			len++;
		n++;
	}
	if (s[n - 1] != c)
		return (ft_alloc(idx_ptr, len, &s[n - len], strs));
	return (-1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		words;
	int		ret;

	words = ft_count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (0);
	strs[words] = 0;
	if (words == 0)
		return (strs);
	ret = ft_alloc_words(s, c, strs);
	if (ret >= 0)
	{
		ret--;
		while (ret > 0)
		{
			free(strs[ret]);
			ret--;
		}
		free(strs);
		return (NULL);
	}
	return (strs);
}

/* int main()
{
	char *cmd = "";
	char **s = ft_split(cmd, ' ');

	clear_wordar(s);
	return (0);
}
void	clear_wordar(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
} */
