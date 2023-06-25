/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:50:38 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 15:41:43 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LIST_H
# define CMD_LIST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "var_list.h"

# define CMD_MAX_LEN 65536

# define REDIRECT_INVALID -1
# define REDIRECT_NONE 0
# define REDIRECT_PIPE 1
# define REDIRECT_OUTPUT 2
# define REDIRECT_OUTPUT_APPEND 3
# define REDIRECT_INPUT 4
# define REDIRECT_INPUT_DELIM 5

typedef struct s_cmd_list	t_cmd_list;
struct s_cmd_list
{
	char		*raw;
	int			redirect;
	int			argc;
	char		**argv;
	t_cmd_list	*next;
};

// cmd_list.c
t_cmd_list	*push_cmd_node(t_cmd_list **list, t_cmd_list *new);
t_cmd_list	*add_cmd_node(t_cmd_list **list);
t_cmd_list	*new_cmd_node(void);
void		free_argv(char **argv);
void		free_cmd_list(t_cmd_list **list);
// cmd_argv_utils.c
int			is_argv_parsing_delimiter(char c);
int			new_quote_value(char quote, int in_quote, int backslashed);
// split_input.c
t_cmd_list	*get_raw_cmd_list_from_input(char *input);
// split_input_utils.c
int			is_delimiter(char c);
int			get_redirect_type(char *start);
// expansion.c
char		*get_expanded_raw(char *raw, t_var_list *env);
// expansion_utils.c
int			is_variable_name_end(char c);
int			is_variable_name_char(char c);
int			reached_size_limit(int index);
// cmd_argv.c
int			get_argc_from_raw(char *raw);
char		**get_argv_from_raw(char *raw);

#endif
