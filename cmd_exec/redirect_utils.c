/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:11:41 by lopayet-          #+#    #+#             */
/*   Updated: 2023/03/18 17:11:57 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

int	is_arrow_redirect(int delimiter)
{
	return (delimiter == 2 || delimiter == 3
		|| delimiter == 4 || delimiter == 5);
}

int	should_pipe_after_redir_chain(t_cmd_list *node)
{
	while (node && is_arrow_redirect(node->redirect))
		node = node->next;
	if (node->redirect == 1)
		return (1);
	return (0);
}

int	redir_touch(t_cmd_list *node)
{
	int	fd;

	if (node->redirect == 2)
		fd = open(node->next->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (node->redirect == 3)
		fd = open(node->next->argv[0], O_WRONLY | O_CREAT | O_APPEND, 0664);
	else if (node->redirect == 4)
		fd = open(node->next->argv[0], O_RDONLY, 0664);
	else
		return (0);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

t_cmd_list	*get_next_cmd_node(t_cmd_list *node)
{
	while (node && is_arrow_redirect(node->redirect))
		node = node->next;
	if (node)
		return (node->next);
	return (node);
}
