/*
 * dp.h
 *
 *  Created on: 18-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_DP_H_
#define SRC_DP_H_

#include "includes.h"

/**
 * n : should be greater than 0, behavior undefined otherwise
 *
 */
ull nth_ugly_number(ui n) {
	if (n < 1) return 0;
	if (n == 1) return 1;

	ull last2, last3, last5;
	vector<ull> UN;

	last2 = last3 = last5 = 0;
	UN.push_back(1);
	while(UN.size() < n) {
		ull next;
		if (2 * UN[last2] <= 3 * UN[last3]) {
			if (2 * UN[last2] <= 5 * UN[last5]) {
				next = (2 * UN[last2]);
				++last2;
			} else {
				next = (5 * UN[last5]);
				++last5;
			}
		} else {
			if (3 * UN[last3] <= 5 * UN[last5]) {
				next = (3 * UN[last3]);
				++last3;
			} else {
				next = (5 * UN[last5]);
				++last5;
			}
		}

		if (next != UN.back())
			UN.push_back(next);
	}

	return UN[n-1];
}

void test_nth_ugly_number() {

	cout << "(Test 1) "<< (nth_ugly_number(1) == 1  ? "Passed" : "Failed") << endl;
	cout << "(Test 2) "<< (nth_ugly_number(4) == 4  ? "Passed" : "Failed") << endl;
	cout << "(Test 3) "<< (nth_ugly_number(10) == 12  ? "Passed" : "Failed") << endl;
}

#endif /* SRC_DP_H_ */
