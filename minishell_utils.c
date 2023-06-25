/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:05:37 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/15 14:36:08 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rl_get(char *prompt, int history)
{
	char	*input;
	char	*trimmed;

	input = readline(prompt);
	if (input == NULL)
		return (NULL);
	trimmed = ft_strtrim(input, " \t");
	if (!trimmed)
		return (NULL);
	if (history && *trimmed)
		add_history(trimmed);
	free(input);
	return (trimmed);
}

static void	new_prompt(int signum)
{
	g_exit_status = 130;
	(void)signum;
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	ctrlbackslash(int signal)
{
	ft_putstr_fd("Quit\n", 1);
	(void)signal;
}

static void	ctrlc(int signal)
{
	printf("\n");
	(void)signal;
}

void	run_signal(int nb)
{
	if (nb == 1)
	{
		signal(SIGINT, &new_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (nb == 2)
	{
		signal(SIGINT, &ctrlc);
		signal(SIGQUIT, &ctrlbackslash);
	}
	if (nb == 3)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
