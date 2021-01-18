/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:41:20 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/18 11:20:46 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// simple implementation of
// ls . | cat -e | 

int main(void)
{
    int    fd[2];
    char *cmd1[] = {"/bin/ls", "ls", ".", NULL};
    char *cmd2[] = {"/bin/cat", "cat", "-e", NULL};
    int    tmp_out;
    int    tmp_in; 
    int     pid;

    tmp_in = dup(0);
    tmp_out = dup(1);
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execl(cmd2[0], cmd2[1], cmd2[2], NULL);
    }else
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[0]);
        execl(cmd1[0], cmd1[1], cmd1[2], NULL);
    }
    return (0);
}