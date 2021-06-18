/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:19:36 by keddib            #+#    #+#             */
/*   Updated: 2021/06/18 08:04:01 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*
** built-ins
*/

int		cd(char *path, t_data *data);
int		exit_(t_data *data, char **argv);
int		env(char *arg0, t_list *env_vars);
int		export(char **args, t_data *data);
int		unset(char **args, t_list **envs);
int		echo_(char **args);
char	is_built_in(t_list *name_arg);
int		pwd(t_data *data);

#endif
