/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:12:35 by lopayet-          #+#    #+#             */
/*   Updated: 2023/03/18 17:16:11 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

int	handle_redirect(t_cmd_list *cmd_node, t_exec_data *data)
{
	if (cmd_node->redirect == 1)
		if (pipe_handle(data) == -1)
			return (-1);
	if (is_arrow_redirect(cmd_node->redirect))
	{
		if (should_pipe_after_redir_chain(cmd_node))
			if (pipe_handle(data) == -1)
				return (-1);
		if (redir_in_handle(cmd_node, data) == -1
			|| redir_out_handle(cmd_node, data) == -1)
			return (-1);
	}
	return (0);
}

int	redir_out_handle(t_cmd_list *node, t_exec_data *data)
{
	int	fd;

	data->next_cmd = get_next_cmd_node(node);
	fd = get_redir_out_fd(node);
	if (fd < 0)
		return (-1);
	if (!fd)
		return (0);
	safe_close(&data->new_stdout);
	data->new_stdout = fd;
	return (0);
}

int	get_redir_out_fd(t_cmd_list *node)
{
	int			fd;
	int			flags;
	int			does_redirect;
	t_cmd_list	*last_redir_out;

	does_redirect = 0;
	flags = O_WRONLY | O_CREAT;
	while (node && is_arrow_redirect(node->redirect))
	{
		if (node->redirect == 2 || node->redirect == 3)
		{
			does_redirect = 1;
			last_redir_out = node;
		}
		node = node->next;
	}
	if (!does_redirect)
		return (0);
	if (last_redir_out->redirect == 2)
		fd = open(last_redir_out->next->argv[0], flags | O_TRUNC, 0664);
	if (last_redir_out->redirect == 3)
		fd = open(last_redir_out->next->argv[0], flags | O_APPEND, 0664);
	return (fd);
}

int	redir_in_handle(t_cmd_list *node, t_exec_data *data)
{
	int	fd;

	data->next_cmd = get_next_cmd_node(node);
	fd = get_redir_in_fd(node, data);
	if (fd < 0)
		return (-1);
	if (!fd)
		return (0);
	safe_close(&data->new_stdin);
	data->new_stdin = fd;
	return (0);
}

int	get_redir_in_fd(t_cmd_list *node, t_exec_data *data)
{
	int			does_redirect;
	t_cmd_list	*last_redir_in;

	does_redirect = 0;
	while (node && is_arrow_redirect(node->redirect))
	{
		if (node->redirect == 4 || node->redirect == 5)
		{
			does_redirect = 1;
			last_redir_in = node;
		}
		if (node->redirect == 5)
			data->heredoc_index++;
		if (node->next && is_arrow_redirect(node->next->redirect))
			if (redir_touch(node) == -1)
				return (-1);
		node = node->next;
	}
	if (!does_redirect)
		return (0);
	if (last_redir_in->redirect == 4)
		return (open(last_redir_in->next->argv[0], O_RDONLY, 0664));
	if (last_redir_in->redirect == 5)
		return (data->heredoc_list[data->heredoc_index]);
	return (0);
}
