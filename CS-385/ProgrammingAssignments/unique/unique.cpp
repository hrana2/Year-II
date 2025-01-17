/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Himanshu Rana - hrana2
 * Date        : 9/24/18
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

	for(unsigned int i = 0; i < s.size(); i++) {
		if((s[i] < 96) || (s[i] > 123)) { // checks to see if the letter is not lowercase by using the ASCII values for lowercase 'a' and 'z'
			cout << "Error: String must contain only lowercase letters." << endl;
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

	unsigned int check_value = 0;

	for(unsigned int i = 0; i < s.size(); i++) {
		if((check_value & (1 << (s[i] - 'a'))) > 0) { // comparing the bitvector and the setter to check if the letter has been found already
			cout << "Duplicate letters found." << endl;
			return false;
		}

		check_value = check_value | (1 << (s[i] - 'a')); // letter has not been found so we "or" the bitvector and setter and set it equal to the setter
	}

	cout << "All letters are unique." << endl;
	return true;

}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

	if(argc != 2) {
		cout << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}

	if(!is_all_lowercase(argv[1])) {
		return 1;
	}

	all_unique_letters(argv[1]);
	return 0;
}
