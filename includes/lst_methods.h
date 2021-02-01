/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_methods.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 08:06:13 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/01 17:52:26 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_METHODES_H
# define LST_METHODES_H


t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_front(t_list **alst, t_list *new_);
void	ft_lstadd_back(t_list **alst, t_list *new_);
#endif
