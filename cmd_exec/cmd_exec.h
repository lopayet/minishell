/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:09:56 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 14:41:49 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXEC_H
# define CMD_EXEC_H

# include "minishell.h"

typedef struct s_exec_data
{
	int			cmd_amount;
	int			forks;
	int			new_stdin;
	int			new_stdout;
	int			new_stdin_copy;
	int			new_stdout_copy;
	int			next_stdin;
	int			*heredoc_list;
	int			heredoc_index;
	int			heredoc_amount;
	t_cmd_list	*next_cmd;
	t_cmd_list	*cmd_list;
	int			is_first_cmd;
	int			last_is_fork;
	int			last_pid;
	int			exit;
}			t_exec_data;

// cmd_exec
int			cmd_exec(t_cmd_list *cmd_list, t_var_list **var_list);
// cmd_exec_utils
int			pipe_handle(t_exec_data *data);
void		safe_close(int	*fd);
int			ft_strrncmp(char *s1, char *s2, size_t n);
void		signal_some_mujeres(t_cmd_list *cmd_list);
// redirect
int			handle_redirect(t_cmd_list *cmd_node, t_exec_data *data);
int			redir_out_handle(t_cmd_list *node, t_exec_data *data);
int			get_redir_out_fd(t_cmd_list *node);
int			redir_in_handle(t_cmd_list *node, t_exec_data *data);
int			get_redir_in_fd(t_cmd_list *node, t_exec_data *data);
// redirect_utils
t_cmd_list	*get_next_cmd_node(t_cmd_list *node);
int			redir_touch(t_cmd_list *node);
int			should_pipe_after_redir_chain(t_cmd_list *node);
int			is_arrow_redirect(int delimiter);
// heredoc
int			make_heredoc_list(t_cmd_list *cmd_list, t_exec_data *data);
void		free_heredoc_list(t_exec_data *data);
// run
void		run(char **argv, t_var_list **var_list, t_exec_data *data);
// run_utils
void		close_redirection_fds(t_exec_data *data);
void		free_exec_data(t_exec_data *data);

#endif
