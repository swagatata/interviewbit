/*
 * os.h
 *
 *  Created on: 15-Jul-2018
 *      Author: swagat
 */

#ifndef SRC_EXPERIMENTS_OS_H_
#define SRC_EXPERIMENTS_OS_H_

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <cstdlib>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "../ds/semaphore.h"

using namespace std;
void test_shared_memory() {
	int shid = shmget(4455, 1048576, IPC_CREAT | 0660);
	if (shid <  0) {
		perror("shmget");
		exit(1);
	}

	char * shaddr;
	if ((shaddr = static_cast<char *>(shmat(shid, nullptr, SHM_RND))) == (char *)-1) {
		perror("shmat");
		exit(1);
	}

	int pid;
	switch(pid = fork()) {
	case -1:perror("fork");
			exit(1);
	case  0:cout << "Start child process" << endl;
			break;
	default:cout << "Continue parent process" << endl;
	}

	if (pid != 0) {
		char * s = shaddr;
		for (int i = 0; i < 400; ++i) {
			for (char c = 'a'; c <= 'z'; ++c) {
				*(s++) = c;
			}
			*(s++) = '\n';
			cout << "wrote " << i + 1 << " lines" << endl;
		}
		*s = '\0';
	} else {
		cout << "(child) Buffer size in bytes is " << strlen(shaddr) << endl;
	}

	shmdt(shaddr);
}

std::mutex cout_mtx, full, empty;

size_t p_i, c_i;
struct PC {
	size_t size;
	int * buffer;
	deque<char> *dq;
	Semaphore *s_full, *s_empty;

	PC(size_t s) {
		size = s;
		buffer = new int[size];
		dq = new deque<char>();

		p_i = 0;
		c_i = 0;

		empty.lock();
		s_full = new Semaphore(0);
		s_empty = new Semaphore(size);
	}

	void consumer() {
		{
			std::lock_guard<std::mutex> lock(cout_mtx);
			cout << "(consumer) start" << endl;
		}
		while (1) {
			if (p_i < c_i) {
				perror("invalid state : consumer ahead of producer");
				exit(1);
			}
			while (p_i == c_i);

			if (buffer[c_i % size] != 1) {
				{
					perror("invalid state : consumer reading non 1 value");
					exit(1);
				}
			}
			buffer[c_i % size] = 0;
//			{
//				lock_guard<mutex> lock(cout_mtx);
//				cout << "(consumer) read " << c_i % size << endl ;
//			}
			++c_i;

			//usleep(400000);
		}
	}

	void producer() {
		{
			std::lock_guard<std::mutex> lock(cout_mtx);
			cout << "(producer) start" << endl;
		}
		while (1) {
			if (p_i < c_i) {
				perror("invalid state : consumer ahead of producer");
				exit(1);
			}
			while (p_i >= c_i + size);

			if (buffer[p_i % size] != 0) {
				{
					perror("invalid state : producer writing non 0 value");
					exit(1);
				}
			}
			buffer[p_i % size] = 1;
//			{
//				std::lock_guard<std::mutex> lock(cout_mtx);
//				cout << "(producer) write " << p_i % size << endl ;
//			}
			++p_i;

			//usleep(400000);
		}
	}

	void producer_new() {
		{
			std::lock_guard<std::mutex> lock(cout_mtx);
			cout << "(producer_new) start" << endl;
		}
		while(true) {
			//while (dq->size() >= size);
			s_empty->down();

			char c = 'a' + rand() % 26;
			{
				std::lock_guard<std::mutex> lock(cout_mtx);
				cout << "(producer_new) wrote " << c << " " << dq->size() << endl;
			}
			dq->push_back(c);

			s_full->up();

			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}

	void consumer_new() {
		{
			std::lock_guard<std::mutex> lock(cout_mtx);
			cout << "(consumer_new) start" << endl;
		}
		while(true) {
			s_full->down();

			char c = dq->front();
			{
				std::lock_guard<std::mutex> lock(cout_mtx);
				cout << "(consumer_new) read " << c << endl;
			}
			dq->pop_front();

			s_empty->up();

			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}

//	~PC() {
//		delete [] buffer;
//	}
};

#endif /* SRC_EXPERIMENTS_OS_H_ */
