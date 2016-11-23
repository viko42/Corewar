/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:37:17 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/23 08:33:02 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

void	(*g_func_process[5])(t_env*, int, int) = {live_func, live_func, live_func, live_func, live_func};

void		apply_func(t_env *e, int xproc, int func)
{
	// printf("FUNC %d\n", func);
	if (func == 1)
		g_func_process[func - 1](e, xproc, func);
}

t_type_func check_jump(t_env *e, char *op_size)
{
	int			index;
	int			x;
	t_type_func	list;

	(void)e;
	index = 0;
	x = 0;
	ft_memset(&list, 0, sizeof(t_type_func));
	if (ft_strlen(op_size) != 8)
	{
		vm_error("check_jump");
		return (list);
	}
	list.size = 2;
	if (op_size[index + 6] != '0' || op_size[index + 7] != '0'){
		list.error = 1;
		// printf("error pour %s\n", op_size);
	}
	while (op_size[index] != '\0')
	{
		if (op_size[index] == '0' && op_size[index + 1] == '1'){
			list.type[x].t_reg++;
			list.size += 1;
		}
		else if (op_size[index] == '1' && op_size[index + 1] == '0'){
			list.type[x].t_dir++;
			list.size += 2;
		}
		else if (op_size[index] == '1' && op_size[index + 1] == '1'){
			list.type[x].t_ind++;
			list.size += 2;
		}
		// else
		// 	list.error = 1;
		index += 2;
		x++;
	}
	return (list);
}

char		*get_opfrom_x(t_env *e, int a, int x)
{
	char	*result;
	int		index;

	index = 0;
	(void)e;
	result = malloc(sizeof(char) * abs(a - x) + 1);
	if (a > x)
		vm_error("x higher than a");
	while (a < x)
	{
		result[index] = tab[a % ((MEM_SIZE))];
		a++;
		index++;
	}
	result[index] = '\0';
	return (result);
}
