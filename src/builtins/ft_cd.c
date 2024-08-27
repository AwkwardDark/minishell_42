/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:32:47 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/27 18:37:05 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* include "" */

// required includes to put in the .h
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>


// needs the function ft_strtrim
void    ft_cd(char *path)
{
    char *trimed_path;
    char current[100];
    char    *home;

    trimed_path = ft_strtrim(path, " ");
    home = getenv("HOME");
    if (!ft_strcmp(trimed_path, "") && home != NULL)
        chdir(home);
    else if (!opendir(trimed_path))
        perror("minishell");
    else
        chdir(trimed_path);
    free(trimed_path);
    printf("%s\n", getcwd(current, 100));
}

#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    while((input = readline("prompt> ")) != NULL) 
    {
        // Indicate that a new line should be drawn
        if (!strcmp(input, "exit"))
            break ;
        else if (!strncmp(input, "cd", 2))
            ft_cd(&input[2]);
        free(input);
    }
    free(input);
    return 0;
}
