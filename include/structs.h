/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:25:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/19 15:32:01 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*Used for tokenize each node in the parsing*/
typedef enum e_type {
	WORD=0,
	R_IN=1,
	R_OUT=2,
	HEREDOC=3,
	APPEND=4,
	O_PAR=5,
	C_PAR=6,
	AND=7,
	OR=8,
	PIPE=9,	
}	t_type;

/*Useless structure just to bypass the norminette on the ft_expand function*/
typedef struct s_index {
	int	i;
	int	j;
}		t_index;

/*Double linked list that stores all the information
separated by spaces or special characters*/
typedef struct s_token {
	char			*content;
	t_type			token_type;
	int				*pre_expand;
	int				exp_tab_len;
	int				wildcard;
	int				del_wild_flag;
	int				heredoc_quote_flag;
	char			*redir;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

/*It stores a copy of the enviroment list, used mainly for
the export, expand and unset built-ins*/
typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_btree {
	t_token			*token;
	struct s_btree	*left_child;
	struct s_btree	*right_child;
}	t_btree;

typedef struct s_garbagecolector
{
	int		fds[1000];
	t_btree	*tree;
}	t_gbcolector;

/*Main structure used for sharing information between the
parsing and the execution, also used for some small features
 on error management*/
typedef struct s_data {
	struct s_env	*env;
	struct s_env	*export;
	struct s_token	*token_lst;
	struct s_btree	*b_tree;
	char			*input;
	char			quote_type;
	char			symbol;
	int				exit_status;
	int				lst_exit_status;
	int				free_flag;
	int				heredoc_flag;
	char			*syntax_error;
	int				*child_ps;
	t_gbcolector	*bin;
}		t_data;

typedef struct s_pipe
{
	char			*outfile;
	char			*infile;
	struct s_env	*env;
	int				heredoc;
	char			*limiter;
}	t_pipe;

#endif
