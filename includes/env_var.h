/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:16:43 by keddib            #+#    #+#             */
/*   Updated: 2021/01/12 16:17:31 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H


/*
** environment variables linked list functions prototypes
*/

t_env_vars			*create_env_var(char *name, char *value);
t_env_vars			*last_env_var(t_env_vars *env_vars);
char				*get_env_name(char *name_value);
char				*get_env_value(char *name_value);
void				add_back_env(t_env_vars **vars, t_env_vars *new_var);
t_env_vars			*build_env_vars(char *envp[]);
t_env_vars			*search_var(t_env_vars **env_vars, char *var_name);
int					change_env_var(t_env_vars **vars, char *var_name, char *new_value);
void				del_env_var(t_env_vars **envs, char *name);
void    			show_env_vars(t_env_vars *vars);
void				free_env_var(t_env_vars *vars);


#endif
