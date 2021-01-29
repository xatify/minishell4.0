/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:19:36 by keddib            #+#    #+#             */
/*   Updated: 2021/01/29 08:11:19 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*
** built-ins
*/

int 	pwd(void);
int     cd(char *path, t_env_vars **vars);
void    exit_(t_data *data, char **argv);
int		env(char *arg0, t_env_vars *env_vars);
int     export(char **args, t_data *data);
int		unset(char **args, t_env_vars **envs);
int     echo(char **args);
char	is_built_in(char *cmd_name);

#endif
