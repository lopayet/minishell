/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:35:43 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/20 11:54:21 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"

static int	get_raw_cmd_length(char *cmd_start)
{
	int	in_quote;
	int	backslash;
	int	i;

	in_quote = 0;
	backslash = 0;
	i = -1;
	while (cmd_start[++i]
		&& !(is_delimiter(cmd_start[i]) && !in_quote && !backslash))
	{
		if ((cmd_start[i] == '\\' && !in_quote)
			|| (cmd_start[i] == '\\' && cmd_start[i + 1] == in_quote))
		{
			backslash = 1;
			continue ;
		}
		if (new_quote_value(cmd_start[i], in_quote, backslash) != in_quote)
			in_quote = new_quote_value(cmd_start[i], in_quote, backslash);
		backslash = 0;
	}
	return (i);
}

static char	*get_next_cmd_index(char *cmd)
{
	cmd += get_raw_cmd_length(cmd);
	while (is_delimiter(*cmd))
		cmd++;
	return (cmd);
}

static int	get_next_redirect(char *input)
{
	input += get_raw_cmd_length(input);
	if (!*input)
		return (REDIRECT_NONE);
	return (get_redirect_type(input));
}

t_cmd_list	*get_raw_cmd_list_from_input(char *input)
{
	t_cmd_list	*list;
	t_cmd_list	*new;
	int			redirect;

	redirect = REDIRECT_NONE;
	list = NULL;
	while (*input)
	{
		new = new_cmd_node();
		if (!new)
			return (free_cmd_list(&list), NULL);
		new->raw = ft_strndup(input, get_raw_cmd_length(input));
		if (!new->raw)
			return (free(new), free_cmd_list(&list), NULL);
		redirect = get_next_redirect(input);
		new->redirect = redirect;
		input = get_next_cmd_index(input);
		push_cmd_node(&list, new);
	}
	return (list);
}
