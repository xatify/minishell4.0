/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:52:49 by keddib            #+#    #+#             */
/*   Updated: 2021/01/17 14:59:13 by abbouzid         ###   ########.fr       */
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
void    expand_env_var(t_stack **primary_stack, t_stack **secondary_stack, t_env_vars **vars);
void    expand_dollar_sign(char **token, t_env_vars *vars, int *exit_status, t_stack **primary_stack);
char    *expand_double_quote_token(char **token, t_env_vars *vars, int *exit_status);
char   	*expand_unquoted_token(char *token, t_env_vars *vars, int *exit_status);
int		expand_cmd(t_simple_command *cmd, t_env_vars *vars, int *exit_status);
void	expand_list(t_strlist *list, t_env_vars *vars, int *exit_status);
char	*expand(char **token, t_env_vars *vars, int *exit_status);
int     expand_pipeline(t_pipeline *pipline, t_data *data);

#endif
