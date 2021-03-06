/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player_in_memory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:55:52 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/19 20:38:06 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	player_to_tab(t_env *e, int x)
{
	int		byte;
	int		start;
	char	*tmp;

	start = e->players[x].start;
	tmp = NULL;
	byte = BYTE_START_CODE;
	while (byte != (int)e->players[x].size)
	{
		tmp = ft_sprintf("%02x", (unsigned char)e->players[x].file[byte]);
		g_tab[start] = hex_to_dec(tmp);
		g_tab2[start] = e->players[x].id_player + 1;
		byte++;
		start += 1;
		free(tmp);
	}
}

void	get_position(t_env *e)
{
	int		saut;

	saut = MEM_SIZE / e->active_players;
	if (e->active_players >= 2)
		e->players[1].start = saut;
	if (e->active_players >= 3)
		e->players[2].start = saut * 2;
	if (e->active_players >= 4)
		e->players[3].start = saut * 3;
}

void	put_player(t_env *e)
{
	t_process	*list;
	int			x;

	x = -1;
	list = NULL;
	get_position(e);
	e->active_process = e->active_players;
	while (++x < e->active_players)
	{
		init_process(e, x);
		e->players[x].position = e->players[x].start % MEM_SIZE;
		player_to_tab(e, x);
		e->process[x].position = e->players[x].position % MEM_SIZE;
		e->process[x].start = e->players[x].start % MEM_SIZE;
		e->process[x].id_player = e->players[x].id_player;
		e->process[x].reg[1] = e->players[x].id_live;
	}
}
