/** @file roman2int.cpp
 *  @brief Convert a Roman Number to an integer 
 *
 *  @author Chander Raja (chanderraja)
 *  @bug No known bugs.
 */

#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <set>

using namespace std;

namespace {

class ValueNode;
typedef std::map<char, ValueNode *> ValueNodeMap;

///
/// Class representing the root node of a Roman number tree
///
class RootNode
{
    static std::set<char> s_valid_numerals;
    ValueNodeMap m_tree;
    static string s_null_str;
    static bool s_init;

public:
    RootNode() {}
    virtual ~RootNode();
     virtual const string& romanNumStr() const { return s_null_str; }

    /// adds a the numeral r and associated value to the tree
    /// returns 0 if r is not a Roman numeral or if a node already exists for r
    /// NOTE: this will not overwrite if there is an existing node for r
    ValueNode * add(char r, int value); ///

    /// returns a pointer to the node representing the numeral r.
    /// returns 0 if r is not a roman numeral
    ValueNode * get(char r);

    /// returns the integral value of the Roman string r if valid
    /// returns -1 if invalid
    int getValue(string& r);

    /// returns true if the r is a valid Roman numeral, false otherwise
    static bool isValidNumeral(char r) { return s_valid_numerals.find(r) != s_valid_numerals.end(); }

};

string RootNode::s_null_str;
std::set<char> RootNode::s_valid_numerals = { 'M', 'D', 'C', 'L', 'X', 'V', 'I' };


///
/// Class representing an internal or leaf node of a Roman number tree
///
class ValueNode: public RootNode
{
    int m_value;
    string m_roman_num; // for debugging
public:
    ValueNode(int value, const string& roman_num): m_value(value), m_roman_num(roman_num) {}
    virtual ~ValueNode() {}
    int getValue(string& roman_str);
private:
    const string& romanNumStr() const { return m_roman_num; }

};


RootNode::~RootNode()
{
    auto it = m_tree.begin();

    while (it != m_tree.end()) {
        delete it->second;
        m_tree.erase(it);
        it = m_tree.begin();
    }
    // Note that I am building using a pre - C++11 compiler
    // otherwise I could have done the following:
    //     while (it != m_tree.end()) {
    //         delete it->second;
    //         it = m_tree.erase(it);
    //     }
}


ValueNode * RootNode::add(char r, int value)
{
	// if r is not a valid Roman numeral
	// or it already exists in the tree
	// return 0
    if (!isValidNumeral(r) || get(r)) {
        return 0;
    }

    string roman_num = romanNumStr() + r;
    ValueNode * node = new ValueNode(value, roman_num);
    if (node) {
        m_tree.insert(std::pair<char, ValueNode *>(r, node));
    }
    return node;
}

/// returns a pointer to the node representing the numeral r.
/// returns 0 if r is not a roman numeral
ValueNode * RootNode::get(char r)
{
    auto it = m_tree.find(r);
    return (it != m_tree.end())? it->second: 0;
}

int RootNode::getValue(string& roman_str)
{
    if (roman_str.empty()) {
        return 0;
    }

    if (!isValidNumeral(roman_str[0])) {
        // invalid numeral
        return -1;
    }

    auto it = m_tree.find(roman_str[0]);

    if (it == m_tree.end()) {
        // first char of numeral is a valid
        // Roman numeral but not found in our tree
        return 0;
    }

    // first char is found - recurse into the tree
    return it->second->getValue(roman_str);

}


int ValueNode::getValue(string& roman_str)
{
	// erase the first character in the string
    roman_str = roman_str.erase(0, 1);

    int retval = RootNode::getValue(roman_str);

    if (retval == -1) {
        // invalid chars found
        return -1;
    }

    if (retval > 0) {
        // match found in subtree, return returned value
        return retval;
    }

    // no match in sub tree, return our value
    return m_value;

}


} // namespace


//
// returns the integer value of the roman string if it is valid
// returns -1 if the roman numeral has incorrect notation or
// invalid characters
int roman2int(string roman_str)
{
	// Build trees for all Roman number notations representing 1000s, 100s, 10s and 1s
    RootNode thousands;
    thousands.add('M', 1000)->add('M', 2000)->add('M', 3000); // M, MM and MMM - we will limit the maximum value to 3000

    RootNode hundreds;
    hundreds.add('C', 100)->add('C', 200)->add('C', 300); // C, CC and CCC
    hundreds.get('C')->add('D', 400); // CD
    hundreds.add('D', 500)->add('C', 600)->add('C', 700)->add('C', 800); // D, DC, DCC and DCCC
    hundreds.get('C')->add('M', 900); // CM


    RootNode tens;
    tens.add('X', 10)->add('X', 20)->add('X', 30); // X, XX, XXX
    tens.get('X')->add('L', 40); // XL
    tens.add('L', 50)->add('X', 60)->add('X', 70)->add('X', 80); // L, LX, LXX, LXXX
    tens.get('X')->add('C', 90); // XC

    RootNode ones;
    ones.add('I', 1)->add('I', 2)->add('I', 3)->add('I', 4); // I, II, III and IIII( alternate representation of 4)
    ones.get('I')->add('V', 4); // IV - normal representation of 4
    ones.add('V', 5)->add('I', 6)->add('I', 7)->add('I', 8); // V, VI, VII, VIII
    ones.get('I')->add('X', 9); // IX

    // extract thousands
    int val1000s = thousands.getValue(roman_str);
    if (val1000s == -1) {
        return -1;
    }
    // extract 100s
    int val100s = hundreds.getValue(roman_str);
    if (val100s == -1) {
        return -1;
    }
    // extract 10s
    int val10s = tens.getValue(roman_str);
    if (val10s == -1) {
        return -1;
    }
    // extract 1s
    int val1s = ones.getValue(roman_str);
    if (val1s == -1) {
        return -1;
    }

    if (!roman_str.empty()) {
        // string has extraneous characters
        return -1;
    }

    // sum up the 4 values
    return val1000s + val100s + val10s + val1s;
}


