#include <stdio.h>
#include <assert.h>

#include "tree_ops.h"

bst_t *InitBigTree();
int Int_Node_Compare(void *iter_data, void *new_data, void *param);
void PrintTreeByLevelTest();


int main()
{
	PrintTreeByLevelTest();
	
	return 0;
}

void PrintTreeByLevelTest()
{
	bst_t *tree = InitBigTree();
	
	PrintTreeByLevel(tree);
	
	BSTDestroy(tree);
}

int Int_Node_Compare(void *iter_data, void *new_data, void *param)
{
	int result = 0;
	int iter_int_data = *(int *)iter_data;
	int new_int_data = *(int *)new_data;	
	(void)(param);

	assert(NULL != iter_data);
	assert(NULL != new_data);
	
	if (iter_int_data > new_int_data)
	{
		result = 1;
	}

	else if (iter_int_data < new_int_data)
	{
		result = -1;
	}
	else /* iter_int_data == new_int_data */
	{
		result = 0;
	}
	
	return result;
}

bst_t *InitBigTree()
{
	bst_t *bst = BSTCreate(Int_Node_Compare, NULL);	
	
	int a_root = 15;
	int b_two_kids_not_root = 97;
	int c_leaf_right_child = 301;
	int d_one_left_child = 14;
	int e_left_leaf = 11;
	int f_left_leaf = 50;
	int g = 67, h= 70, i =19 , j = 22, k = 33, l = 44, m = 55, n = 66;
	
	BSTInsert(bst, &a_root);
	BSTInsert(bst, &b_two_kids_not_root); 
	BSTInsert(bst, &c_leaf_right_child); 
	BSTInsert(bst, &d_one_left_child);  
	BSTInsert(bst, &e_left_leaf);
	BSTInsert(bst, &f_left_leaf);									
	BSTInsert(bst, &g);
	BSTInsert(bst, &h);
	BSTInsert(bst, &i);
	BSTInsert(bst, &j);
	BSTInsert(bst, &k);
	BSTInsert(bst, &l);
	BSTInsert(bst, &m);
	BSTInsert(bst, &n);
	
	return bst;
}

bst_t *InitSmallTree()
{
	bst_t *bst = BSTCreate(Int_Node_Compare, NULL);	
	
	int a_root = 15;
	int b_two_kids_not_root = 97;
	int c_leaf_right_child = 301;
	int d_one_left_child = 14;
	int e_left_leaf = 11;
	int f_left_leaf = 50;
	int g = 67, h= 70, i =19 , j = 22, k = 33, l = 44, m = 55, n = 66;
	
	BSTInsert(bst, &a_root);
	BSTInsert(bst, &b_two_kids_not_root); 
	BSTInsert(bst, &c_leaf_right_child); 
	BSTInsert(bst, &d_one_left_child);  
	BSTInsert(bst, &e_left_leaf);
	BSTInsert(bst, &f_left_leaf);									
	BSTInsert(bst, &g);
	BSTInsert(bst, &h);
	BSTInsert(bst, &i);
	BSTInsert(bst, &j);
	BSTInsert(bst, &k);
	BSTInsert(bst, &l);
	BSTInsert(bst, &m);
	BSTInsert(bst, &n);
	
	return bst;
}
