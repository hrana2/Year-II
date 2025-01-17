/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Himanshu Rana - hrana2
 * Version     : 1.0
 * Date        : 11/4/18
 * Description : Counts the number of inversions in an array.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

//Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);



/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
//By using two for loops the time complexity is satisfied
//This is the slower version because the function is comparing each element with those after it
long count_inversions_slow(int array[], int length) {
    // TODO
	long counter = 0;
	for(int i = 0; i < length - 1; ++i) {
		for(int j = i + 1; j < length; ++j) {
			if(array[i] > array[j]) {
				counter++;
			}
		}
	}
	return counter;

}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
//This function is the faster version because it uses mergesort to not compare all the elements with each other
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!

	int *scratch = new int[length];
	long counter = mergesort(array, scratch, 0, length - 1);
	delete[] scratch;
	return counter;

}


static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO

	long count = 0;
	int mid;
	if(low < high) {
		mid = ((low + high) / 2);
		count = mergesort(array, scratch, low, mid);
		count += mergesort(array, scratch, mid + 1, high);

		//sets new midpoint and low values of array
		int newLow = low;
		int newMid = mid + 1;

		for(int i = low; i <= high; i++) {
			if(newLow <= mid && (newMid > high || array[newLow] <= array[newMid])) {
				scratch[i] = array[newLow];
				newLow++;
			}
			else {
				scratch[i] = array[newMid];
				newMid = newMid + 1;
				count = count + ((mid - newLow) + 1);
			}
		}

		for(int j = low; j <= high; ++j) {
			array[j] = scratch[j];
		}


	}
	return count;
}


int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

	if(argc > 2) {
		cout << "Usage: " << argv[0] << " [slow]" << endl;
		return 1;
	}
	else if((argc == 2) && strcmp("slow", argv[1]) != 0) {
		cout << "Error: Unrecognized option \'" << argv[1] << "\'." << endl;
		return 1;
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output

    //checks to see if no values were inputed
    if(values.size() == 0) {
    	cout << "Error: Sequence of integers not received." << endl;
    	return 1;
    }

    if(argc == 2) {
    	cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    }
    else {
    	cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }


    return 0;
}
