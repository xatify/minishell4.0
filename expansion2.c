/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 09:24:00 by abbouzid          #+#    #+#             */
/*   Updated: 2021/01/29 09:19:08 by abbouzid         ###   ########.fr       */
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

void    expand_env_var(t_stack **primary_stack, t_stack **secondary_stack, t_env_vars **vars)
{
       t_token      *var;
       t_env_vars    *env_var;

        var = NULL;
        empty_stack(secondary_stack, &var);
        if (var && *(var->tkn))
       {
            env_var = search_var(vars, var->tkn);
            if (env_var)
                push_str_to_stack(primary_stack, env_var->value);
            free_tokens(&var);
       }
}

void    expand_dollar_sign(char **token, t_stack **primary_stack, t_data *data)
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
        //push(primary_stack, *(*token)++);
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
    expand_env_var(primary_stack, &secondary_stack, &(data->env_vars));
}

int     expand_unquoted_token(t_stack **stack, char **token, t_data *data)
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
                expand_dollar_sign(token, stack, data);
                continue;
            }
        }
        if (**token == '\0')
            break;
        (*token)++;
    }
    if ((*stack) && (*stack)->special)
    {
        ft_putstr_fd("error while parsing !", 2);
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
                expand_dollar_sign(token, stack, data);
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

char    *expand(char **token, t_data *data)
{
    t_stack     *stack = NULL;
    t_token        *tmp;
    char           *tkn;

    while (**token)
    {
        push(&stack, *(*token)++);
        if (top_stack(&stack) == '\'' || top_stack(&stack) == '\"')
        {
            if (!expand_quotes(&stack, token, data))
            {
                free_stack(&stack);
                return (NULL);
            }
        }
        else if (!expand_unquoted_token(&stack, token, data))
        {
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


void    expand_list(t_strlist *list, t_data *data)
{
    char    *tmp;
    if (list)
    {
      tmp = expand(&(list->str), data);
      if (!tmp)
        list->str = ft_strdup("");
      else
        list->str = tmp;
      expand_list(list->next, data);
    }
}

int     expand_cmd(t_simple_command *cmd, t_data *data)
{
    char    *tmp;

    if (!cmd)
        return (1);
    if (cmd->cmd_name)
    {
        tmp = cmd->cmd_name;
        cmd->cmd_name = expand(&(cmd->cmd_name), data);
        free(tmp);
        if (!cmd->cmd_name)
            return (0);
        cmd->built_in = is_built_in(cmd->cmd_name);
    }
    expand_list(cmd->arguments, data);
    expand_list(cmd->infiles, data);
    expand_list(cmd->outfiles, data);
    expand_list(cmd->append_outfiles, data);

    return (expand_cmd(cmd->next, data));
}

int     expand_pipeline(t_pipeline *pipline, t_data *data)
{
    return (expand_cmd(pipline->simple_cmd, data));
}
