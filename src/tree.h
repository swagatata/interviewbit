/*
 * tree.h
 *
 *  Created on: 15-Jul-2018
 *      Author: swagat
 *      Description: Interviewbit problems in trees section
 */

#ifndef SRC_TREE_H_
#define SRC_TREE_H_

#include "includes.h"
#include "helper/tree.h"

TreeNode *sorted_array_to_bbst_recursive(const vector<int> &v, size_t l, size_t r) {
	if (l >= r) return nullptr;

	if (l + 1 == r) return new TreeNode(v[l]);

	size_t mid = l + (r - l)/2;

	auto * left_subtree = sorted_array_to_bbst_recursive(v, l, mid);
	auto * right_subtree = sorted_array_to_bbst_recursive(v, mid + 1, r);

	auto * root = new TreeNode(v[mid]);
	root->left = left_subtree;
	root->right = right_subtree;

	return root;
}

// https://www.interviewbit.com/problems/sorted-array-to-balanced-bst/
TreeNode *sorted_array_to_bbst(const vector<int> &v) {
	return sorted_array_to_bbst_recursive(v, 0, v.size());
}

void test_sorted_array_to_bbst() {
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	vector<int> v(a, a+10);

	TreeNode * root = sorted_array_to_bbst(v);

	cout << "(test_sorted_array_to_bbst) Test 1 "<< (is_balanced(root) ? "Passed" : "Failed") << endl;

	auto act = in_order(root);
	cout << "(test_sorted_array_to_bbst) Test 2 "
			<< (compare_vectors<int>(act, v) ? "Passed" : "Failed") << endl;
}

#endif /* SRC_TREE_H_ */
