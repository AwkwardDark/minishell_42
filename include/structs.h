/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:25:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/27 12:05:54 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//typedef
/*
typedef struct s_ecmd {
	
} t_ecmd
*/
typedef struct s_cmd {
	char			**content;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_struct {
	t_cmd	*cmd;
}		t_struct;

#endif
