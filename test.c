/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:19:15 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/13 17:26:18 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int     main(void)
{
    pid_t   pid;
    int     status;
    char    *argv[2] = {"ls", "."};
    
    pid = fork();
    if (pid == 0)
    {
        execv("/bin/ls", NULL);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        printf("hiii\n");
    }
    else
    {
        printf("execv error\n");
    }
    return (0);
}