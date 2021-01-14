/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:19:15 by abbouzid          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2021/01/14 09:27:13 by keddib           ###   ########.fr       */
=======
/*   Updated: 2021/01/14 09:13:30 by abbouzid         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int     main(void)
{
    pid_t   pid;
    int     status;
<<<<<<< Updated upstream
    char    *argv[2] = {"ls", "."};

=======
    char    *argv[3] = {"ls", "..", NULL};
    
>>>>>>> Stashed changes
    pid = fork();
    if (pid == 0)
    {
        execv("/bin/ls", argv);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        ft_putstr_fd("hiii\n", 1);
    }
    else
    {
        ft_putstr_fd("execv error\n", 1);
    }
    return (0);
}
