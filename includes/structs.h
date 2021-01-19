/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:13:03 by keddib            #+#    #+#             */
/*   Updated: 2021/01/19 10:57:51 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
** structures prototypes
*/

typedef	struct s_strlist
{
	char 				*str;
	struct s_strlist 	*next;
}				t_strlist;

typedef	struct s_simple_command
{
	char		*cmd_name;
	int			first;
	int 		output_stream;
	t_strlist 	*arguments;
	t_strlist	*infiles;
	t_strlist	*outfiles;
	char 		built_in;
	t_strlist	*append_outfiles;
	struct s_simple_command		*next;
}				t_simple_command;

typedef struct s_pipeline
{
	t_simple_command 	*simple_cmd;
	struct 	s_pipeline  *next;
}				t_pipeline;

typedef  struct s_token
{
	char 	*tkn;
	int		id;
	struct 	s_token *next;
}				t_token;

typedef	struct	s_stack
{
	char				character;
	int 				meta;
	int					special;
	struct 		s_stack *next;

}				t_stack;

typedef struct s_env_vars
{
	char		*name;
	char		*value;
	int			num;
	struct	s_env_vars *next;
}				t_env_vars;

typedef struct s_data
{
	t_env_vars 	*env_vars;
	t_strlist	*unset_vars;
	char		*input_cmd;
	t_pipeline	*parse_tree;
	int			exit_status;
	int			tmp_in;
	int			tmp_out;
}				t_data;

#endif
