/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:52:49 by keddib            #+#    #+#             */
/*   Updated: 2021/06/23 17:15:14 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

/*
** $? and $ENV_VAR expansion of single command
*/

void	expand_unquoted_token(t_list **stack, char **token, t_data *data);
void	expand_quotes(t_list **stack, char **token, t_data *data);
void	expand_double_quotes(t_list **stack, char **token, t_data *data);
void	expand_dollar_sign(char **token, t_list **p_stack, t_data *data);
void	handle_expand_env_var(char **token, t_list **p_stack, t_data *data);
void	expand_exit_status(t_list **p_stack, t_data *data, char **token);
void	expand_env_var(t_list **tmp[2], t_list **vars);
void	set_cmd_name(t_command *cmd);
char	*expand(t_list *list, t_data *data);
void	expand_list(t_list *list, t_data *data);
int		expand_redirections(t_list *redirections, t_data *data);
int		expand_cmd(t_list *cmds, t_data *data);
int		expand_pipeline(t_pipeline *pipline, t_data *data);
t_list	*rm_quotes(t_list *tokens);
void		rmq(char *str);

#endif
