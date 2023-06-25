/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:10:24 by vpac              #+#    #+#             */
/*   Updated: 2023/04/21 13:13:07 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	control_cd(t_var_list *list, char *arg)
{
	char	*oldpwd;

	if (!ft_strcmp(arg, "-"))
	{
		oldpwd = get_var_content(list, "OLDPWD");
		if (oldpwd && chdir(oldpwd) != 0)
		{
			g_exit_status = 1;
			perror(MINISHELL_STR);
		}
	}
	else
	{
		if (chdir(arg) != 0)
		{
			g_exit_status = 1;
			perror(MINISHELL_STR);
		}
	}
}

void	mini_cd(t_var_list **list, char *arg)
{
	char		*pwd;
	char		old_pwd[2048];
	char		new_pwd[2048];

	getcwd(old_pwd, 2048);
	if (!arg)
	{
		pwd = get_var_content(*list, "HOME");
		if (pwd && chdir(pwd) != 0)
			g_exit_status = 1;
	}
	else
		control_cd(*list, arg);
	getcwd(new_pwd, 2048);
	if (!add_var_node(list, "PWD", new_pwd))
		g_exit_status = 1;
	if (!add_var_node(list, "OLDPWD", old_pwd))
		g_exit_status = 1;
}
