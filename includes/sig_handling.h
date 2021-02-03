/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:26:58 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/03 11:00:08 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLING_H
# define SIG_HANDLING_H

void	sig_int_handler(int signum);
void	sig_quit_handler(int signum);

#endif
