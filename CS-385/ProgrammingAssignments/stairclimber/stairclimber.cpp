/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Himanshu Rana(hrana2)
 * Date        : 10/3/18
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;



vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

	vector<vector<int>> result;
	vector<vector<int>> num_ways;

	vector<int> way;

	if(num_stairs < 1) {
		num_ways.push_back(way);
	}
	else {
		for(int i = 1; i <= 3; i++) {
			if(num_stairs >= i) {
				result = get_ways(num_stairs - i); // decrementing the amount of steps taken
				for(unsigned int j = 0; j < result.size(); j++) {
					result[j].push_back(i);
					num_ways.push_back(result[j]);
				}
			}
		}
	}

	return num_ways;



}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

	int x;
	unsigned int max_spaces;
	for(unsigned int i = 0; i < ways.size(); i++) { // getting maximum space for labels from the highest label
		x = ways.size();
		max_spaces = 1;
		while(x >= 10) {
			max_spaces++;
			x /= 10;
		}

		cout << setw(max_spaces) << i + 1 << ". " << "["; // setting the max width and making all the labels right aligned

		for(unsigned int j = ways[i].size() - 1; j >= 1; j--) {
			cout << ways[i][j] << ", "; // printing out all of the combinations
		}
		cout << ways[i][0] << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
	istringstream iss;
	int limit;

	if(argc != 2) {
		cout << "Usage: " << argv[0] << " <number of stairs>" << endl; // making sure that there is an input and the right amount
		return 1;
	}

	iss.str(argv[1]);
	if(!(iss >> limit) || limit < 1) { // making sure that the input is a positive number
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	vector<vector<int>> ways = get_ways(limit);

	if(limit == 1) { // if there is only one stair then there is only one way to climb it
		cout << "1 way to climb 1 stair." << endl;
	}
	else {
		cout << ways.size() << " ways to climb " << limit << " stairs." << endl;
	}

	display_ways(ways);
	return 0;

}
