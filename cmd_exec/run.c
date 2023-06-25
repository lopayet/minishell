/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:48:51 by vpac              #+#    #+#             */
/*   Updated: 2023/04/15 17:40:24 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

static char	*find_value(char *key, char **char_env)
{
	int	i;

	i = -1;
	while (char_env[++i])
	{
		if (!ft_strncmp(char_env[i], key, ft_strlen(key)))
			return (char_env[i] + ft_strlen(key) + 1);
	}
	return (0);
}

static char	*find_path(char *cmd, char **char_env)
{
	int			i;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	file_stat;

	temp = find_value("PATH", char_env);
	paths = ft_split(temp, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin("/", cmd);
		new_path = ft_strjoin(paths[i], temp);
		free(temp);
		if (stat(new_path, &file_stat) == 0)
		{
			free_argv(paths);
			return (new_path);
		}
		free(new_path);
	}
	free_argv(paths);
	return (ft_strdup(cmd));
}

static void	run_executable(char **argv, t_var_list *var_list, t_exec_data *data)
{
	char	*path;
	char	**char_env;

	char_env = list_to_char(var_list);
	path = find_path(argv[0], char_env);
	if (execve(path, argv, char_env) != 0)
	{
		free(path);
		free_argv(char_env);
		free_exec_data(data);
		free_var_list(&var_list);
		rl_clear_history();
		ft_putstr_fd("Couldn't execute command\n", 2);
		exit(127);
	}
}

void	run(char **argv, t_var_list **var_list, t_exec_data *data)
{
	data->last_is_fork = 0;
	if (is_builtin(argv) && !is_fork_builtin(argv)
		&& data->is_first_cmd && data->cmd_amount == 1)
		return (exec_builtin(var_list, argv, &(data->exit)));
	data->forks++;
	data->last_is_fork = 1;
	data->last_pid = fork();
	if (data->last_pid < 0)
		perror(MINISHELL_STR);
	if (data->last_pid == 0)
	{
		if (data->new_stdout)
			dup2(data->new_stdout, 1);
		if (data->new_stdin)
			dup2(data->new_stdin, 0);
		close_redirection_fds(data);
		if (is_builtin(argv))
			exec_builtin(var_list, argv, &(data->exit));
		else
			run_executable(argv, *var_list, data);
		free_exec_data(data);
		free_var_list(var_list);
		rl_clear_history();
		exit(g_exit_status);
	}
}
