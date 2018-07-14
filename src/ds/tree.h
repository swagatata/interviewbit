/*
 * tree.h
 *
 *  Created on: 15-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_DS_TREE_H_
#define SRC_DS_TREE_H_



struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


#endif /* SRC_DS_TREE_H_ */
