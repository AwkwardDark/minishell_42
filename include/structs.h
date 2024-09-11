/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:25:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/11 15:08:24 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
 
// # define NULL 0
# include "../libft/includes/libft.h"
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# define SIMPLE_COMMAND 2 
# include <errno.h>

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

/*Double linked list that stores all the information
separated by spaces or special characters*/
typedef struct s_token {
	char			*content;
	t_type			token_type;
	int				*pre_expand;
	int				exp_tab_len;
	int				wildcard;
	int				quote_flag;
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

/*Main structure used for sharing information between the
parsing and the execution, also used for some small features
 on error management*/
typedef struct s_data {
	struct s_env	*env;
	struct s_token	*token_lst;
	char			*input;
	char			quote_type;
	char			symbol;
	int				exit_status;
	char			*syntax_error;
}		t_data;

/* Pierre */

typedef struct s_btree {
	t_token			*token;
	struct s_btree	*left_child;
	struct s_btree	*right_child;
}	t_btree;

typedef struct s_pipe
{
	char			*outfile;
	char			*infile;
	struct s_env	*env;
	int				heredoc;
	char			*limiter;
}	t_pipe;

#endif
