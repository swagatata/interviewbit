/*
 * stack_queue.h
 *
 *  Created on: 14-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_STACK_QUEUE_H_
#define SRC_STACK_QUEUE_H_

#include "includes.h"
#include "helper/string.h"
#include "helper/tests.h"

string simplify_path(string s) {
	auto vs = split(s, '/');

	deque<string> dq;
	for (auto a : vs) {
		if (a.size() < 1)
			continue;

		if (a.compare("..") == 0) {
			if (dq.size() > 0) {
				dq.pop_back();
			}
			continue;
		}

		if (a.compare(".") == 0) {
			continue;
		}

		dq.push_back(a);
	}

	if (dq.empty()) return "/";

	stringstream path;
	while(!dq.empty()) {
		path << "/" << dq.front();
		dq.pop_front();
	}

	return path.str();
}

void test_simplify_path() {
	cout << "Test 1 "<< ((simplify_path("/a/./b/../../c/").compare("/c") == 0) ? "Passed" : "Failed") << endl;
	cout << "Test 2 "<< ((simplify_path("/").compare("/") == 0) ? "Passed" : "Failed") << endl;
	cout << "Test 3 "<< ((simplify_path("/.").compare("/") == 0) ? "Passed" : "Failed") << endl;
	cout << "Test 4 "<< ((simplify_path("//").compare("/") == 0) ? "Passed" : "Failed") << endl;
	cout << "Test 5 "<< ((simplify_path("/..").compare("/") == 0) ? "Passed" : "Failed") << endl;
	cout << "Test 6 "<< ((simplify_path("/a/./b/../../c").compare("/c") == 0) ? "Passed" : "Failed") << endl;
	cout << "Test 7 "<< ((simplify_path("/a/./b/../../c/..").compare("/") == 0) ? "Passed" : "Failed") << endl;
}

// https://www.interviewbit.com/problems/redundant-braces/
int redundant_braces(string s) {
	stack<char> st;

	for (char c : s) {
		// cout << "char is " << c << endl;
		if (c == '(') {
			st.push('(');
		} else if (c == ')') {
			// is there content?
			// if not this is redundant
			if (st.top() == 'o') {
				st.pop(); // pop operator
				st.pop(); // pop left parentheses
			} else {
				return 1;
			}
		} else if (c == ' ') {
			continue;
		} else if (c == '+' || c == '-' || c == '*' || c == '/'){
			st.push('o');
		}
	}

	return 0;
}

void test_redundant_braces() {
	cout << "Test 1 "<< (redundant_braces("((a + b))") == 1 ? "Passed" : "Failed") << endl;
	cout << "Test 2 "<< (redundant_braces("(a + (a + b))") == 0 ? "Passed" : "Failed") << endl;
	cout << "Test 3 "<< (redundant_braces("()") == 1 ? "Passed" : "Failed") << endl;
	cout << "Test 4 "<< (redundant_braces("((a))") == 1 ? "Passed" : "Failed") << endl;
	cout << "Test 5 "<< (redundant_braces("(a + ((c) + b))") == 1 ? "Passed" : "Failed") << endl;
}

// https://www.interviewbit.com/problems/nearest-smaller-element/
vector<int> prev_smaller(vector<int> &A) {
	vector<int> ps(A.size());
	ps[0] = -1;

	stack<pair<int, int> > st;
	st.push(make_pair(A[0], 0));

	for (int i = 1; i < A.size(); ++i) {
		int a = A[i];

		while (st.size() > 0 && a <= st.top().first) {
			st.pop();
		}
		if (st.size() > 0)
			ps[i] = st.top().second;
		else
			ps[i] = -1;

		st.push(make_pair(a, i));
	}

	return ps;
}

void test_prev_smaller() {

}

vector<int> next_smaller(vector<int> &A) {
	int n = A.size();
	vector<int> ps(n);
	ps[n-1] = -1;

	stack<pair<int, int> > st;
	st.push(make_pair(A[n-1], n-1));

	for (int i = n - 1; i >= 0; --i) {
		int a = A[i];

		while (st.size() > 0 && a <= st.top().first) {
			st.pop();
		}
		if (st.size() > 0)
			ps[i] = st.top().second;
		else
			ps[i] = -1;

		st.push(make_pair(a, i));
	}

	return ps;
}

int largestRectangleArea(vector<int> &A) {
	// for each element get nearest smaller element on left and right sides
	vector<int> lefts = prev_smaller(A);
	vector<int> rights = next_smaller(A);

//	pv(lefts);
//	pv(rights);

	int max_area = 0;
	for (int i = 0; i < A.size(); ++i) {
		int left_l = i - (lefts[i]);// inclusive of i
		int right_l = (rights[i] == -1 ? A.size() : rights[i]) - i - 1;
		int area = (left_l + right_l) * A[i];

		if (area > max_area) max_area = area;
	}

	return max_area;
}

void test_largestRectangleArea() {
	int a[6] = {3, 5, 2, 2, 1, 4};
	vector<int> v(a, a+6);

	cout << "Test 1 "<< (largestRectangleArea(v) == 8 ? "Passed" : "Failed") << endl;

	v.resize(1);
	v[0] = 3;

	cout << "Test 2 "<< (largestRectangleArea(v) == 3 ? "Passed" : "Failed") << endl;
}

// assum 1 : distinct elements
vector<int> slidingMaximum(const vector<int> &v, int w) {
	if (w > v.size()) {
		vector<int> ve;
		ve.push_back(*(max_element(v.begin(), v.end())));

		return ve;
	}

	deque<pair<int, int> > dq;
	dq.push_back(make_pair(v[0], 0));

	for (int i = 1; i < w; ++i) {
		while (dq.size() > 0 && v[i] >= dq.back().first) {
			dq.pop_back();
		}
		dq.push_back(make_pair(v[i], i));
	}

	vector<int> max;
	max.push_back(dq.front().first);

	for (size_t wend = w; wend < v.size(); ++wend) {
		if (wend - w == dq.front().second) {
			dq.pop_front();
		}

		while (dq.size() > 0 && v[wend] >= dq.back().first) {
			dq.pop_back();
		}
		dq.push_back(make_pair(v[wend], wend));

		max.push_back(dq.front().first);
	}

	return max;
}

void testslidingMaximum() {
	int a[5] = {3, 2, 1, 5, 4};
	vector<int> v(a, a+5);
	vector<int> act;// = slidingMaximum(v, 2);

	int b[4] = {3, 2, 5, 5};
	vector<int> exp(b, b+4);

	cout << "Test 1 "<< (compare_vectors(act, exp) ? "Passed" : "Failed") << endl;

	v.resize(1);
	v[0] = 3;
	act = slidingMaximum(v, 2);
	cout << "Test 2 "<< (compare_vectors(act, v) ? "Passed" : "Failed") << endl;

	int at[50] = {648, 614, 490, 138, 657, 544, 745, 582, 738, 229, 775, 665, 876, 448, 4, 81, 807, 578, 712, 951, 867, 328, 308, 440, 542, 178, 637, 446, 882, 760, 354, 523, 935, 277, 158, 698, 536, 165, 892, 327, 574, 516, 36, 705, 900, 482, 558, 937, 207, 368};
	vector<int> vt(at, at+50);
	act = slidingMaximum(vt, 9);
	int bt[] = {745,745,775,775,876,876,876,876,876,876,876,951,951,951,951,951,951,951,951,951,882,882,882,882,935,935,935,935,935,935,935,935,935,892,892,892,900,900,900,937,937,937};
	vector<int> expt(bt, bt+42);

	cout << "Test 3 "<< (compare_vectors(act, expt) ? "Passed" : "Failed") << endl;
}

int rainWaterTrapped(const vector<int> &A) {
	if (A.size() < 3) return 0;

	int n = A.size();
	vector<int> leftmax(n);
	vector<int> rightmax(n);
	leftmax[0] = A[0];
	rightmax[n - 1] = A.back();
	for (int i = 1; i < n; ++i) {
		if (A[i] >= leftmax[i - 1])
			leftmax[i] = A[i];
		else
			leftmax[i] = leftmax[i-1];

		if (A[n - i - 1] >= rightmax[n - i])
			rightmax[n - i - 1] = A[n - i - 1];
		else
			rightmax[n - i - 1] = rightmax[n - i];
	}

//	pv(leftmax);
//	pv(rightmax);

	unsigned long long area = 0;
	for (int i = 1; i < A.size() - 1; ++i) {
		int edge = min(leftmax[i-1], rightmax[i+1]);
		if (edge > A[i]) {
			area += (edge - A[i]);
		}
	}

	return area;
}

void testrainWaterTrapped() {
	int a[] = {0,1,0,2,1,0,1,3,2,1,2,1};
	vector<int> v(a, a+12);

	cout << "Test 1 "<< (rainWaterTrapped(v) == 6 ? "Passed" : "Failed") << endl;
}

#endif /* SRC_STACK_QUEUE_H_ */
