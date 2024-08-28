/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:25:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 13:48:48 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type {
	NONE=0,
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
};

typedef struct s_token {
	char			*cmd;
	int				flag;
	struct e_type	token_type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}		t_token;

typedef struct s_cmd {
	char		**parsed_cmd;
}	t_cmd;

// typedef struct s_btree {
// 	void	*content;
// 	struct s_btree	*....
// }

typedef struct s_data {
	t_cmd			*cmd;
	char			**env;
	struct s_cmd	**cmd_tab;
	char			*input;
}		t_data;

#endif
