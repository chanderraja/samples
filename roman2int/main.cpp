//============================================================================
// Name        : main.cpp
// Author      : Chander Raja
// Version     :
// Copyright   :
// Description : Convert a Roman Number to an integer
//============================================================================

#include <iostream>
#include "roman2int.h"

using namespace std;

int main(int argc, char *argv[])
{

    if (argc != 2) {
        cerr << "Usage: " + string(argv[0]) + " <roman number>" << endl;
        return -1;
    }

    string roman_str(argv[1]);

    int val = roman2int(roman_str);

    if (val == -1) {
        cout << "Invalid Roman number" << endl;
        return -1;
    }

    cout << val << endl;

    return 0;
}

