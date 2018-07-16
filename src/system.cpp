/*
 * system.cpp
 *
 *  Created on: 15-Jul-2018
 *      Author: swagat
 */


/**
 * Leslie Lamport's Bakery Algorithm
 */
#include "includes.h"

int n;
int * num = new int[n];
bool * choosing = new bool[n];

void locker(ui i) {
	choosing[i] = true;
	num[i] = 1 + *(max_element(num, num+n));
	choosing[i] = false;

	for (ui j = 0; j < n; ++j) {
		while(choosing[j]);
		while(num[j] != 0 && (num[j] < num[i] || (num[j] == num[i] && j < i)));
	}
}

void unlocker(ui i) {
	num[i] = 0;
}

int test_and_set(int * p) { // atomic
	int temp = *p;
	*p = 1;
	return temp;
}

void method() {
	int lock = 0;

	while(test_and_set(&lock) == 1);  //lock()
	// critical section
	lock = 0; // unlock
}

// intel atomic method
int xchg(int *p, int val) {
	int temp = *p;
	*p = val;
	return temp;
}

// spinlocks
void acquire(int *lock) {
	while (xchg(lock, 1) != 0);
}

void release(int *lock) {
	lock = 0;
}

// an improvement
void acquire2(int *lock) {
	while (xchg(lock, 1) != 0) {
		// most of the time is spent in the inner while loop
		// lock is read from cache instead of all the way from memory
		while (*lock != 0);
	}
}
