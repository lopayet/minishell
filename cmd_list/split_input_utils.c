/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:41:47 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 14:56:46 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"

int	is_delimiter(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	get_redirect_type(char *start)
{
	char	redir[3];

	redir[0] = start[0];
	redir[1] = start[1];
	redir[2] = 0;
	if (redir[1])
		redir[2] = start[2];
	if (redir[0] == '>' && (!redir[1] || !is_delimiter(redir[1])))
		return (REDIRECT_OUTPUT);
	if (redir[0] == '<' && (!redir[1] || !is_delimiter(redir[1])))
		return (REDIRECT_INPUT);
	if (redir[0] == '|' && (!redir[1] || !is_delimiter(redir[1])))
		return (REDIRECT_PIPE);
	if (redir[0] == '>' && redir[1] == '>'
		&& (!redir[2] || !is_delimiter(redir[2])))
		return (REDIRECT_OUTPUT_APPEND);
	if (redir[0] == '<' && redir[1] == '<'
		&& (!redir[2] || !is_delimiter(redir[2])))
		return (REDIRECT_INPUT_DELIM);
	return (REDIRECT_INVALID);
}
