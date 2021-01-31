/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:52:49 by keddib            #+#    #+#             */
/*   Updated: 2021/01/31 07:36:31 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

/*
** $? and $ENV_VAR expansion of single command
*/

bool    is_single_quote_token(char *token);
bool    is_double_quote_token(char *token);
char    *expand_single_quote_token(char **token);
void    expand_env_var(t_stack **p_stack, t_stack **s_stack, t_env_vars **vars, t_strlist *list);
void    expand_dollar_sign(char **token, t_stack **p_stack, t_data *data, t_strlist *list);
char    *expand_double_quote_token(char **token, t_data *data, t_strlist *list);
int     expand_unquoted_token(t_stack **stack, char **token, t_data *data, t_strlist *list);
int	    expand_cmd(t_command *cmd, t_data *data);
int 	expand_list(t_strlist *list, t_data *data);
char	*expand(t_strlist *list, t_data *data, int *error);
void     expand_pipeline(t_pipeline *pipline, t_data *data);

#endif
