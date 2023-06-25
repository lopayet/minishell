/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:43:04 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 15:54:13 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_var_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_variable_name_char(str[i]))
		i++;
	if (i > 0 && (str[i] == 0 || str[i] == '='))
		return (0);
	return (1);
}
