/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:25:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/29 13:06:12 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type {
	//NONE=0,
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
} t_type;

typedef struct s_token {
	char			**cmd;
	int				len;
	t_type			token_type;
	//t_expand 		*expand;
	struct s_cmd	*next;
	//struct s_cmd	*prev;
}		t_token;

typedef struct s_cmd {
	char		**parsed_cmd;
}	t_cmd;

// typedef struct s_exp {
// 	int			expand;
	//?// char		*value;
	//?// char		*join;
// }	t_exp;

typedef struct s_env {
	char		*key;
	char		*value;
	struct s_env *next;
}	t_env;

// typedef struct s_btree {
// 	void	*content;
// 	struct s_btree	*....
// }

typedef struct s_data {
	struct s_env	*env;
	struct s_cmd	**cmd_tab;
	char			*input;
	int				exit_status;
}		t_data;

#endif
