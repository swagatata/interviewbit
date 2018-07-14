/*
 * string.h
 *
 *  Created on: Jul 13, 2018
 *      Author: swagat
 */

#ifndef STRING_H_
#define STRING_H_

#include "../includes.h"

using namespace std;

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

#endif /* STRING_H_ */
