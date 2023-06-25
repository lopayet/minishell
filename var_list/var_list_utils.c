/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:40:19 by vpac              #+#    #+#             */
/*   Updated: 2023/04/20 13:55:31 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var_list.h"

int	list_len(t_var_list *list)
{
	int			i;
	t_var_list	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->content)
			i += 1 + ft_strlen(tmp->name) + ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	return (i);
}

char	**list_to_char(t_var_list *list)
{
	char		**char_list;
	t_var_list	*tmp;
	int			i;

	i = 0;
	tmp = list;
	char_list = malloc(sizeof(char *) * (list_len(tmp) + 1));
	if (!char_list)
		return (NULL);
	while (tmp)
	{
		if (tmp->content)
		{
			char_list[i] = 0;
			char_list[i] = ft_strjoin_free(char_list[i], tmp->name);
			char_list[i] = ft_strjoin_free(char_list[i], "=");
			char_list[i] = ft_strjoin_free(char_list[i], tmp->content);
			if (!char_list[i])
				return (NULL);
			i++;
		}
		tmp = tmp->next;
	}
	char_list[i] = 0;
	return (char_list);
}

void	remove_var_node(t_var_list **list, char *name)
{
	t_var_list	*node;
	t_var_list	*prev;

	if (*list && !ft_strcmp((*list)->name, name))
	{
		node = (*list)->next;
		free((*list)->content);
		free((*list)->name);
		free(*list);
		*list = node;
		return ;
	}
	node = *list;
	prev = 0;
	while (node)
	{
		if (!ft_strcmp(node->name, name))
		{
			prev->next = node->next;
			return (free(node->content), free(node->name), free(node));
		}
		prev = node;
		node = node->next;
	}
}
