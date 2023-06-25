/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:12:09 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 14:38:42 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

int	pipe_handle(t_exec_data *data)
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (-1);
	data->new_stdout = fd[1];
	data->next_stdin = fd[0];
	return (0);
}

void	safe_close(int	*fd)
{
	if (!*fd)
		return ;
	close(*fd);
	*fd = 0;
}

void	signal_some_mujeres(t_cmd_list *cmd_list)
{
	if (cmd_list && cmd_list->argv[0])
	{
		if (!ft_strncmp(cmd_list->argv[0], "./", 2)
			&& !ft_strrncmp(cmd_list->argv[0], "/minishell", 10))
			run_signal(3);
		else
			run_signal(2);
	}
	else
		run_signal(2);
}

int	ft_strrncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	n--;
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while ((s1[i] || s2[j]) && i > (ft_strlen(s1) - n))
	{
		if (s1[i] != s2[j])
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		i--;
		j--;
	}
	return (0);
}
