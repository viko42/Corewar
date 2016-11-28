/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompile.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:59:59 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/28 21:49:31 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DECOMPILE_H
# define _DECOMPILE_H

# include "op.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_data
{
	char			*file_name; // nom du fichier
	char			*core_name; // .name
	char			*core_comment; // .comment
	char			**content; // instructions en bytecode d'abord puis en chaine
	int				nb_commands; // nombre d'instructions
	int				*len; // taille des instructions a leur index respectif dans content
							// pour pouvoir utiliser ft_strndup
	char			*brute_file; // file brute quoi
	int				pointer; // pointer sur l'endroit auquel on est dans content, pas sur d'en avoir besoin
	int				content_size; // nombre de bytes lu dans le fichier
}					t_data;

t_data				*get_file_info(char *file_name);
void				parse_info(t_data *data);
void				decompile(t_data *data);
void				print_file(t_data *data);
void				error(int error_code);
void				init_content_tab(t_data *data);
int					get_name_and_comment(char *brute_info, t_data *data);
int					next_command_size(char *champ);
void				add_dim(t_data *data, char *str, int len);
char				*ft_strndup(char *to_copy, size_t len);

#endif
