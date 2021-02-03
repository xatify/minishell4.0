/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 09:52:49 by keddib            #+#    #+#             */
/*   Updated: 2021/02/03 10:54:24 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

/*
** $? and $ENV_VAR expansion of single command
*/

BOOL	is_single_quote_token(char *token);
BOOL	is_double_quote_token(char *token);
void	expand_new_tokens(char *tkn, t_list **p_stack, t_list **new_args);
void	expand_token_list(t_list *list, t_env_var *env_var, t_list **p_stack);
void	expand_env_var(t_list **p_stack, t_list **s_stack, t_list **vars,
		t_list *list);
void	expand_exit_status(t_list **p_stack, t_data *data, char **token);
void	handle_expand_env_var(char **token, t_list **p_stack, t_data *data,
		t_list *list);
void	expand_dollar_sign(char **token, t_list **p_stack, t_data *data,
		t_list *list);
int		handle_ut_non_special(t_list **stack, char **token);
void	handle_ut_back_slash(t_list **stack, char **token,
		int *first_back_slash);
int		handle_ut_dollar_sign(t_list **stack, char **token, t_data *data,
		t_list *list);
int		ret_expand_ut(t_list **stack);
int		expand_unquoted_token(t_list **stack, char **token, t_data *data,
		t_list *list);
int		handle_dq_non_special(t_list **stack, char **token);
void	handle_dq_back_slack(t_list **stack, char **token,
		int *first_back_slash);
int		handle_dq_dollar_sign(t_list **stack, char **token, t_data *data);
int		expand_double_quotes(t_list **stack, char **token, t_data *data);
int		expand_single_quotes(t_list **stack, char **token);
int		expand_quotes(t_list **stack, char **token, t_data *data);
char	*handle_expansion(t_list **stack, int error);
char	*expand(t_list *list, t_data *data, int *error);
int		expand_list(t_list *list, t_data *data);
int		expand_cmd(t_list *cmds, t_data *data);
int		expand_pipeline(t_pipeline *pipline, t_data *data);

#endif
