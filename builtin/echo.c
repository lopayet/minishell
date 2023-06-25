/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:19:36 by vpac              #+#    #+#             */
/*   Updated: 2023/03/20 12:02:38 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_echo(char	**argv)
{
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	if (argv[1] && !ft_strcmp(argv[1], "-n"))
	{
		i = 2;
		flag = 1;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
}
