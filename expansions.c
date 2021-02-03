/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:24:00 by abbouzid          #+#    #+#             */
/*   Updated: 2021/02/03 08:34:18 by abbouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

bool    is_single_quote_token(char *token)
{
    return ((token[0] == '\'')? TRUE: FALSE);
}

bool    is_double_quote_token(char *token)
{
    return ((token[0] == '"')? TRUE: FALSE);
}

void    expand_new_tokens(char *tkn, t_list **p_stack, t_list **new_args)
{
    int     i;
    char    **splits;

    splits = ft_split(tkn, ' ');
    i = 0;
    if (splits[0])
    {
        push_str_to_stack(p_stack, splits[0]);
        i++;
    }
    while (splits[i])
    {
        ft_lstadd_back(new_args, ft_lstnew(ft_strdup(splits[i])));
        i++;
    }
    free_argv(splits);
}

void    expand_token_list(t_list *list, t_env_var *env_var, t_list **p_stack)
{
    t_list      *new_args;
    t_list      *tmp;

    new_args = NULL;
    if (list)
    {
        expand_new_tokens(env_var->value, p_stack, &new_args);
        if (new_args != NULL)
        {
            tmp = list->next;
            list->next = new_args;
            ft_lstlast(new_args)->next = tmp;
        }
       
    }
    else
        push_str_to_stack(p_stack, env_var->value);
}

void    expand_env_var(t_list **p_stack, t_list **s_stack, t_list **vars, t_list *list)
{
       t_list       *var_name;
       t_env_var    *env_var;

        var_name = NULL;
        empty_stack(s_stack, &var_name);
        if (var_name && *((t_token *)(var_name->content))->tkn)
       {
            env_var = search_var(vars, ((t_token *)(var_name->content))->tkn);
            if (env_var)
                expand_token_list(list, env_var, p_stack);
            ft_lstclear(&var_name, free_token);
       }
}

void    expand_exit_status(t_list **p_stack, t_data *data, char **token)
{
    (*token)++;
    push_str_to_stack(p_stack, ft_itoa(data->exit_status));
}

void    handle_expand_env_var(char **token, t_list **p_stack, t_data *data, t_list *list)
{
    t_list *s_stack;

    s_stack = NULL;
    if (!(is_underscore(**token) || is_alpha(**token)))
    {
        push(p_stack, '$');
        return;
    }
    while (**token)
    {
        if (is_alpha(**token) || is_num(**token) || is_underscore(**token))
        {
            push(&s_stack, **token);
            (*token)++;
        }
        else
            break;
    }
    expand_env_var(p_stack, &s_stack, &(data->env_vars), list);
}

void    expand_dollar_sign(char **token, t_list **p_stack, t_data *data, t_list *list)
{
    t_list *s_stack;

    s_stack = NULL;
    if (**token == '?')
        expand_exit_status(p_stack, data, token);
    else if (is_num(**token))
        (*token)++;
    else
        handle_expand_env_var(token, p_stack, data, list);
}

int     handle_ut_non_special(t_list **stack, char **token)
{
    if (**token == '\"' || **token == '\'')
    {
        if (*stack && ((t_stack *)((*stack)->content))->special)
        {
            pop(stack);
            push(stack, **token);
            return (0);
        }
        else
            return (1);
    }
    else
    {
        if (*stack && ((t_stack *)((*stack)->content))->special)
            pop(stack);
        push(stack, **token);
    }
    return (0);
}

void    handle_ut_back_slash(t_list **stack, char **token, int *first_back_slash)
{
    if (!(*first_back_slash))
    {
        *first_back_slash = 1;
        push(stack, **token);
        ((t_stack *)((*stack)->content))->special = 1;
    }
    else if (((t_stack *)((*stack)->content))->special)
        ((t_stack *)((*stack)->content))->special = 0;
    else if((*stack) && !(((t_stack *)((*stack)->content))->special))
    {
        push(stack, **token);
        ((t_stack *)((*stack)->content))->special = 1;
    }
}

int     handle_ut_dollar_sign(t_list **stack, char **token, t_data *data, t_list *list)
{
    if ((*stack) && ((t_stack *)((*stack)->content))->special)
    {
        pop(stack);
        push(stack, **token);
        return (0);
    }
    else
    {
        (*token)++;
        expand_dollar_sign(token, stack, data, list);
        return (1);
    }
}

int     ret_expand_ut(t_list **stack)
{
    if ((*stack) && ((t_stack *)((*stack)->content))->special)
    {
        ft_putstr_fd("error while parsing !\n", 2);
        return (0);
    }
    return(1);
}

int     expand_unquoted_token(t_list **stack, char **token, t_data *data, t_list *list)
{
    int         first_back_slash;

    (*token)--;
    pop(stack);
    first_back_slash = 0;
    while (**token)
    {
        if (**token != '$' && **token != '\\')
        {
            if (handle_ut_non_special(stack, token))
                break;
        }
        else if (**token == '\\')
            handle_ut_back_slash(stack, token, &first_back_slash);
        else if (**token == '$')
        {
            if (handle_ut_dollar_sign(stack, token, data, list))
                continue;
        }
        if (**token == '\0')
            break;
        (*token)++;
    }
    return (ret_expand_ut(stack));
}


int     handle_dq_non_special(t_list **stack, char **token)
{
    if (**token == '\"')
    {
        if (*stack && ((t_stack *)((*stack)->content))->special)
        {
            pop(stack);
            push(stack, **token);
        }
        else
        {
            (*token)++;
            return (1);
        }
    }
    else
        push(stack, **token);
    return (0);
}

void     handle_dq_back_slack(t_list **stack, char **token, int *first_back_slash)
{
    if (!(*first_back_slash))
    {
        *first_back_slash = 1;
        push(stack, **token);
        ((t_stack *)((*stack)->content))->special = 1;
    }
    else if (((t_stack *)((*stack)->content))->special)
        ((t_stack *)((*stack)->content))->special = 0;
    else if (!(((t_stack *)((*stack)->content))->special))
    {
        push(stack, **token);
        ((t_stack *)((*stack)->content))->special = 1;
    } 
}

int     handle_dq_dollar_sign(t_list **stack, char **token, t_data *data)
{
    if ((*stack) && ((t_stack *)((*stack)->content))->special)
    {
        pop(stack);
        push(stack, **token);
        return (0);
    }
    else
    {
        (*token)++;
        expand_dollar_sign(token, stack, data, NULL);
        return (1);
    }
}

int     expand_double_quotes(t_list **stack, char **token, t_data *data)
{
    int         first_back_slash;

    pop(stack);
    first_back_slash = 0;
    while (TRUE)
    {
        if (**token != '$' && **token != '\\')
        {
            if (handle_dq_non_special(stack, token))
                break;
        }
        else if (**token == '\\')
            handle_dq_back_slack(stack, token, &first_back_slash);
        else if (**token == '$')
        {
            if (handle_dq_dollar_sign(stack, token, data))
                continue;
        }
        (*token)++;
    }
    return(1);
}

int     expand_single_quotes(t_list **stack, char **token)
{
    pop(stack);
    while(**token != '\'')
        push(stack, *(*token)++);
    (*token)++;
    return (1);
}

int     expand_quotes(t_list **stack, char **token, t_data *data)
{
    if (top_stack(stack) == '\'')
    {
        if (!expand_single_quotes(stack, token))
            return (0);
    }
    else if (!expand_double_quotes(stack, token, data))
        return (0);
    return (1);
}

char    *handle_expansion(t_list **stack, int error)
{
    t_list      *tmp;
    char        *expansion;
    
    if (error)
    {
        ft_lstclear(stack, free);
        return (NULL);
    }
    tmp = NULL;
    if (*stack)
    {
        empty_stack(stack, &tmp);
        expansion = ft_strdup(((t_token *)(tmp->content))->tkn);
        ft_lstclear(&tmp, free_token);
        return (expansion);
    }
    return (NULL);
}

char    *expand(t_list *list, t_data *data, int *error)
{
    t_list        *stack;
    char           **token;
    char           *tkn;

    stack = NULL;
    tkn = (list->content);
    token = &tkn;
    while (**token)
    {
        push(&stack, *(*token)++);
        if (top_stack(&stack) == '\'' || top_stack(&stack) == '\"')
        {
            if (!expand_quotes(&stack, token, data))
                *error = 1;
        }
        else if (!expand_unquoted_token(&stack, token, data, list))
            *error = 1;
        if (*error)
            break;
    }
    return (handle_expansion(&stack, *error));
}


int    expand_list(t_list *list, t_data *data)
{
    int     error;
    char    *tmp;

    error = 0;
    if (list)
    {
        tmp = expand(list, data, &error);
        if (!error)
        {
            free(list->content);
            if (!tmp)
                list->content = ft_strdup("");
            else
                list->content = tmp;
            return (expand_list(list->next, data));
        }
        else
            return (0);
    }
    return (1);
}

int     expand_cmd(t_list *cmds, t_data *data)
{
    t_command *cmd;

    if (cmds)
    {
        cmd = (t_command *)(cmds->content);
        if (expand_list(cmd->name_and_args, data) && 
            expand_list(cmd->infiles, data) &&
            expand_list(cmd->outfiles, data) &&
            expand_list(cmd->append_outfiles, data))
        {
            return (expand_cmd(cmds->next, data));   
        }
        return (0);
    }
    return (1);
}

int     expand_pipeline(t_pipeline *pipline, t_data *data)
{
    return (expand_cmd(pipline->cmds, data));
}