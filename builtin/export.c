/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:22:25 by vpac              #+#    #+#             */
/*   Updated: 2023/04/21 16:01:22 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var_list	*get_next_var_node_ascii(t_var_list *list,
	t_var_list *current)
{
	t_var_list	*tmp;
	t_var_list	*min_after;
	int			boolean;

	min_after = 0;
	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(current->name, tmp->name) < 0)
		{
			boolean = (min_after == 0);
			if (boolean)
				min_after = tmp;
			else if (ft_strcmp(min_after->name, tmp->name) > 0)
				min_after = tmp;
		}
		tmp = tmp->next;
	}
	return (min_after);
}

static t_var_list	*get_first_var_node_ascii(t_var_list *list)
{
	t_var_list	*tmp;
	t_var_list	*minimun;

	minimun = list;
	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, minimun->name) < 0)
			minimun = tmp;
		tmp = tmp->next;
	}
	return (minimun);
}

static void	print_export(t_var_list *list)
{
	t_var_list	*tmp;

	tmp = get_first_var_node_ascii(list);
	while (tmp)
	{
		if (ft_strcmp("_", tmp->name))
		{
			printf("declare -x %s", tmp->name);
			if (tmp->content)
				printf("=\"%s\"", tmp->content);
			printf("\n");
		}
		tmp = get_next_var_node_ascii(list, tmp);
	}
}

static void	secure_content(t_var_list **list, char *name, char *content)
{
	char	*temp;

	if (!content)
		temp = ft_strdup("");
	else
		temp = ft_strdup(content);
	if (!add_var_node(list, name, temp))
		g_exit_status = 1;
	free(temp);
}

void	mini_export(char **argv, t_var_list **list)
{
	int		i;
	char	**split;

	i = 0;
	if (!argv[1])
		print_export(*list);
	while (argv[++i])
	{
		if (is_invalid_var_name(argv[i]))
		{
			ft_putstr_fd("minishell: not a valid identifier\n", 2);
			continue ;
		}
		if (ft_strchr(argv[i], '='))
		{
			split = ft_split(argv[i], '=');
			if (!split)
				return ;
			secure_content(list, split[0], split[1]);
			free_argv(split);
		}
		add_var_node(list, argv[i], 0);
	}
}
