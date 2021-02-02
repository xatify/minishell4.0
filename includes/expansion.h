/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:52:49 by keddib            #+#    #+#             */
/*   Updated: 2021/02/02 08:56:30 by abbouzid         ###   ########.fr       */
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
void    expand_env_var(t_list **p_stack, t_list **s_stack, t_list **vars, t_list *list);
void    expand_dollar_sign(char **token, t_list **p_stack, t_data *data, t_list *list);
int     expand_double_quotes(t_list **stack, char **token, t_data *data);
int     expand_single_quotes(t_list **stack, char **token);
int     expand_quotes(t_list **stack, char **token, t_data *data);
int     expand_unquoted_token(t_list **stack, char **token, t_data *data, t_list *list);
int	    expand_cmd(t_list *cmds, t_data *data);
int 	expand_list(t_list *list, t_data *data);
char	*expand(t_list *list, t_data *data, int *error);
int     expand_pipeline(t_pipeline *pipline, t_data *data);

#endif
