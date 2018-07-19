/*
 * dp.h
 *
 *  Created on: 18-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_DP_H_
#define SRC_DP_H_

#include "includes.h"
#include "helper/math.h"

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

ull combinations(ui n, ui k) {
	ui ** c;
	c = new ui*[n+1];
	FOR(i, (n+1)) {
		c[i] = new ui[k+1];
		c[i][0] = 1;
	}
	FOR(i, (k+1)) {
		c[0][i] = 0;
	}

	c[0][0] = 1;
	for (ui i = 1; i <= n; ++i) {
		for (ui j = 1; j <= min(i,k); ++j) {
			if (i == j) {
				c[i][j] = 1;
			} else {
				c[i][j] = c[i-1][j] + c[i-1][j-1];
			}
			cout << "c[" << i << "][" << j << "] is " << c[i][j] << endl;
		}
	}

	return c[n][k];
}

void test_combinations() {
	combinations(10, 4);
}

bool subset_sum(vector<int> v, ull sum) {
	bool * ss;

	ss = new bool[sum+1];

	ss[0] = true;
	for (ui i = 1; i <= sum; ++i) {
		ss[i] = false;
	}

	for (ui j = 1; j <= v.size(); ++j) {
		for (int i = 1; i <= sum; ++i) {
			ss[i] = ss[i] || ((i - v[j-1]) >= 0 ? ss[i - v[j-1]] : false);
		}
	}

	return ss[sum];
}

void test_subset_sum() {
	int a[] = {3, 34, 4, 12, 5, 2};
	vector<int> v(a, a + 6);

	cout << "(Test 1) "<< (subset_sum(v, 9)  ? "Passed" : "Failed") << endl;

	v.clear();
	cout << "(Test 2) "<< (!subset_sum(v, 9)  ? "Passed" : "Failed") << endl;
	cout << "(Test 3) "<< (subset_sum(v, 0)  ? "Passed" : "Failed") << endl;
}

// https://www.geeksforgeeks.org/subset-sum-divisible-m/
bool subset_sum_divisible(vector<int> v, ui sum) {
	bool ** ssd;

	ssd = new bool*[v.size() + 1];
	FOR(i, (v.size()+1)) {
		ssd[i] = new bool[sum];
	}

	FOR(i, sum) {
		ssd[0][i] = false;
		ssd[1][i] = false;
	}
	ssd[1][v[0]%sum] = true;

	for (ui i = 2; i <= v.size(); ++i) {
		for (ui j = 0; j < sum; ++j) {
			ssd[i][j] = ssd[i-1][j] || ssd[i-1][mod(j-v[i-1], sum)] || (j == v[i-1]%sum);
			// cout << "ssd[" << i << "][" << j << "] = " << ssd[i][j] << endl;
		}
	}

	return ssd[v.size()][0];
}

void test_subset_sum_divisible() {
	int a[] = {3, 34, 4, 12, 5, 2};
	vector<int> v(a, a + 6);

	cout << "(Test 1) "<< (subset_sum_divisible(v, 9)  ? "Passed" : "Failed") << endl;

	int b[] = {3, 1, 7, 5};
	vector<int> vb(b, b + 4);
	cout << "(Test 2) "<< (subset_sum_divisible(vb, 6)  ? "Passed" : "Failed") << endl;

	int c[] = {1, 6};
	vector<int> vc(c, c + 2);
	cout << "(Test 3) "<< (!subset_sum_divisible(vc, 5)  ? "Passed" : "Failed") << endl;
}

ui longest_inc_subsequence_length(vector<int> &v) {
	if (v.size() < 2) return v.size();

	ui * lisl = new ui[v.size()];

	lisl[0] = 1;
	ui max_l = 0, max_ll =0;
	for (ui i = 1; i < v.size(); ++i) {
		max_l = 1;
		for (ui j = 0; j < i; ++j) {
			if (v[j] <= v[i]) {
				ui l = 1 + lisl[j];
				if (l > max_l) {
					max_l = l;
					if (max_l > max_ll)
						max_ll = max_l;
				}
			}
		}
		lisl[i] = max_l;
	}

	return max_ll;
}

void test_longest_inc_subsequence_length() {
	int a[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
	vector<int> v(a, a+9);

	cout << "(Test 1) "<< (longest_inc_subsequence_length(v) == 6  ? "Passed" : "Failed") << endl;
}

int numDecodings(string A) {
	ui n = A.size();
	if (n == 0) return 0;
	if (n == 1) return 1;

	vector<ui> nd(A.size());

	nd[0] = 1;
	for (ui i = 1; i < n; ++i) {
		nd[i] = 0;
		if (A[i] != '0') {
			nd[i] += nd[i-1];
		}

		// cout << "nd[i] " << nd[i] << endl;


		string sub = A.substr(i-1, 2);
		// cout << "sub " << sub << endl;
		int chr = stoi(sub, nullptr, 10);
		// cout << "chr " << chr << endl;

		if (chr > 9 && chr < 27) {
			if (i >= 2) {
				nd[i] += nd[i-2];
			} else {
				nd[i] += 1;
			}
		}

		// cout << "nd[i] " << nd[i] << endl;
	}

	return nd[n-1];
}

void test_numDecodings() {
	cout << "(Test 1) "<< (numDecodings("12") == 2  ? "Passed" : "Failed") << endl;
}

int maxProfit(const vector<int> &A) {
	if (A.size() < 2) return 0;

	int min = A[0];
	int profit;
	int max_profit = 0;
	for (int i = 1; i < A.size(); ++i) {
		if (A[i] > min) {
			profit = A[i] - min;
			if (profit > max_profit)
				max_profit = profit;
		} else {
			min = A[i];
		}
	}

	return max_profit;
}

void test_maxProfit() {
	int a[] = {1, 2};
	vector<int> v(a, a+2);

	cout << "(Test 1) "<< (maxProfit(v) == 1  ? "Passed" : "Failed") << endl;
}

#endif /* SRC_DP_H_ */
