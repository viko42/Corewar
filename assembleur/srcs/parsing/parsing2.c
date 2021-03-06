/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:42:43 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/19 04:43:30 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void			free_2d_tab(char **tab)
{
	int a;

	a = 0;
	if (tab == NULL)
		return ;
	while (tab[a] && tab[a][0])
	{
		free(tab[a]);
		++a;
	}
	free(tab);
}

void			print_2d_tab(char **tab, int size)
{
	int a;

	a = 0;
	if (tab == NULL)
		return ;
	while (tab[a] && tab[a][0] && (a < size - 1))
	{
		ft_putendl(tab[a]);
		++a;
	}
	ft_putendl(tab[a]);
}

void			double_cote(char *str, char *error)
{
	int	a;

	a = 0;
	while (*str)
	{
		if (*str == '\"')
			a++;
		str++;
	}
	if (a != 2)
		asm_error(error);
}

void			handle_comment(char *str, t_env *e, char **tab)
{
	double_cote(str, "error in .comment");
	e->comment = ft_strdup(tab[1]);
	if (ft_strlen(e->comment) > COMMENT_LENGTH)
	{
		ft_printf("Champion comment to long ");
		ft_printf("Max lenght %d)\n", COMMENT_LENGTH);
		free_2d_tab(tab);
		exit(-1);
	}
}

void			name_comment(char *s, t_env *e)
{
	char	**tab;

	tab = ft_strsplit(s, '\"');
	if ((s[1] == 'n') && (s[2] == 'a') && (s[3] == 'm') && (s[4] == 'e') &&
		valid_name_comment(s, 1))
	{
		double_cote(s, "error in .name");
		e->name = ft_strdup(tab[1]);
		if (ft_strlen(e->name) > PROG_NAME_LENGTH)
		{
			ft_printf("Champion name to long ");
			ft_printf("(Max lenght %d)\n", PROG_NAME_LENGTH);
			free_2d_tab(tab);
			exit(-1);
		}
	}
	else if ((s[1] == 'c') && (s[2] == 'o') && (s[3] == 'm')
		&& (s[4] == 'm') && (s[5] == 'e') && (s[6] == 'n') &&
		(s[7] == 't') && valid_name_comment(s, 2))
		handle_comment(s, e, tab);
	else
		asm_error(ft_strjoin("Extension field \"",
			ft_strjoin(s, "\" unknown.")));
	free_2d_tab(tab);
}
