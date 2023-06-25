/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:10:55 by lopayet-          #+#    #+#             */
/*   Updated: 2023/03/18 17:11:30 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

int	get_heredoc_amount(t_cmd_list *cmd_list)
{
	int	amount;

	amount = 0;
	while (cmd_list)
	{
		if (cmd_list->redirect == 5)
			amount++;
		cmd_list = cmd_list->next;
	}
	return (amount);
}

int	init_heredoc_list(t_cmd_list *cmd_list, t_exec_data *data)
{
	int	amount;
	int	size;

	amount = get_heredoc_amount(cmd_list);
	if (amount == 0)
		return (0);
	size = sizeof(int) * (amount);
	data->heredoc_list = malloc(size);
	data->heredoc_amount = amount;
	if (!data->heredoc_list)
		return (-1);
	ft_bzero(data->heredoc_list, size);
	return (0);
}

int	make_heredoc(int *pipe_in, char *pattern)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (-1);
	line = 0;
	while (1)
	{
		line = rl_get("> ", 0);
		if (!line)
			return (close(fd[0]), close(fd[1]), -1);
		if (!ft_strcmp(line, pattern))
			break ;
		line = ft_strjoin_free(line, "\n");
		if (!line)
			return (close(fd[0]), close(fd[1]), -1);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	*pipe_in = fd[0];
	free(line);
	return (close(fd[1]), 0);
}

int	make_heredoc_list(t_cmd_list *cmd_list, t_exec_data *data)
{
	int	i;

	i = 0;
	if (init_heredoc_list(cmd_list, data) != 0)
		return (-1);
	while (cmd_list)
	{
		if (cmd_list->redirect == 5)
		{
			if (make_heredoc(data->heredoc_list + i,
					cmd_list->next->argv[0]) != 0)
				return (-1);
			i++;
		}
		cmd_list = cmd_list->next;
	}
	data->heredoc_index = -1;
	return (0);
}

void	free_heredoc_list(t_exec_data *data)
{
	int	i;

	if (!data->heredoc_list)
		return ;
	i = -1;
	while (++i < data->heredoc_amount)
		safe_close(&data->heredoc_list[i]);
	free(data->heredoc_list);
}
