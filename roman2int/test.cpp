//============================================================================
// Name        : main.cpp
// Author      : Chander Raja
// Version     :
// Copyright   :
// Description : Unit test for roman2int utility
//============================================================================

#include <iostream>
#include <list>
#include <utility>

#include "roman2int.h"

using namespace std;

int main(int argc, char *argv[])
{
	list<pair<string, int>> testVectors =
	{
		{ "I", 1 },
		{ "V", 5 },
		{ "XL", 40 },
		{ "foo", -1 },
		{ "0", -1 },
		{ "MCMLX_XXIV", -1 },
		{ "VV", -1 },
		{ "MCMLXXXIV", 1984 },
		{ "VL", -1 },
		{ "MCMLXXHVII", -1 },
		{ "IIII", 4 },
		{ "MCD", 1400 }
	};

	cout << "Starting tests ..." << endl;

	auto it = testVectors.begin();

	while (it != testVectors.end()) {

		int val = roman2int(it->first);
		bool success = (val == it->second);
		string passfail = success? string("PASS"): string("*FAIL*");

		cout << "Testing " << it->first << ", expected "
				<< it->second << ", got " << val
				<< "..." << passfail
				<< endl;

		if (not success) {
			break;
		}
		++it;
	}

    return 0;
}

