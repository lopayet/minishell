/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:21:17 by vpac              #+#    #+#             */
/*   Updated: 2023/04/20 15:48:22 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_var_list *list)
{
	while (list)
	{
		if (list->content)
			printf("%s=%s\n", list->name, list->content);
		list = list->next;
	}
}
