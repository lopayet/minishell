/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:10:29 by lopayet-          #+#    #+#             */
/*   Updated: 2023/03/18 16:27:03 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_unset(char **argv, t_var_list **list)
{
	int		i;

	i = 0;
	while (argv[++i])
		remove_var_node(list, argv[i]);
}
