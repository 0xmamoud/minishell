/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:37:49 by tbarret           #+#    #+#             */
/*   Updated: 2024/04/05 15:35:30 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libft/libft.h"

int ft_variable_size(char *str)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$' && str[i + 1])
			count++;
		i++;
	}
	return (count);
}

void clear_tab(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int ft_valid_variable(char c)
{
	if (c == '_' || c == '$' || ft_isalnum(c))
		return (1);
	return (0);
}

char **ft_variable_split(char *str)
{
	char **split;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	split = malloc(sizeof(char *) * (ft_variable_size(str) + 1));
	if (!split)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$' && str[i + 1])
		{
			k = i + 1;
			while (str[k] && ft_valid_variable(str[k]))
				k++;
			split[j] = malloc(sizeof(char) * ((k - i) + 1));
			if (!split[j])
				return (clear_tab(split), NULL);
			k = 0;
			while (str[i] && ft_valid_variable(str[i]))
			{
				printf("%c\n", str[i]);
				split[j][k] = str[i];
				i++;
				k++;
			}
			split[j][k] = 0;
			j++;
		} else {
			i++;
		}
	}
	split[j] = 0;
	return (split);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
    size_t	needle_len;

    if (*needle == '\0')
        return ((char *)haystack);
    needle_len = ft_strlen(needle);
    while (*haystack)
    {
        if (ft_strncmp(haystack, needle, needle_len) == 0)
            return ((char *)haystack);
        haystack++;
    }
    return (NULL);
}

static void	ft_replace(char **result, char *variable, char *data)
{
    char	*pos;
    char	*new_result;
    int		index;

    pos = ft_strstr(*result, variable);
    if (pos != NULL)
    {
        index = pos - *result;
        new_result = ft_calloc(ft_strlen(*result) - ft_strlen(variable) + ft_strlen(data) + 1, sizeof(char));
        ft_strlcpy(new_result, *result, index + 1);
        ft_strlcat(new_result, data, ft_strlen(new_result) + ft_strlen(data) + 1);
        ft_strlcat(new_result, *result + index + ft_strlen(variable), ft_strlen(new_result) + ft_strlen(*result + index + ft_strlen(variable)) + 1);
        free(*result);
        *result = new_result;
    }
}

char		*ft_replace_all(char *str, char **variable, char **data)
{
    char	*result;
    int		i;

    result = ft_strdup(str);
    i = 0;
    while (variable[i] != NULL)
    {
        ft_replace(&result, variable[i], data[i]);
        i++;
    }
    return (result);
}

char *ft_double_quotes_replace(char *str)
{
	char *result;
	char **split;
	char **variable;
	int i;

	i = 0;
	split = ft_split(str, '"');  
	result = ft_strdup(str);
	if (!split)
		return (NULL);
	while (split[i])
	{
		if (i % 2)
		{
			variable = ft_variable_split(split[i]);
			char **data = malloc(sizeof(char *) * (ft_variable_size(split[i]) + 1));
			// faire la fonction qui get env (data sert a rien, juste pour tester)
			for (int j = 0; variable[j]; j++)
				data[j] = ft_strdup("test");
			data[ft_variable_size(split[i])] = 0;
			char *replace = ft_replace_all(split[i], variable, data);
			ft_replace(&result, split[i], replace);
			clear_tab(data);
			clear_tab(variable);
			free(replace);
		}
		i++;
	}
	clear_tab(split);
	return (result);
}

int	ft_double_quotes_size(char *str)
{
	int count;
	int i;
	int quote;

	i = 0;
	quote = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (quote == 0)
			{
				quote = 1;
			} else {
				count++;
				quote = 0;
			}
		}
		i++;
	}
	return (count);
}

#include <stdlib.h>

char **ft_get_double_quotes(char *str)
{
    char **result;
    int quote = 0;
    int i = 0;
    int j = 0;
	int length;

    result = malloc(sizeof(char *) * (ft_double_quotes_size(str) + 1));
    if (!result)
        return NULL;

    while (str[i])
    {
        if (str[i] == '"')
        {
            if (quote == 0)
            {
                quote = 1;
                i++;
                length = 0;
                while (str[i + length] && str[i + length] != '"')
                    length++;

                result[j] = malloc(sizeof(char) * (length + 1));
                if (!result[j])
                    return NULL;

                int k = 0;
                while (str[i] && str[i] != '"')
                {
                    result[j][k] = str[i];
                    i++;
                    k++;
                }
                result[j][k] = '\0';
                j++;
            }
            else
            {
                quote = 0;
            }
        }
        i++;
    }
    result[j] = NULL;
    return result;
}


int main(void)
{
	// char *str = "Bonjour \"$USER\" \"$USER\"\", 'comment vas-tu ?'\", \"$HOME\", '$USER'   $USER";
	// char *parse = ft_double_quotes_replace(str);
	
	// printf("%s\n", parse);
	// free(parse);
	// char **result = ft_get_double_quotes("Bonjour \"$USER\" \"$USER\"\", 'comment vas-tu ?'\", \"$HOME\", '$USER'   $USER");
	// for (int i = 0; result[i]; i++)
	// {
	// 	printf("%s\n", result[i]);
	// 	free(result[i]);
	// }
	//BREF j'ai cassé mon code MDRRRR, je vais devoir tout refaire, je vais faire un truc plus simple
	return 0;
}
