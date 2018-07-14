/*
 * tests.h
 *
 *  Created on: 14-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_HELPER_TESTS_H_
#define SRC_HELPER_TESTS_H_

#include "../includes.h"

template <class T>
bool compare_vectors(vector<T> &v1, vector<T> &v2) {
	if (v1.size() != v2.size()) return false;

	for (int i = 0; i < v1.size(); ++i)
		if (v1[i] == v2[i]) continue;
		else return false;

	return true;
}


#endif /* SRC_HELPER_TESTS_H_ */
