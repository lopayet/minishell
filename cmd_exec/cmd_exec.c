/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:56:49 by vpac              #+#    #+#             */
/*   Updated: 2023/04/21 14:42:07 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

static void	rec_cmd_exec(t_cmd_list *cmd_list, t_var_list **var_list,
				t_exec_data *data);
static void	set_exit_status(t_exec_data data, int wait_res);
static int	get_cmd_amount(t_cmd_list *cmd_node);
static void	cmd_exec_cleanup(t_exec_data *data);

int	cmd_exec(t_cmd_list *cmd_list, t_var_list **var_list)
{
	t_exec_data	data;
	int			res;

	ft_bzero(&data, sizeof(t_exec_data));
	data.cmd_list = cmd_list;
	data.is_first_cmd = 1;
	data.cmd_amount = get_cmd_amount(cmd_list);
	if (make_heredoc_list(cmd_list, &data) != 0)
		return (perror(MINISHELL_STR), 0);
	signal_some_mujeres(cmd_list);
	rec_cmd_exec(cmd_list, var_list, &data);
	cmd_exec_cleanup(&data);
	if (data.last_pid)
		waitpid(data.last_pid, &res, WUNTRACED);
	data.forks--;
	while (data.forks-- > 0)
		waitpid(-1, NULL, WUNTRACED);
	run_signal(1);
	set_exit_status(data, res);
	return (data.exit);
}

static void	rec_cmd_exec(t_cmd_list *cmd_node, t_var_list **var_list,
	t_exec_data *data)
{
	if (cmd_node)
	{
		data->next_cmd = cmd_node->next;
		if (handle_redirect(cmd_node, data) == -1)
		{
			perror(MINISHELL_STR);
			return ;
		}
		run(cmd_node->argv, var_list, data);
		safe_close(&data->new_stdout);
		safe_close(&data->new_stdin);
		data->new_stdin = data->next_stdin;
		data->next_stdin = 0;
		if (data->next_cmd)
			data->is_first_cmd = 0;
		rec_cmd_exec(data->next_cmd, var_list, data);
	}
}

static void	set_exit_status(t_exec_data data, int wait_res)
{
	if (!data.last_is_fork)
		return ;
	if (WIFEXITED(wait_res))
		g_exit_status = WEXITSTATUS(wait_res);
	if (WIFSIGNALED(wait_res))
		g_exit_status = 128 + WTERMSIG(wait_res);
}

static int	get_cmd_amount(t_cmd_list *cmd_node)
{
	int	res;

	res = 1;
	while (cmd_node)
	{
		if (cmd_node->redirect == 1)
			res++;
		cmd_node = cmd_node->next;
	}
	return (res);
}

static void	cmd_exec_cleanup(t_exec_data *data)
{
	safe_close(&(data->new_stdout));
	safe_close(&(data->new_stdin));
	safe_close(&(data->next_stdin));
	free_heredoc_list(data);
}
