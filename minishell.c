/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:18 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 15:57:32 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static void		minishell(t_data data);
static char		*create_prompt(void);
static t_data	init_shell(char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (!isatty(1))
		return (1);
	if (argc > 1)
		return (1);
	(void) argv;
	data = init_shell(envp);
	minishell(data);
	free_var_list(&data.env_var_list);
	rl_clear_history();
	return (g_exit_status);
}

static void	minishell(t_data data)
{
	char		*input;
	char		*prompt;
	int			exit;
	t_cmd_list	*list;

	exit = 0;
	run_signal(1);
	while (!exit)
	{
		prompt = create_prompt();
		input = rl_get(prompt, 1);
		free(prompt);
		if (input == NULL)
			break ;
		list = get_cmd_list_from_input(input, data.env_var_list);
		free(input);
		exit = cmd_exec(list, &data.env_var_list);
		free_cmd_list(&list);
	}
	if (!exit)
		g_exit_status = 0;
	printf("exit\n");
}

static char	*create_prompt(void)
{
	char	*tmp;
	char	*prompt;

	tmp = NULL;
	tmp = getcwd(tmp, 4096);
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (prompt);
}

static t_data	init_shell(char **envp)
{
	t_data	data;

	if (isatty(0))
		printf("\033[36m\nERECTILE DISFUNCTION MINISHELL\n\n\033[0m");
	data.env_var_list = get_var_list_from_envp(envp);
	return (data);
}
