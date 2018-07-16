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

void pre_order(TreeNode *A) {
	if (A == nullptr) return;

	cout << A->val << ",";
	pre_order(A->left);
	pre_order(A->right);
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

void bst_insert(TreeNode * root, TreeNode * newNode) {
	if (root == nullptr || newNode == nullptr) return;

	if (root->val >= newNode->val) {
		if (root->left)
			bst_insert(root->left, newNode);
		else
			root->left = newNode;
	} else {
		if (root->right)
			bst_insert(root->right, newNode);
		else
			root->right = newNode;
	}
}

TreeNode * build_bst(ui size = 100) {
	auto rands = generate_random(size, 1, size);
	auto * root = new TreeNode(rands[0]);

	for (ui i = 1; i < size; ++i) {
		bst_insert(root, new TreeNode(rands[i]));
	}

	return root;
}

TreeNode * findPredecessor(TreeNode * root) {
	if (!root) return nullptr;

	if (root->left == nullptr) return nullptr;

	TreeNode * cur = root->left;
	while (cur->right != nullptr && cur->right != root) {
		cur = cur->right;
	}

	return cur;
}

vector<int> in_order_morris(TreeNode * root) {
	vector<int> v;
	if (!root) return v;

	TreeNode * current = root;
	while (current) {
		if (current->left) {
			auto * predecessor = findPredecessor(current);
			if (predecessor->right) {
				predecessor->right = nullptr;
				v.push_back(current->val);
				current = current->right;
			} else {
				predecessor->right = current;
				current = current->left;
			}
		} else {
			v.push_back(current->val);
			current = current->right;
		}
	}

	return v;
}

void test_in_order_morris() {
	auto * root = build_bst(500);

	auto v1 = in_order(root);
	auto v2 = in_order_morris(root);

	cout << "(Test 1) "<< (compare_vectors(v1, v2)  ? "Passed" : "Failed") << endl;
}

#endif /* SRC_HELPER_TREE_H_ */
