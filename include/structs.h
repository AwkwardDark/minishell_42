/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:25:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/01 11:54:58 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
 
# define NULL 0
# include "../libft/includes/libft.h"
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/*Used for tokenize each node in the parsing*/
typedef enum e_type {
	//NONE=0?,
	S_QUOTE=1,
	d_QUOTE=2,
	R_IN=3,
	R_OUT=4,
	HEREDOC=5,
	APPEND=6,
	O_PAR=7,
	C_PAR=8,
	PRE_EXP=9,
	AND=10,
	OR=11,
	PIPE=12,
	CMD=13
} t_type;

/*Double linked list that stores all the information
separated by spaces or special characters/operators*/
typedef struct s_token {
	char			*content;
	t_type			token_type;
	struct s_token	*next;
	struct s_token	*prev;
	//int				len;
	//t_expand 		*expand;
}		t_token;

/*It stores a copy of the enviroment list, used mainly for
the export, exand and unset built-ins*/
typedef struct s_env {
	char		*key;
	char		*value;
	struct s_env *next;
}	t_env;

typedef struct s_btree {
	t_token			*token;
	struct s_btree	*left_child;
	struct s_btree	*right_child;
}	t_btree;

/*Main structure used for sharing information between the
parsing and the execution*/
typedef struct s_data {
	struct s_env	*env;
	struct s_token	*token_lst;
	char			*input;
	int				exit_status;
}		t_data;

#endif
