/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:22 by mlevieux          #+#    #+#             */
/*   Updated: 2016/12/01 21:57:07 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompile.h"

// Error codes :
// 1. No file given
// 2. Could not open file
// 3. Error reading file
// 4. Error allocating memory

// Fonction reprise du compilateur pour mettre le op.c dans la structure
void		fille_op_tab2(t_data *env)
{
	env->op_tab[9] = (t_op){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,
		T_REG}, 10, 25, "load index", 1, 1};
	env->op_tab[10] = (t_op){"sti", 3, {T_REG, T_REG | T_DIR | T_IND,
		T_DIR | T_REG}, 11, 25, "store index", 1, 1};
	env->op_tab[11] = (t_op){"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1};
	env->op_tab[12] = (t_op){"lld", 2, {T_DIR | T_IND, T_REG},
	13, 10, "long load", 1, 0};
	env->op_tab[13] = (t_op){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,
		T_REG}, 14, 50, "long load index", 1, 1};
	env->op_tab[14] = (t_op){"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1};
	env->op_tab[15] = (t_op){"aff", 1, {T_REG}, 16, 2, "aff", 1, 0};
	env->op_tab[16] = (t_op){0, 0, {0}, 0, 0, 0, 0, 0};
}

void		fille_op_tab(t_data *env)
{
	env->op_tab[0] = (t_op)(t_op){"live", 1, {T_DIR}, 1, 10, "alive", 0, 0};
	env->op_tab[1] = (t_op){"ld", 2,
	{T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0};
	env->op_tab[2] = (t_op){"st", 2,
	{T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0};
	env->op_tab[3] = (t_op){"add", 3,
	{T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0};
	env->op_tab[4] = (t_op){"sub", 3,
	{T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0};
	env->op_tab[5] = (t_op){"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND
		| T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0};
	env->op_tab[6] = (t_op){"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND
		| T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0};
	env->op_tab[7] = (t_op){"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND
		| T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0};
	env->op_tab[8] = (t_op){"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1};
	fille_op_tab2(env);
}

// La fonction suivante sert juste a lire le fichier entier et a le mettre dans
// le champ 'brute_file' de data, elle set egalement les autres champs a leur
// equivalent NULL
t_data		*get_file_info(char *file_name)
{
	t_data	*res;
	int		fd;

	res = (t_data *)malloc(sizeof(t_data));
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error(2);
	res->file_name = ft_strdup(file_name);
	res->brute_file = ft_strnew(CHAMP_MAX_SIZE);
	if ((res->content_size = read(fd, res->brute_file, CHAMP_MAX_SIZE)) == -1)
		error(3);
	fille_op_tab(res);
	res->pointer = 0;
	res->core_name = NULL;
	res->core_comment = NULL;
	res->content = NULL;
	res->len = NULL;
	res->nb_commands = 0;
	return (res);
}

// La fonction suivante est un simple strdup modifie pour palier au probleme cause
// par les zeros dans les chaines de bytes a copier d'une chaine a l'autre
// du coup elle a le meme exact comportement qu'un strdup a la difference
// qu'au lieu de copier jusqu'au zero elle copie len bytes
char		*ft_strndup(char *to_copy, size_t len)
{
	char	*res;

	if (to_copy == NULL)
		return (NULL);
	res = ft_strnew(len);
	while (--len - 1 > 0)
		res[len] = to_copy[len];
	return (res);
}

// Recupere le nom et le commentaire du heros,
// les met dans la structure t_data et renvoie le nombre
// d'octets pour commencer le vrai fichier du heros
int			get_name_and_comment(char *tmp, t_data *data)
{
	int i;
	
	i = 0;
	while (tmp[i] != 0 && i < PROG_NAME_LENGTH)
		i += 1;
	data->core_name = ft_strsub(tmp, 0, i);
	i = PROG_NAME_LENGTH + 1;
	while (tmp[i] != 0 && i < PROG_NAME_LENGTH + COMMENT_LENGTH)
		i += 1;
	data->core_comment = ft_strsub(tmp, PROG_NAME_LENGTH + 1, i - PROG_NAME_LENGTH + 1);
	return (PROG_NAME_LENGTH + COMMENT_LENGTH + 1);
}

// Cette fonction s'occupe juste de sauter d'opcode en opcode
// et de remplir le champs 'content' de data avec les 'lignes' de bytecode
// a noter qu'aucune modification du contenu n'est faite ici!
void		parse_info(t_data *data)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = data->brute_file;
	i = get_name_and_comment(tmp, data);
	while (tmp[i] == 0 && i < data->content_size)
		i += 1;
	while (i < data->content_size)
	{
		j = next_command_size(&(tmp[i]));
		add_dim(data, ft_strsub(tmp, i, j - i + 1), j - i + 1);
		i = j + 1;
	}
	free(data->brute_file);
	data->brute_file = NULL;
	data->content_size = 0;
}

// La fonction suivante permet de reallouer, de copier et de rajouter un
// elements aux tableaux 'content' et 'len' automatiquement, un peu long en
// execution surement mais etant donne la taille maximum d'un champion
// on va en faire abstraction
void		add_dim(t_data *data, char *to_add, int len_str)
{
	int		i;
	char	**tmp;
	int		*tmp_int;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (data->nb_commands + 1));
	while (i < data->nb_commands)
	{
		tmp[i] = ft_strndup(data->content[i], data->len[i]);
		free(data->content[i]);
		i += 1;
	}
	tmp[i] = ft_strndup(to_add, len_str);
	free(to_add);
	free(data->content);
	data->content = NULL;
	data->content = tmp;
	data->nb_commands += 1;
	tmp_int = (int*)malloc(sizeof(int) * data->nb_commands);
	ft_memcpy(tmp_int, data->len, (data->nb_commands - 1) * 4);
	tmp_int[data->nb_commands - 1] = len_str;
	free(data->len);
	data->len = NULL;
	data->len = tmp_int;
}

// Remplace tous les opcodes de la structure t_data par les instructions
// correspondantes, à changer pour des realloc, mais l'idee est la
void		data_replace_instructions(t_data *data)
{
	char	opcode;
	char	*replacer;
	int		len;
	
	replacer = NULL;
	data->pointer = 0;
	while (data->pointer < data->nb_commands)
	{
		opcode = data->content[data->pointer][0];
		len = ft_strlen(data->op_tab[opcode].name) - 1;
		replacer = ft_strnew(len + data->len[data->pointer]);
		ft_strcpy(replacer, data->op_tab[opcode].name);
		ft_strncpy(replacer + len + 1, data->content[data->pointer] + 1,
			data->len[data->pointer] - 1);
		free(data->content[data->pointer]);
		data->content[data->pointer] = NULL;
		data->content[data->pointer] = replacer;
		data->len[data->pointer] += len;
		replacer = NULL;
		data->pointer += 1;
	}
	data->pointer = 0;
}

// Recupere la taille des arguments d'une instruction
// grace à son ocp
int			get_ocp_len(char *champ)
{
	int	size;

	size = 0;
	if (*champ << 2 & 000000001)
		size += 1;
	else if (*champ << 2 & 000000010)
		size += 2;
	else if (*champ << 2 & 000000011)
		size += 4;
	if (*champ << 4 & 000000001)
		size += 1;
	else if (*champ << 4 & 000000010)
		size += 2;
	else if (*champ << 4 & 000000011)
		size += 4;
	if (*champ << 6 & 000000001)
		size += 1;
	else if (*champ << 6 & 000000010)
		size += 2;
	else if (*champ << 6 & 000000011)
		size += 4;
	return (size);
}

// Cas special correspondant a la fonction precedente
int			get_spec_len(char *champ)
{
	if (*champ == 15)
		return (REG_SIZE);
	else
		return (DIR_SIZE);
}

char		*get_single_info(char *bytes, int code, int *len)
{
	int		number;

	number = 0;
	if (code == REG_CODE)
		number = (int)(*bytes);
	else if (code == IND_CODE)
	{
		number += ((int)(*bytes) * 256);
		number += (int)(*bytes);
	}
	else if (code == DIR_CODE)
	{
		number += ((int)(*bytes) * 256 * 256 * 256);
		number += ((int)(*bytes) * 256 * 256);
		number += ((int)(*bytes) * 256);
		number += (int)(*bytes);
	}
	else
		return (0);
	return (ft_itoa(number));
}

// Prend une string (nulle ou non), un pointeur sur les octets
// courants du fichier et concatene l'argument correspondant a
// la fin de la chaine avant de la retourner
char		*get_decompiled_info(char *actual_string, char *bytes, int code)
{
	int		len;
	char	*tmp;
	
	len = 0;
	tmp = get_single_info(bytes, code, &len);
	actual_string = realloc(actual_string, ft_strlen(actual_string) + len);
	if (actual_string == NULL)
		error(4);
	ft_strcat(actual_string, tmp);
	free(tmp);
	tmp = NULL;
	return (actual_string);
}

int			get_size(char byte)
{
	if (byte & REG_CODE)
		return (1);
	if (byte & DIR_CODE)
		return (DIR_SIZE);
	if (byte & IND_CODE)
		return (IND_SIZE);
	return (0);
}

// Appelle en boucle la fonction precedente, afin de remplacer
// la totalité du contenu de data->contents, par les arguments
// correspondants sous formes humainement lisible
void 		transform_arguments(char *args, int len, t_data *data)
{
	char	*res;
	int		next_len;
	
	res = NULL;
	if (*args == 0 || *args == 8 || *args == 11 ||
			*args == 14)
		res = get_decompiled_info(res, args + 1, DIR_SIZE);
	else if (*args == 15)
		res = get_decompiled_info(res, args + 1, REG_SIZE);
	else
	{
		next_len = get_size(*(args + 1) << 6);
		res = get_decompiled_info(res, args + 2, get_code(next_len));
		if (len > next_len)
		{
			res = get_decompiled_info(res, args + next_len,
				get_code(*(args + 1) << 4));
			next_len = get_size(*(args + 1) << 4);
		}
		if (len > next_len)
			res = get_decompiled_info(res, args + next_len,
				get_code(*(args + 1) << 2));
	}
	free(data->content[data->pointer]);
	data->content[data->pointer] = NULL;
	data->content[data->pointer] = res;
	data->len[data->pointer] = -1;
}

// Prend un ocp et renvoie la taille totale du champ que 
// l'instruction va occuper en nombre d'octets
int			next_command_size(char *champ)
{
	int		size;

	size = 1;
	if (*champ == 0 || *champ == 8 || *champ == 11 ||
			*champ == 14 || *champ == 15)
		size += get_spec_len(champ);
	else
		size += get_ocp_len(champ + 1);
	return (size);
}

// Genere aleatoirement un label
char		*generate_label(void)
{
	time_t	t;
	char	nb_chars;
	char	*label;
	int		i;

	srand(time(NULL));
	nb_chars = MIN_CHAR_NUM + rand() % (MAX_CHAR_NUM - MIN_CHAR_NUM);
	label = ft_strnew(nb_chars);
	i = 0;
	while (i < nb_chars)
	{
		t = (time_t)clock();
		srand(t);
		label[i] = (char)((rand() % 26) + 98);
		i += 1;
	}
	return (label);
}

/* 
* * Le concept est plutot simple, on commence par verifier si le nombre de
** fichiers donnes en argument n'est pas nul, puis respectivement, on lit
** le fichier, on casse ses instructions bytecode, on traduit ses instructions
** en chaines de caracteres et puis on ecrit un nouveau fichier en .s qui
** correspond au .cor envoye. puis on passe au fichier suivant...
*/

int 		main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 2)
		error(1);
	while (argc > 1)
	{
		data = get_file_info(argv[argc - 1]);
		parse_info(data);
		decompile(data);
		print_file(data);
		free(data);
		data = NULL;
		argc -= 1;
	}
	return (0);
}
