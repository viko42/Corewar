/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjump.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:24:29 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/13 15:43:51 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

// Cette instruction n’est pas suivie d’octet pour décrire les paramètres.
// Elle prend toujours un index (IND_SIZE) et fait un saut à cet index si le carry est à un.
// Si le carry est nul, zjmp ne fait rien mais consomme le même temps.
// zjmp %23 met, si carry == 1, (PC + (23 % IDX_MOD)) dans le PC.
// l n’y a jamais eu, n’y a pas, et n’y aura jamais d’octet de codage des paramètres
// derrière cette opération dont l’opcode est de 9. Elle prendra un index, et fait un
// saut à cette adresse si le carry est à 1.
int		check_zjump(t_env *e, int xproc, t_type_func list)
{
	// ft_putstr_fd("Check_zjump -- Fonction\n", e->fd);
	(void)xproc;
	(void)list;
	(void)e;
	return (1);
}

void	zjump_func(t_env *e, int xproc, t_type_func list)
{
	char	*jump_to;

	(void)list;

	ft_putstr_fd("zjump--\n", e->fd);

	jump_to = get_x_from_position(e, e->process[xproc].position + 1, e->process[xproc].position + 3);
	ft_putstr_fd(jump_to, e->fd);
	ft_putstr_fd("CYCLE : ",e->fd);
	ft_putnbr_fd(e->arena.cycle, e->fd);
	ft_putstr_fd("\n",e->fd);
	// ft_printf_fd(e->fd, "Check_zjump process[%s] %d-> Position actuelle [%d] // Saut de %d\n", jump_to, xproc, e->process[xproc].position, hex_to_dec(jump_to));
	if (e->process[xproc].carry == 1){
		e->process[xproc].position = (e->process[xproc].position + ((short)hex_to_dec(jump_to) % IDX_MOD)) % MEM_SIZE;
		ft_printf_fd(e->fd, "With carry- zjmp to %d ---- [%d] - %s\n", e->process[xproc].position, hex_to_dec(jump_to), jump_to);
	}
	else
	{
		e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
		ft_printf_fd(e->fd, "With NO carry- zjmp to %d ---- [%d] - %s\n", e->process[xproc].position, hex_to_dec(jump_to), jump_to);
	}
	// ft_printf_fd(e->fd, "Check_zjump process %d-> Position UPDATE [%d]\n", xproc, e->process[xproc].position);

	free(jump_to);
}
