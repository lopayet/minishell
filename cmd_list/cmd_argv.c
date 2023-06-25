/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:47:12 by lopayet-          #+#    #+#             */
/*   Updated: 2023/03/18 16:29:53 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cmd_list.h"

#define CONTINUE_LOOP 1

static int	get_next_word_index(char *str)
{
	int	in_quote;
	int	backslash;
	int	i;

	in_quote = 0;
	backslash = 0;
	i = -1;
	while (str[++i]
		&& !(is_argv_parsing_delimiter(str[i]) && !in_quote && !backslash))
	{
		if ((str[i] == '\\' && !in_quote)
			|| (str[i] == '\\' && str[i + 1] == in_quote))
		{
			backslash = 1;
			continue ;
		}
		if (new_quote_value(str[i], in_quote, backslash) != in_quote)
			in_quote = new_quote_value(str[i], in_quote, backslash);
		backslash = 0;
	}
	while (str[i] && is_argv_parsing_delimiter(str[i]))
		i++;
	return (i);
}

static int	dup_arg_loop(char *str, int *in_quote, int *backslash)
{
	if ((*str == '\\' && !*in_quote)
		|| (*str == '\\' && str[1] == *in_quote))
	{
		*backslash = 1;
		return (CONTINUE_LOOP);
	}
	if (new_quote_value(*str, *in_quote, *backslash) != *in_quote)
	{
		*in_quote = new_quote_value(*str, *in_quote, *backslash);
		return (CONTINUE_LOOP);
	}
	return (0);
}

static char	*dup_arg(char *str)
{
	int		in_quote;
	int		backslash;
	int		i;
	char	*arg;

	arg = malloc(get_next_word_index(str) + 1);
	if (!arg)
		return (NULL);
	in_quote = 0;
	backslash = 0;
	i = 0;
	str--;
	while (*(++str)
		&& !(is_argv_parsing_delimiter(*str) && !in_quote && !backslash))
	{
		if (dup_arg_loop(str, &in_quote, &backslash) == CONTINUE_LOOP)
			continue ;
		backslash = 0;
		arg[i] = *str;
		i++;
	}
	arg[i] = 0;
	return (arg);
}

int	get_argc_from_raw(char *raw)
{
	int		argc;

	argc = 0;
	while (*raw)
	{
		raw += get_next_word_index(raw);
		argc++;
	}
	return (argc);
}

char	**get_argv_from_raw(char *raw)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (get_argc_from_raw(raw) + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*raw && is_argv_parsing_delimiter(*raw))
		raw++;
	while (*raw)
	{
		argv[i] = dup_arg(raw);
		raw += get_next_word_index(raw);
		i++;
	}
	argv[i] = 0;
	return (argv);
}
