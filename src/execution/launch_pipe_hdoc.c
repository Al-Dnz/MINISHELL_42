/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pipe_hdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:08:02 by adenhez           #+#    #+#             */
/*   Updated: 2021/12/27 23:08:03 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_pipe_hdoc(t_btree *tree)
{
	if (tree->left != NULL)
		launch_pipe_hdoc(tree->left);
	if (tree->right != NULL)
		launch_pipe_hdoc(tree->right);
	if (tree != NULL)
	{
		if (hdoc_pipe(tree) == 1)
			g_data.stop = 1;
	}
	return (1);
}
