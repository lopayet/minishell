/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:20:56 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/14 12:55:21 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <features.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "libft.h"
# include "readline.h"
# include "history.h"

# include "var_list.h"
# include "cmd_list.h"
# include "parse.h"
# include "cmd_exec.h"
# include "builtin.h"

# define MINISHELL_STR "minishell"

extern int				g_exit_status;

typedef struct s_data	t_data;
struct s_data
{
	t_var_list	*env_var_list;
};

// minishell_utils
char		*rl_get(char *prompt, int history);
void		run_signal(int nb);

#endif
