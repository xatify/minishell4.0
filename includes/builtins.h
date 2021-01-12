/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:19:36 by keddib            #+#    #+#             */
/*   Updated: 2021/01/12 16:20:25 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*
** built-ins
*/

int 	pwd(void);
int		env(t_env_vars *env_vars);
int     export(t_strlist *args, t_env_vars **envs);
int		unset(t_strlist *arguments, t_env_vars **envs);

char	is_build_in(char *cmd_name);

#endif
