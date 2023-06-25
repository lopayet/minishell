/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:08:55 by vpac              #+#    #+#             */
/*   Updated: 2023/04/21 12:13:07 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **argv)
{
	if (!argv)
		return (0);
	if (!ft_strcmp(argv[0], "echo"))
		return (1);
	else if (!ft_strcmp(argv[0], "cd"))
		return (2);
	else if (!ft_strcmp(argv[0], "pwd"))
		return (3);
	else if (!ft_strcmp(argv[0], "export"))
		return (4);
	else if (!ft_strcmp(argv[0], "unset"))
		return (5);
	else if (!ft_strcmp(argv[0], "env"))
		return (6);
	else if (!ft_strcmp(argv[0], "exit"))
		return (7);
	return (0);
}

int	is_fork_builtin(char **argv)
{
	if (!argv)
		return (0);
	if (!ft_strcmp(argv[0], "echo"))
		return (1);
	else if (!ft_strcmp(argv[0], "pwd"))
		return (3);
	else if (!ft_strcmp(argv[0], "env"))
		return (6);
	return (0);
}

void	exec_builtin(t_var_list **list, char **argv, int *exit)
{
	int		i;

	g_exit_status = 0;
	i = is_builtin(argv);
	if (i == 1)
		mini_echo(argv);
	else if (i == 2)
		mini_cd(list, argv[1]);
	else if (i == 3)
		mini_pwd();
	else if (i == 4)
		mini_export(argv, list);
	else if (i == 5)
		mini_unset(argv, list);
	else if (i == 6)
		mini_env(*list);
	else if (i == 7)
	{
		*exit = 1;
		g_exit_status = get_exit_code(argv[1]);
	}
}
