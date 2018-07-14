/*
 * tree.h
 *
 *  Created on: 15-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_HELPER_TREE_H_
#define SRC_HELPER_TREE_H_


#include "../includes.h"

int balanced_height(TreeNode* A) {
    if (A==nullptr) return 0;

    int leftHeight = balanced_height(A->left);
    if (leftHeight < 0) return -1;

    int rightHeight = balanced_height(A->right);
    if (rightHeight < 0) return -1;

    int diff = leftHeight - rightHeight;

    if (diff < 2 && diff > -2) {
        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    } else {
        return -1;
    }
}

bool is_balanced(TreeNode* A) {
    int height = balanced_height(A);

    return height >= 0;
}

vector<int> in_order(TreeNode *A) {
	stack<pair<TreeNode *, int> > s;
	s.push(make_pair(A, 0));
	vector<int> v;
	while (s.size()) {
		auto top = s.top(); s.pop();
		if (top.second == 0) {
			s.push(make_pair(top.first, 1));

			if (top.first->left) {
				s.push(make_pair(top.first->left, 0));
			}
		} else {
			v.push_back(top.first->val);

			if (top.first->right) {
				s.push(make_pair(top.first->right, 0));
			}
		}
	}

	return v;
}


#endif /* SRC_HELPER_TREE_H_ */
