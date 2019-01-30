/*
 * rom2int.h
 *
 *  Created on: Sep 7, 2018
 *      Author: Chander Raja
 */

#ifndef ROMAN2INT_H_
#define ROMAN2INT_H_

#include <string>

///
/// roman2int is a utility function to convert a roman number string
/// returns the integer value of the Roman string if it is valid
/// returns -1 if the Roman number has incorrect notation or
/// invalid characters (e.g. MCM@VIII)
///
/// NOTE: 1. In this implementation, IIII is a valid alternate
///          notation for 4.
///       2. The maximum Roman number supported is MMM (3000)
///       3. Only upper case Roman numerals are supported
int roman2int(std::string roman_str);



#endif /* ROMAN2INT_H_ */
