/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:43:39 by lopayet-          #+#    #+#             */
/*   Updated: 2023/03/18 16:34:23 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cmd_list.h"

#define IN_D_QUOTE '"'
#define IN_S_QUOTE '\''

int	is_argv_parsing_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	new_quote_value(char quote, int in_quote, int backslashed)
{
	if (!(quote == '\'' || quote == '"'))
		return (in_quote);
	if (backslashed && !in_quote)
		return (0);
	if ((backslashed && in_quote) && quote == in_quote)
		return (in_quote);
	if (in_quote == quote)
		return (0);
	if (!in_quote && (quote == '\'' || quote == '"'))
		return (quote);
	return (in_quote);
}
