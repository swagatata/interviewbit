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

#endif /* SRC_STACK_QUEUE_H_ */
