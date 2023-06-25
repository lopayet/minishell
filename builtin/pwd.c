/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:09:39 by lopayet-          #+#    #+#             */
/*   Updated: 2023/03/20 14:36:14 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_pwd(void)
{
	char	*pwd;
	char	buffer[2048];

	pwd = getcwd(buffer, 2048);
	if (!pwd)
	{
		g_exit_status = 1;
		ft_putstr_fd("error\n", 2);
		return ;
	}
	printf("%s\n", buffer);
}
