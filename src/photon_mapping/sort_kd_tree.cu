/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_kd_tree.cu                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:24:44 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/18 14:28:19 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"
#include "photon_mapping.h"
#include "cuda.h"

static t_kd_tree	*split_list(t_kd_tree *tree, int length);
static t_kd_tree	*get_next_smallest_by_dim(t_kd_tree **left, t_kd_tree **right, int dim);
static t_kd_tree	*split_list(t_kd_tree *tree, int length);
static int			get_length(t_kd_tree *root);
static t_kd_tree	*get_median(t_kd_tree *root, int length);
static t_kd_tree	*split_without_median(t_kd_tree *root, t_kd_tree **median);
static t_kd_tree	*merge_sort_by_dim(t_kd_tree *root, int dim);

__host__
void				print_photons2(t_kd_tree *tree);

/*
** Creates a sorted kd tree based off the linked list "root"
*/

void	sort_kd_tree(t_kd_tree **root, int dim, t_kd_tree **sorted)
{
	t_kd_tree	*right;
	t_kd_tree	*median;
	int			length;

	dim = (dim == 3) ? 0 : dim; 
	right = NULL;
	*root = merge_sort_by_dim(*root, dim);
	// printf("SORT RESULTS DIM %d %p: \n", dim, *root);
	// print_photons2(*root);
	length = get_length(*root);
	if (length == 1)
	{
		(*sorted) = *root;
		(*sorted)->right = NULL;
		(*sorted)->left = NULL;
		return ;
	}
	length = length / 2 + length % 2;
	median = get_median(*root, length); 
	right = split_without_median(*root, &median);
	// printf("root: %p, median: %p, right: %p\n", *root, median, right);
	*sorted = median;
	(*sorted)->right = NULL;
	(*sorted)->left = NULL;
	if (*root)
	{
		// printf("sort left: %p\n", *root);
		sort_kd_tree(root, dim + 1, &((*sorted)->left));
	}
	if (right)
	{
		// printf("sort right: %p\n", right);
		sort_kd_tree(&right, dim + 1, &((*sorted)->right));
	}
	// printf("done sorting\n");
}

static t_kd_tree		*merge_sort_by_dim(t_kd_tree *root, int dim)
{
	int			length;
	t_kd_tree	*tmp;
	t_kd_tree	*link;
	t_kd_tree	*sorted;


	// printf("merge_sort_by_dim: \n");
	// print_photons2(root);
	tmp = NULL;
	link = NULL;
	// C(1)
	length = get_length(root);
	// printf("length: [%d]\n", length);
	if (length > 1)
	{
		// C(2)
		tmp = split_list(root, length / 2);
		// printf("after split print root:\n");
		// print_photons2(root);
		// printf("after split print tmp:\n");
		// print_photons2(tmp);
		// printf("merge_sort_by_dim root\n");
		root = merge_sort_by_dim(root, dim);	
		// printf("merge_sort_by_dim tmp\n");
		tmp = merge_sort_by_dim(tmp, dim);
	}
	// C(3)
	// if (!root || !root->right)
	// {
	// 	printf("merge_sort_by_dim return : %p\n", root);
	// 	return (root);
	// }
	sorted = NULL;
	// C(4)
	while (root || tmp)
	{
		if (!sorted)
		{
			// C(30)
			sorted = get_next_smallest_by_dim(&root, &tmp, dim);
			link = sorted;
		}
		else
		{
			// C(31)
			link->right = get_next_smallest_by_dim(&root, &tmp, dim);
			link = link->right;
		}
	}
	link->right = NULL;
	// printf("merge_sort_by_dim return : %p\n", sorted);
	return (sorted);
}

static t_kd_tree	*get_next_smallest_by_dim(t_kd_tree **left, t_kd_tree **right, int dim)
{
	t_kd_tree	*tmp;
	int			r_length;
	int			l_length;

	l_length = get_length(*left);
	r_length = get_length(*right);
	tmp = NULL;
	// printf("get_next_smallest_by_dim: left: [%d] right: [%d]\n", l_length, r_length);
	// printf("compare left: %p (%f) ", *left, (l_length ? (*left)->pos.x : 0.0));
	// printf("with right: %p (%f)\n", *right, (r_length ? (*right)->pos.x : 0.0));
	if (!r_length && l_length)
	{
		// C(10)
		tmp = *left;
		// printf("check left length: %d\n", get_length(*left));
		*left = (*left)->right;
		// printf("check left length2: %d\n", get_length(*left));
		// printf("left address: %p\n", *left);
	}
	else if (!l_length && r_length)
	{
		// C(11)
		tmp = *right;
		// printf("check right length: %d\n", get_length(*right));
		*right = (*right)->right;
		// printf("check right length2: %d\n", get_length(*right));
		// printf("right address: %p\n", *right);
	}
	else if ((dim == 0 && (*left)->pos.x < (*right)->pos.x))
	{
		// C(12)
		tmp = *left;
		*left = (*left)->right;
	}
	else if ((dim == 0) && (*left)->pos.x >= (*right)->pos.x)
	{
		// C(13)
		tmp = *right;
		*right = (*right)->right;
	}
	else if (dim == 1 && (*left)->pos.y < (*right)->pos.y)
	{
		// C(14)
		tmp = *left;
		*left = (*left)->right;
	}
	else if (dim == 1 && (*left)->pos.y >= (*right)->pos.y)
	{
		// C(15)
		tmp = *right;
		*right = (*right)->right;
	}
	else if (dim == 2 && (*left)->pos.z < (*right)->pos.z)
	{
		// C(16)
		tmp = *left;
		*left = (*left)->right;
	}
	else if (dim == 2 && (*left)->pos.z >= (*right)->pos.z)
	{
		// C(17)
		tmp = *right;
		*right = (*right)->right;
	}
	// printf("get_next_smallest_by_dim return : %p\n", tmp);
	tmp->right = NULL;
	return (tmp);
}

static t_kd_tree	*split_list(t_kd_tree *tree, int length)
{
	int 		i;
	t_kd_tree	*tmp;
	t_kd_tree	*tmp2;

	tmp = tree;
	i = 0;
	while (++i < length)
	{
		tmp = tmp->right;
	}
	tmp2 = tmp->right;
	tmp->right = NULL;
	return (tmp2);
}

static int	get_length(t_kd_tree *root)
{
	int i;

	// printf("get_length: ");
	i = 0;
	while (root)
	{
			// printf("%p\n", root);
		++i;
		root = root->right;
	}
	// printf("%d\n", i);
	return (i);
}


static t_kd_tree	*get_median(t_kd_tree *root, int length)
{
	t_kd_tree	*median;
	int			i;

	i = 0;
	while (++i < length) 
		root = root->right;
	// printf("found median: [%p] [%f, %f, %f] (length: %d)\n", root, root->pos.x, root->pos.y, root->pos.z, length);
	return (root);
}

static t_kd_tree	*split_without_median(t_kd_tree *root, t_kd_tree **median)
{
	t_kd_tree	*right;
	// int			i;

	// printf("split_without_median: %p\n", *median);
	right = NULL;
	// i = 0;
	//iterate through list until link BEFORE the median
	// printf("root: %p\n", root);
	while (root != *median && root->right != *median)
	{
		root = root->right;
		// printf("root: %p\n", root);
	}
	// printf("stopped at: %p with i: %d\n", root, i);  
	if (root != *median)  
	{ 
		right = root->right->right;
		// printf("set right to %p\n", right);
	}
	else
		right = root->right;
	root->right = NULL;
	return (right);
}

__host__
void	print_photons2(t_kd_tree *tree)
{
	if (!tree)
		return ;
	// print_photons(tree->left);
	printf("photon: [%p] [%f, %f, %f]\n", tree, tree->pos.x, tree->pos.y, tree->pos.z);
	print_photons2(tree->right);
}