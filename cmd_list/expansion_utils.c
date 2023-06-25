/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:47:06 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 15:52:19 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"

int	is_variable_name_end(char c)
{
	return (!(
			(c >= '0' && c <= '9')
			|| (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c == '_' || c == '?')));
}

int	is_variable_name_char(char c)
{
	return (((c >= '0' && c <= '9')
			|| (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c == '_')));
}

int	reached_size_limit(int index)
{
	return (index >= CMD_MAX_LEN - 1);
}
