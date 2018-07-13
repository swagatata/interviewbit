/*
 * stl.h
 *
 *  Created on: Jul 13, 2018
 *      Author: swagat
 */

#ifndef STL_H_
#define STL_H_

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void test_max() {
	cout << max<int>(3, 2) << endl;

	int a[5] = {3, 4, 2, 5, 1};
	vector<int> v(a, a+5);

	cout << "Vector is" << endl;
	for (auto i : v)
		cout << i << " " ;
	cout << endl;

	auto max_it = max_element(v.begin(), v.end());
	cout << *max_it << endl;

	auto mm = minmax(9, 10);
	cout << "min is " << mm.first << endl;
	cout << "max is " << mm.second << endl;
}

#endif /* STL_H_ */
