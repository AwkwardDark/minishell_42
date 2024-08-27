/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:25:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/27 14:54:15 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum	e_cmd_type {
	none,
	s_quote,
	d_quote,
	r_in,
	r_out,
	r_heredoc,
	r_append,
	o_bracket,
	c_bracket,
	pre_exp,
	and,
	or,
	pipe,	
};

typedef struct s_cmd {
	char			*cmd;
	enum e_cmd_type	cmd_type;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_struct {
	t_cmd	*cmd;
}		t_struct;

#endif
