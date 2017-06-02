/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_kd_tree.cu                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:37:57 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/02 09:51:14 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "photon_mapping.h"
#include "cuda.h"

static t_kd_tree	*create_kd_node(t_photon photon);

/*
** Creates a linked list with t_kd_tree nodes based off the photons gathered during the photon shooting
*/

void		create_kd_tree(t_photon *photon_list, t_kd_tree **root, int photon_count)
{
	int i;
	int y;
	t_kd_tree *node;

	// printf("create kd tree: photoncount: %d\n", photon_count);
	node = NULL;
	i = -1;
	// printf("create kd tree--\n");
	// printf("create kd tree: [%f, %f, %f]\n", photon_list[0]->pos.x, photon_list[0]->pos.y, photon_list[0]->pos.z);
	while (++i < photon_count)
	{
		y = -1;
		while (++y < MAX_RAY_DEPTH && !v_isnan((photon_list + i)[y].dir))
		{
			if (!node)
			{
				*root = create_kd_node((photon_list + i)[y]);
				if (*root)
					node = *root;
			}
			else
			{
				node->right = create_kd_node((photon_list + i)[y]);
				if (node->right)
					node = node->right;
			}
		}  
	}  
}

static t_kd_tree		*create_kd_node(t_photon photon)
{
	t_kd_tree	*node; 
	int ret;

	ret = cudaMallocHost(&(node), sizeof(t_kd_tree));
	if (ret)
	{
		printf("cudamallocerror for node\n");
		usleep(1000000);
		return (NULL);
	}
	node->pos = photon.pos;
	node->dir = photon.dir;
	node->col = photon.col;
	node->n = photon.n;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

void		free_kd_tree(t_kd_tree *root)
{
	if (!root)
		return ;
	if (root->right)
		free_kd_tree(root->right);
	if (root->left)
		free_kd_tree(root->left);
	cudaFree(root);
}