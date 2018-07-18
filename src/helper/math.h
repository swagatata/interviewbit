/*
 * math.h
 *
 *  Created on: 19-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_HELPER_MATH_H_
#define SRC_HELPER_MATH_H_

#include "../includes.h"

// m should not be 0
ui mod(int n, ui m) {
	if (n < 0) {
		ui c = (n * -1)%m;
		return (c == 0 ? 0 : (m-c));
	} else
		return n % m;
}

void test_mod() {
	cout << "(Test 1) "<< (mod(0, 1) == 0 ? "Passed" : "Failed") << endl;
	cout << "(Test 2) "<< (mod(10, 1) == 0 ? "Passed" : "Failed") << endl;

	cout << "(Test 3) "<< (mod(10, 2) == 0 ? "Passed" : "Failed") << endl;
	cout << "(Test 4) "<< (mod(10, 3) == 1 ? "Passed" : "Failed") << endl;

	cout << "(Test 5) "<< (mod(-10, 3) == 2 ? "Passed" : "Failed") << endl;
	cout << "(Test 5) "<< (mod(-10, 1) == 0 ? "Passed" : "Failed") << endl;
}




#endif /* SRC_HELPER_MATH_H_ */
