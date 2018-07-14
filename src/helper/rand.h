/*
 * rand.h
 *
 *  Created on: 15-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_HELPER_RAND_H_
#define SRC_HELPER_RAND_H_

#include "../includes.h"

/**
 * Generate r random numbers in the given range [m,n]
 *
 * Can generate only numbers between 0 and RAND_MAX(which is usually the same as INT_MAX)
 */
vector<ui> generate_random(ui r, ui m, ui n) throw(string) {
	if (m > n) throw "Illegal Arguments : Invalid Range : m should be less than or equal to n";

	if (m == n) {
		return *(new vector<ui>(r, m));
	}

	if ((n - m + 1) > RAND_MAX) {
		throw "Illegal Arguments : Range wider than RAND_MAX";
	}

	vector<ui> v(r);
	srand(time(0));

	ui range = n - m + 1;
	FOR(i, r) {
		v[i] = (m + rand() % range);
	}

	return v;
}


#endif /* SRC_HELPER_RAND_H_ */
