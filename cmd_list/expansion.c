/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:53:38 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 14:55:37 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd_list.h"

#define IN_D_QUOTE '"'
#define IN_S_QUOTE '\''

static char	*get_cmd_var_content(char *start, t_var_list *env)
{
	int		len;
	int		i;
	char	*name;
	char	*content;

	len = 0;
	while (start[len] && !is_variable_name_end(start[len]))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	name = malloc(len + 1);
	if (!name)
		return (0);
	i = -1;
	while (++i < len)
		name[i] = start[i];
	name[i] = 0;
	if (ft_strcmp(name, "?") == 0)
		return (free(name), ft_itoa(g_exit_status));
	content = get_var_content(env, name);
	free(name);
	if (!content)
		return (0);
	return (ft_strdup(content));
}

static int	strcpy_var_content(char *dst, char *name_start,
	t_var_list *env, int max)
{
	char	*content;
	int		i_dst;
	int		i_src;

	content = get_cmd_var_content(name_start, env);
	if (!content)
		return (0);
	i_dst = 0;
	i_src = 0;
	while (content[i_src])
	{
		if (content[i_src] == '"' || content[i_src] == '\''
			|| content[i_src] == '\\')
		{
			dst[i_dst] = '\\';
			i_dst++;
		}
		if (i_dst < max)
			dst[i_dst] = content[i_src];
		i_dst++;
		i_src++;
	}
	free(content);
	return (i_dst);
}

static void	get_expanded_raw_backslash_check(
	char **raw, char **new, int *i_new, int *backslash)
{
	*backslash = 0;
	if (**raw == '\\')
	{
		*backslash = 1;
		(*new)[(*i_new)++] = **raw;
		(*raw)++;
	}
}

static void	expansion_routine(char **raw, char *new,
	int *i_new, t_var_list *env)
{
	*i_new += strcpy_var_content(new + *i_new, ++(*raw),
			env, CMD_MAX_LEN - *i_new);
	while (**raw && !is_variable_name_end(**raw))
		(*raw)++;
}

char	*get_expanded_raw(char *raw, t_var_list *env)
{
	char	*new;
	int		i_new;
	int		in_quote;
	int		backslash;

	new = malloc(CMD_MAX_LEN);
	if (!new)
		return (NULL);
	i_new = 0;
	in_quote = 0;
	backslash = 0;
	while (*raw && !reached_size_limit(i_new))
	{
		get_expanded_raw_backslash_check(&raw, &new, &i_new, &backslash);
		in_quote = new_quote_value(*raw, in_quote, backslash);
		if (in_quote != IN_S_QUOTE && *raw == '$')
		{
			expansion_routine(&raw, new, &i_new, env);
			continue ;
		}
		if (!reached_size_limit(i_new))
			new[i_new++] = *raw++;
	}
	return (new[i_new] = 0, new);
}
