/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:59:53 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 13:14:39 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_list.h"
#include "var_list.h"

static int	parse_error_check(t_cmd_list *node);

static int	cook_cmd_pasta(t_cmd_list *node, t_var_list *env)
{
	char	*expanded_raw;

	expanded_raw = get_expanded_raw(node->raw, env);
	free(node->raw);
	node->raw = expanded_raw;
	if (!expanded_raw)
		return (1);
	node->argc = get_argc_from_raw(node->raw);
	node->argv = get_argv_from_raw(node->raw);
	if (!node->argv)
		return (1);
	return (0);
}

t_cmd_list	*get_cmd_list_from_input(char *input, t_var_list *env)
{
	t_cmd_list	*node;
	t_cmd_list	*list;

	list = get_raw_cmd_list_from_input(input);
	if (!list)
		return (NULL);
	node = list;
	while (node)
	{
		if (cook_cmd_pasta(node, env) != 0)
			return (free_cmd_list(&list), NULL);
		node = node->next;
	}
	if (parse_error_check(list))
	{
		ft_putstr_fd("Parsing error.\n", 2);
		return (free_cmd_list(&list), NULL);
	}
	return (list);
}

static int	parse_error_check(t_cmd_list *node)
{
	while (node)
	{
		if (node->redirect == REDIRECT_INVALID)
			return (1);
		if (!node->argv || !node->argv[0])
			return (2);
		if (node->redirect != REDIRECT_NONE && !node->next)
			return (3);
		node = node->next;
	}
	return (0);
}
