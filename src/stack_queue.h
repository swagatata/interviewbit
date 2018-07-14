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
#endif /* SRC_STACK_QUEUE_H_ */
