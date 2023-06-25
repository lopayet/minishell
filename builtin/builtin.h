/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:11:33 by lopayet-          #+#    #+#             */
/*   Updated: 2023/04/21 16:00:03 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

//builtins
void		mini_pwd(void);
void		mini_echo(char	**argv);
void		mini_cd(t_var_list **list, char *argv);
void		mini_export(char **argv, t_var_list **list);
void		mini_unset(char **argv, t_var_list **list);
void		mini_env(t_var_list *list);
int			get_exit_code(char *arg);
//
int			is_builtin(char **tmp);
void		exec_builtin(t_var_list **list, char **str, int *exit);
int			is_fork_builtin(char **tmp);
int			is_exit(char **tmp);
int			is_invalid_var_name(char *str);

#endif
