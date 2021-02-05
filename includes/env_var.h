/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:16:43 by keddib            #+#    #+#             */
/*   Updated: 2021/02/03 10:45:15 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

/*
** environment variables linked list functions prototypes
*/

t_list				*build_env_vars(char **envp);
t_env_var			*create_env_var(char *name, char *value);
char				*get_env_name(char *name_value);
char				*get_env_value(char *name_value);
t_list				*build_env_vars(char *envp[]);
t_env_var			*search_var(t_list **env_vars, char *var_name);
int					change_env_var(t_list **vars, char *var_name,
					char *new_value);
void				free_env_var(void *var);
void				fill_envp(char **envp_i, t_env_var *var);
char				**built_envp(t_list *vars);
void				del_env_var(t_list **vars, char *name);

#endif
