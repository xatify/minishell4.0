/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:24:00 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/31 07:37:04 by abbouzid         ###   ########.fr       */
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

void    expand_env_var(t_stack **primary_stack, t_stack **secondary_stack, t_env_vars **vars, t_strlist *list)
{
       t_token      *var;
       t_env_vars    *env_var;
       char          **splits;
       char          first_char;
       t_strlist     *new_args;
       t_strlist     *tmp;
       int          i;

        var = NULL;
        new_args = NULL;
        empty_stack(secondary_stack, &var);
        if (var && *(var->tkn))
       {
            env_var = search_var(vars, var->tkn);
            if (env_var)
            {
                first_char = env_var->value[0];
                if (list)
                {
                    splits = ft_split(env_var->value, ' ');
                    i = 0;
                    if (first_char != ' ')
                    {
                        push_str_to_stack(primary_stack, splits[0]);
                        i = 1;
                    }
                    while (splits[i])
                    {
                        add_strlist(&new_args, splits[i]);
                        i++;
                    }
                    if (new_args != NULL)
                    {
                        tmp = list->next;
                        list->next = new_args;
                        last_strlist(new_args)->next = tmp;
                    }
                    free_argv(splits);
                }
                else
                    push_str_to_stack(primary_stack, env_var->name);
            }
            free_tokens(&var);
       }
}

void    expand_dollar_sign(char **token, t_stack **primary_stack, t_data *data, t_strlist *list)
{
    t_stack *secondary_stack;

    secondary_stack = NULL;
    if (**token == '?')
    {
        (*token)++;
        push_str_to_stack(primary_stack, ft_itoa(data->exit_status));
        return;
    }
    if (is_num(**token))
    {
        (*token)++;
        return;
    }
    if (!(is_underscore(**token) || is_alpha(**token)))
    {
        push(primary_stack, '$');
        return;
    }
    while (**token)
    {
        if (is_alpha(**token) || is_num(**token) || is_underscore(**token))
        {
            push(&secondary_stack, **token);
            (*token)++;
        }
        else
            break;
    }
    expand_env_var(primary_stack, &secondary_stack, &(data->env_vars), list);
}

int     expand_unquoted_token(t_stack **stack, char **token, t_data *data, t_strlist *list)
{
    int         first_back_slash;

    (*token)--;
    pop(stack);
    first_back_slash = 0;
    while (**token)
    {
        if (**token != '$' && **token != '\\')
        {
            if (**token == '\"' || **token == '\'')
            {
                if (*stack && (*stack)->special)
                {
                    pop(stack);
                    push(stack, **token);
                }
                else
                    break;
            }
            else
            {
                if (*stack && (*stack)->special)
                    pop(stack);
                push(stack, **token);
            }
        }
        else if (**token == '\\' && !first_back_slash)
        {
            first_back_slash = 1;
            push(stack, **token);
            (*stack)->special = 1;
        }
        else if (**token == '\\' &&  (* stack) && (*stack)->special)
            (*stack)->special = 0;
        else if (**token == '\\' && (*stack) && !((*stack)->special))
        {
            push(stack, **token);
            (*stack)->special = 1;
        }
        else if (**token == '$')
        {
            if ((*stack) && (*stack)->special)
            {
                pop(stack);
                push(stack, **token);
            }
            else
            {
                (*token)++;
                expand_dollar_sign(token, stack, data, list);
                continue;
            }
        }
        if (**token == '\0')
            break;
        (*token)++;
    }
    if ((*stack) && (*stack)->special)
    {
        ft_putstr_fd("error while parsing hfh!", 2);
        return (0);
    }
    return(1);
}

int     expand_double_quotes(t_stack **stack, char **token, t_data *data)
{
    int         first_back_slash;

    pop(stack);
    first_back_slash = 0;
    while (TRUE)
    {
        if (**token != '$' && **token != '\\')
        {
            if (**token == '\"')
            {
                if (*stack && (*stack)->special)
                {
                    pop(stack);
                    push(stack, **token);
                }
                else
                {
                    (*token)++;
                    break;
                }
            }
            else
                push(stack, **token);
        }
        else if (**token == '\\' && !first_back_slash)
        {
            first_back_slash = 1;
            push(stack, **token);
            (*stack)->special = 1;
        }
        else if (**token == '\\' && (*stack)->special)
            (*stack)->special = 0;
        else if (**token == '\\' && !((*stack)->special))
        {
            push(stack, **token);
            (*stack)->special = 1;
        }
        else if (**token == '$')
        {
            if ((*stack) && (*stack)->special)
            {
                pop(stack);
                push(stack, **token);
            }
            else
            {
                (*token)++;
                expand_dollar_sign(token, stack, data, NULL);
                continue;
            }
        }
        (*token)++;
    }
    return(1);
}

int     expand_single_quotes(t_stack **stack, char **token)
{
    pop(stack);
    while(**token != '\'')
        push(stack, *(*token)++);
    (*token)++;
    return (1);
}

int     expand_quotes(t_stack **stack, char **token, t_data *data)
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

char    *expand(t_strlist *list, t_data *data, int *error)
{
    t_stack     *stack = NULL;
    t_token        *tmp;
    char           **token;
    char           *tkn;

    token = &(list->str);
    while (**token)
    {
        push(&stack, *(*token)++);
        if (top_stack(&stack) == '\'' || top_stack(&stack) == '\"')
        {
            if (!expand_quotes(&stack, token, data))
            {
                *error = 1;
                free_stack(&stack);
                return (NULL);
            }
        }
        else if (!expand_unquoted_token(&stack, token, data, list))
        {
            *error = 1;
            free_stack(&stack);
            return (NULL);
        }
    }
    tmp = NULL;
    if (stack)
    {
        empty_stack(&stack, &tmp);
        tkn = ft_strdup(tmp->tkn);
        free_tokens(&tmp);
        return (tkn);
    }
    return (NULL);
}


int    expand_list(t_strlist *list, t_data *data)
{
    int     error;
    char    *tmp;

    error = 0;
    if (list)
    {
      tmp = expand(list, data, &error);
      if (!error)
      {
        if (!tmp)
            list->str = ft_strdup("");
        else
            list->str = tmp;
        return (expand_list(list->next, data));
      }
    }
    return (1);
}

int     expand_cmd(t_command *cmd, t_data *data)
{
    if (cmd)
    {
        if (expand_list(cmd->name_and_args, data) && 
            expand_list(cmd->infiles, data) &&
            expand_list(cmd->outfiles, data) &&
            expand_list(cmd->append_outfiles, data))
        {
            return (expand_cmd(cmd->next, data));   
        }
    }
    return (1);
}

void     expand_pipeline(t_pipeline *pipline, t_data *data)
{
    expand_cmd(pipline->simple_cmd, data);
}