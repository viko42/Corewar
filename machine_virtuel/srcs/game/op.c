/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 19:01:46 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 00:46:33 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		fille_op_tab2(t_env *env)
{
	env->op[9] = (t_op){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,
		T_REG}, 10, 25, "load index", 1, 1};
	env->op[10] = (t_op){"sti", 3, {T_REG, T_REG | T_DIR | T_IND,
		T_DIR | T_REG}, 11, 25, "store index", 1, 1};
	env->op[11] = (t_op){"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1};
	env->op[12] = (t_op){"lld", 2, {T_DIR | T_IND, T_REG},
	13, 10, "long load", 1, 0};
	env->op[13] = (t_op){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,
		T_REG}, 14, 50, "long load index", 1, 1};
	env->op[14] = (t_op){"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1};
	env->op[15] = (t_op){"aff", 1, {T_REG}, 16, 2, "aff", 1, 0};
	env->op[16] = (t_op){0, 0, {0}, 0, 0, 0, 0, 0};
}

void		op_tab(t_env *env)
{
	env->op[0] = (t_op)(t_op){"live", 1, {T_DIR}, 1, 10, "alive", 0, 0};
	env->op[1] = (t_op){"ld", 2,
	{T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0};
	env->op[2] = (t_op){"st", 2,
	{T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0};
	env->op[3] = (t_op){"add", 3,
	{T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0};
	env->op[4] = (t_op){"sub", 3,
	{T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0};
	env->op[5] = (t_op){"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND
		| T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0};
	env->op[6] = (t_op){"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND
		| T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0};
	env->op[7] = (t_op){"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND
		| T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0};
	env->op[8] = (t_op){"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1};
	fille_op_tab2(env);
}
