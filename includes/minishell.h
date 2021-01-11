/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:49:46 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/11 16:05:34 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define SHELL "/bin/sh"
#define PROMPT "\nminishell:>"

/******************************************************************************/
/*	macros 																	  */
/******************************************************************************/
#define TRUE 1
#define FALSE 0
#define STDIN 0
#define STDOUT 1
#define bool int

/******************************************************************************/
/*	structures prototypes													  */
/******************************************************************************/
typedef	struct s_strlist
{
	char 				*str;
	struct s_strlist 	*next;
}				t_strlist;

typedef	struct s_simple_command
{
	char		*cmd_name;
	t_strlist 	*arguments;
	t_strlist	*infiles;
	t_strlist	*outfiles;
	t_strlist	*append_outfiles;
	struct s_simple_command		*next;
}				t_simple_command;

typedef struct s_pipeline
{
	t_simple_command 	*simple_cmd;
	struct 	s_pipeline  *next;
}				t_pipeline;

typedef  struct s_token
{
	char 	*tkn;
	int		id;
	struct 	s_token *next;
}				t_token;

typedef	struct	s_stack
{
	char				character;
	int 				meta;
	int					special;
	struct 		s_stack *next;

}				t_stack;

typedef struct s_env_vars
{
	char		*name;
	char		*value;
	struct	s_env_vars *next;
}				t_env_vars;
/******************************************************************************/
/*	get_input																  */
/******************************************************************************/
// int					get_input( t);
int				get_next_line(int fd, char **line);

/******************************************************************************/
/*	tokens linked list methodes												  */
/******************************************************************************/
enum token {OUTPUT, INPUT, APPEND_OUT, PIPE, SEMICOLON, WORD};
void            del_token_head(t_token **tokens);
int             token_id(char *token);
t_token 		*new_token(char **str);
int            identify_all_tokens(t_token *tokens);
t_token 		*last_token(t_token *tokens);
void			add_token(t_token **tokens, t_token *new_token);
void			free_tokens(t_token **head);

/******************************************************************************/
/*	lexer functions															  */
/******************************************************************************/
int     handle_single_quote(t_stack **stack, char **input_cmd);
int     special(t_stack *stack);
int     handle_double_quote(t_stack **stack, char **input_cmd);
int     handle_metacharacter(t_stack **stack, t_token **tokens, char **input_cmd);
int      handle_quotes(t_stack **stack, char **input_cmd, t_token **tokens);
t_token    *lexer(char *input_cmd);

/******************************************************************************/
/*	stack to handle the double quote strings 								  */
/******************************************************************************/

char    pop(t_stack **stack_head);
void	push(t_stack **stack_head, char character);
int     stack_len(t_stack **stack_head);
char    top_stack(t_stack **stack_head);
void    free_stack(t_stack **stack);
int		empty_stack(t_stack **stack_head, t_token **tokens);
void	is_metacharacter(t_stack **stack);
void	push_str_to_stack(t_stack **stack, char *str);

/******************************************************************************/
/*	strings manipulation prototypes											  */
/******************************************************************************/
char				*ft_strcpy(char *dst, char *src);
int					ft_strlen(char *str);
void				ft_strlcpy(char *dst, char *src, int len);
int					ft_strcmp(char *str1, char *str2);
void				*ft_memset(void	*b, int c, size_t len);
bool				is_white_character(char c);
char				*ft_strdup(char *str);
bool				is_alpha(char c);
bool				is_num(char c);
bool				is_underscore(char c);
bool				is_identifier(char *str);
bool				is_meta(char c);
int					ft_printf(const char *s, ...);
char				*ft_itoa(int i);

/******************************************************************************/
/* environment variables linked list functions prototypes					  */
/******************************************************************************/
t_env_vars			*create_env_var(char *name, char *value);
t_env_vars			*last_env_var(t_env_vars *env_vars);
char				*get_env_name(char *name_value);
char				*get_env_value(char *name_value);
void				add_back_env(t_env_vars **vars, t_env_vars *new_var);
t_env_vars			*build_env_vars(char *envp[]);
t_env_vars			*search_var(t_env_vars **env_vars, char *var_name);
int					change_env_var(t_env_vars **vars, char *var_name, char *new_value);
void				del_env_var(t_env_vars **envs, char *name);
void    			show_env_vars(t_env_vars *vars);
void				free_env_var(t_env_vars *vars);
/******************************************************************************/
/* parser functions 														  */
/******************************************************************************/
t_pipeline      *parser(t_token     **tokens);
int            	parse_redirection(t_token **tokens, t_simple_command *command, int redirection);
int     		parse_cmd_name(t_token **tokens, t_simple_command *command);
int     		parse_arguments(t_token **tokens, t_simple_command *command);
t_simple_command 	*parse_simple_command(t_token    **tokens);
t_pipeline      	*parse_pipe_line(t_token **tokens);
void			show_parse_tree(t_pipeline *parse_tree);
void			free_parse_tree(t_pipeline *parse_tree);

/******************************************************************************/
/* built-ins																  */
/******************************************************************************/
int 	pwd(void);
int		env(t_env_vars *env_vars);
int     export(t_strlist *args, t_env_vars **envs);
int		unset(t_strlist *arguments, t_env_vars **envs);


/******************************************************************************/
/* str linked list methodes													  */
/******************************************************************************/
t_strlist 			*new_strlist(char   *str);
t_strlist 			*last_strlist(t_strlist *strlist);
int     			add_strlist(t_strlist **strlist, char *str);
void                free_strlist(t_strlist *strlist);
void        		show_strlist(t_strlist *strlist);


/******************************************************************************/
/* simple command linked list methodes										  */
/******************************************************************************/
void                initialize_cmd(t_simple_command *command);
void                free_command(t_simple_command *command);
t_simple_command  	*last_command(t_simple_command *cmd);
void            	add_back_command(t_simple_command **cmd_head, t_simple_command *command);
t_simple_command	*new_cmd(void);
void				show_command(t_simple_command *cmd);

/******************************************************************************/
/* pipeline 	 linked list methodes										  */
/******************************************************************************/
t_pipeline	*new_pipe_line(void);
void        free_pipeline(t_pipeline *pipeline);
void        free_pipeline_list(t_pipeline *pipeline_head);
t_pipeline	*last_pipeline(t_pipeline *pipeline);
void        add_back_pipeline(t_pipeline **pipe_head, t_pipeline *pipeline);
void		show_pipeline(t_pipeline *pipeline);

/******************************************************************************/
/* $? and $ENV_VAR expansion of single command								  */
/******************************************************************************/
bool    is_single_quote_token(char *token);
bool    is_double_quote_token(char *token);
char    *expand_single_quote_token(char **token);
void    expand_env_var(t_stack **primary_stack, t_stack **secondary_stack, t_env_vars **vars);
void    expand_dollar_sign(char **token, t_env_vars *vars, int *exit_status, t_stack **primary_stack);
char    *expand_double_quote_token(char **token, t_env_vars *vars, int *exit_status);
char   	*expand_unquoted_token(char *token, t_env_vars *vars, int *exit_status);
int		expand_cmd(t_simple_command *cmd, t_env_vars *vars, int *exit_status);
void	expand_list(t_strlist *list, t_env_vars *vars, int *exit_status);
char	*expand(char **token, t_env_vars *vars, int *exit_status);
#endif
