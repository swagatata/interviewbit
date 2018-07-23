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

int maxProfitOneTransaction(const vector<int> &A) {
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

void test_maxProfitOneTransaction() {
	int a[] = {1, 2};
	vector<int> v(a, a+2);

	cout << "(Test 1) "<< (maxProfitOneTransaction(v) == 1  ? "Passed" : "Failed") << endl;
}

// https://www.interviewbit.com/problems/best-time-to-buy-and-sell-stocks-ii/
// any number of transactions where a buy cannot be on the same day as a prev sell.
int maxProfit(const vector<int> &prices) {
	size_t n = prices.size();
	if (n < 2) return 0;

	vector<int> DP(n);
	for (int i = n-2; i >= 0; --i) {
		int profit = 0, max_profit = 0;
		for (size_t j = i+1; j < n; ++j) {
			if (prices[j] > prices[i]) {
				profit = (prices[j] - prices[i]) + ((j < (n-1)) ? DP[j+1] : 0);
				if (profit > max_profit)
					max_profit = profit;
			}
		}
		if (DP[i+1] > max_profit)
			max_profit = DP[i+1];

		DP[i] = max_profit;
		// cout << "DP[" << i << "] : " << max_profit << endl;
	}

	return *max_element(DP.begin(), DP.end());
}

// any number of transactions where a buy can be on the same day as a prev sell.
int maxProfitAlt(const vector<int> &prices) {
	size_t n = prices.size();
	if (n < 2) return 0;

	int cur = prices[0];
	int mp = 0;
	for (int i = 1; i < n; ++i) {
		if (prices[i] < cur) {
			cur = prices[i];
		} else {
			mp += (prices[i] - cur);
			cur = prices[i];
		}
	}

	return mp;
}

void test_maxProfit() {
	int a[307] = {7551982,8124939,4023780,7868369,4412570,2542961,7380261,1164290,7781065,1164599,2563492,5354415,4994454,2627136,5933501,668219,1821804,7818378,33654,4167689,8652323,5750640,9822437,3466466,554089,6168826,335687,2466661,8511732,6288553,2905889,7747975,3744045,1545003,1008624,8041203,7176125,4321092,714053,7200073,166697,7814651,3090485,8318668,6600364,3352620,2430137,7685821,1442555,828955,6540266,5305436,116568,1883410,7975347,9629015,4735259,6559041,1832532,5840170,6983732,5886179,1496505,7241412,144558,9462840,8579314,2488436,9677478,7589124,5636642,2440601,1767332,2399786,6299635,8534665,1367339,805592,5572668,6990026,8465261,4808596,7641452,8464860,3170126,7403200,6932907,3776122,1313688,3992189,2382116,3886952,349816,1596435,7353742,9964868,9882224,3818546,3885458,1200559,3910256,7949895,463872,6392805,9513226,3427933,3470571,6225817,552452,5567651,6414423,6701681,4725847,894529,8046603,426263,5280891,9197661,9764507,1740413,9530261,9163599,7561587,5848442,7312422,4794268,5793465,5039382,5147388,7346933,4697363,6436473,5159752,2207985,8256403,8958858,6099618,2172252,3063342,4324166,3919237,8985768,2703255,2386343,3064166,247762,7271683,1812487,7163753,4635382,449426,2561592,3746615,8741199,6696192,606265,5374062,3065308,6918398,2956279,8949324,2804580,3421479,7846658,8895839,8277589,1262596,451779,9972218,6378556,4216958,7127258,8593578,326883,4737513,6578257,7582654,8675499,9038961,7902676,8874020,5513073,631930,912719,8394492,1508363,455175,9215635,6813970,2021710,5673212,184474,4511247,4653238,2218883,9669544,295018,3694660,1709444,4019025,5047809,45740,1035395,8159408,1557286,1304144,6496263,2094202,9945315,1905585,1143081,6994125,9609830,1077628,3488222,6299366,7187139,3883908,7077292,3210807,7328762,7695314,1138834,7689433,5083719,202831,8138452,5495064,7543763,1597085,5429837,8455839,6925605,6600884,3571512,3422637,8911245,3700762,2338168,6830853,2539094,490627,2294717,497349,8297867,7299269,4769134,285033,4335917,9908413,152868,2658658,3525848,1884044,4953877,8660374,8989154,888731,7217408,2614940,7990455,9779818,1441488,9605891,4518756,3705442,9331226,404585,9011202,7355000,7461968,6512552,2689841,2873446,256454,1068037,8786859,2323599,3332506,2361155,7476810,5605915,5950352,6491737,8696129,4637800,4207476,9334774,840248,9159149,5201180,7211332,3135016,8524857,4566111,7697488,1833291,7227481,8289951,2389102,9102789,8585135,1869227,4082835,8447466,4985240,4176179};
	vector<int> v(a, a+307);
	int mp = maxProfitAlt(v);

	cout << "(Test 1) "<< (maxProfitAlt(v) == 552236226  ? "Passed" : "Failed") << endl;
}

#endif /* SRC_DP_H_ */
