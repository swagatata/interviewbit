/*
 * semaphore.h
 *
 *  Created on: 16-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_DS_SEMAPHORE_H_
#define SRC_DS_SEMAPHORE_H_

#include <mutex>

using namespace std;

class Semaphore {
private:
	int val;
	mutex zero;
	mutex atom;

public:
	Semaphore(int n = 0) {
		val = n;

		if (val <= 0) {
			val = 0;
			zero.lock();
		}
	}

	void up() {
		lock_guard<std::mutex> atomic(atom);

		++val;
		zero.unlock();
	}

	void down() {
		lock_guard<std::mutex> atomic(atom);

		if (val <= 0) {
			atom.unlock();
			zero.lock();
		}
		--val;
	}
};


#endif /* SRC_DS_SEMAPHORE_H_ */
