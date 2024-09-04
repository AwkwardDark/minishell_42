/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:25:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/04 18:46:31 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*Used for tokenize each node in the parsing*/
typedef enum e_type {
	WORD=0,
	IN_R=1,
	OUT_R=2,
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
//TODO: Add redir, expand or wildcar metadata?
typedef struct s_token {
	char			*content;
	t_type			token_type;	
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

#endif
