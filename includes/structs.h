/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:13:03 by keddib            #+#    #+#             */
/*   Updated: 2021/04/06 14:41:10 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
** structures prototypes
*/

typedef	struct		s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*previous;
}					t_list;

typedef	struct		s_command
{
	t_list			*name_and_args;
	t_list			*redirections;
	char			built_in;
}					t_command;

typedef struct		s_pipeline
{
	t_list			*cmds;
}					t_pipeline;

typedef struct		s_redirection
{
	char			*file;
	int				type;
}					t_redirection;

typedef struct		s_token
{
	char			*tkn;
	int				id;
}					t_token;

typedef	struct		s_stack
{
	char			character;
	int				meta;
	int				special;
}					t_stack;

typedef struct		s_env_var
{
	char			*name;
	char			*value;
}					t_env_var;

typedef	struct		s_termc
{
	char			*up_key;
	char			*down_key;
	char			*cariage_return;
	char			*clear_line;
	char			*keyend;
	char			*keystart;
}					t_termc;

typedef struct		s_data
{
	t_list			*env_vars;
	t_list			*unset_vars;
	char			*input_cmd;
	t_list			*parse_tree;
	int				exit_status;
	int				in_terminal;
	t_termios		origin;
	t_termios		modified;
	t_list			*history_head;
	t_list			*history_index;
	int				no_status_check;
	t_termc			*termc;
}					t_data;

#endif
