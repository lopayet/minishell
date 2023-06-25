/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:50:48 by lopayet-          #+#    #+#             */
/*   Updated: 2023/03/18 16:28:40 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cmd_list.h"

t_cmd_list	*new_cmd_node(void)
{
	t_cmd_list	*new;

	new = malloc(sizeof(t_cmd_list));
	if (!new)
		return (0);
	ft_bzero(new, sizeof(t_cmd_list));
	return (new);
}

t_cmd_list	*push_cmd_node(t_cmd_list **list, t_cmd_list *new)
{
	t_cmd_list	*cursor;

	if (*list == 0)
	{
		new->next = 0;
		*list = new;
		return (new);
	}
	cursor = *list;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = new;
	new->next = 0;
	return (new);
}

t_cmd_list	*add_cmd_node(t_cmd_list **list)
{
	t_cmd_list	*new;

	new = new_cmd_node();
	push_cmd_node(list, new);
	return (new);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_cmd_list(t_cmd_list **list)
{
	t_cmd_list	*node;
	t_cmd_list	*next;

	if (*list == 0)
		return ;
	node = *list;
	next = node->next;
	while (next)
	{
		if (node->raw)
			free(node->raw);
		if (node->argv)
			free_argv(node->argv);
		free(node);
		node = next;
		next = node->next;
	}
	if (node->raw)
		free(node->raw);
	if (node->argv)
		free_argv(node->argv);
	free(node);
}
