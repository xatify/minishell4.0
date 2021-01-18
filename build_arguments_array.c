/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_arguments_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:26:28 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/18 08:55:44 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int     count_argv(t_strlist *list)
{
    if (list)
    {
        if (list->str)
            return (1 + count_argv(list->next));
        else
            return (count_argv(list->next));
    }
    return (0);
}

void    free_argv(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}    

void    fill_argv(char **argv, t_strlist *args)
{
    int         i;

    i = 1;
    while (args)
    {
        while (!(args->str))
            args = args->next;
        if (!(argv[i] = (char *)malloc(ft_strlen(args->str) + 1)))
        {
            free_argv(argv);
            argv = NULL;
            return;
        }
        ft_strcpy(argv[i], args->str);
        i++;
        args = args->next;
    }
    argv[i] = NULL;
}


char    **built_argv(t_simple_command *cmd)
{
    char    **argv;
    int     argc;

    argc = 2 + count_argv(cmd->arguments);
    if (!(argv = (char **)malloc(argc * sizeof(char *))))
        return (NULL);
    ft_memset(argv, 0, argc * sizeof(char *));
    if (!(argv[0] = (char *)malloc(ft_strlen(cmd->cmd_name) + 1)))
    {
        free(argv);
        return (NULL);
    }
    ft_strcpy(argv[0], cmd->cmd_name);
    fill_argv(argv, cmd->arguments);
    return (argv);
}

int     args_num(char **args)
{
    int num;

    num = 0;
    if (!args)
        return (num);
    while (args[num])
        num++;
    return (num);
}