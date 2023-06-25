/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:30:58 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/15 16:39:12 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

void	close_redirection_fds(t_exec_data *data)
{
	safe_close(&data->new_stdout);
	safe_close(&data->new_stdin);
	safe_close(&data->next_stdin);
}

void	free_exec_data(t_exec_data *data)
{
	close_redirection_fds(data);
	free_cmd_list(&data->cmd_list);
	free_heredoc_list(data);
}
