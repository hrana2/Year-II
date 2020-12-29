/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Authors     : Himanshu Rana(hrana2) and Jessica Valenzuela(jvalenzu)
 * Date        : 10/19/18
 * Description : Uses breadth first search to find the best possible solution to the waterjug puzzle
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana and Jessica Valenzuela
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;


int capA;
int capB;
int capC;
int goalState[2];
bool is_success = 0;
string output;

class State {
private:
	vector<string> directions;
	int JugA;
	int JugB;
	int JugC;

public:
	State(int a, int b, int c, vector<string> adjacent);
	vector<string> get_Edges();
	void displayVector();
	int get_A();
	int get_B();
	int get_C();

};

State::State(int a, int b, int c, vector<string> adjacent) {
	JugA = a;
	JugB = b;
	JugC = c;
	directions = adjacent;

}

vector<string> State::get_Edges() {
	return directions;
}

int State::get_A() {
	return JugA;
}

int State::get_B() {
	return JugB;
}

int State::get_C() {
	return JugC;
}

//Displays a vector of each edge for all the states
void State::displayVector() {
	for(unsigned int x = 0; x < directions.size(); ++x) {
		cout << directions[x] << endl;
	}
}

//Checks to see if the goal that has been set is reached
bool ReachedGoal(int x, int y) {
	if((x == goalState[0]) && (y == goalState[1])) {
		return true;
	}
	else {
		return false;
	}
}

//Makes the edges for vector
vector<string> make_edges(int a, int b, int c) {
	vector<string> edges;
	stringstream iss;
	iss << "Initial state. (" << a << ", " << b << ", " << c << ")";
	edges.push_back(iss.str());
	return edges;
}

//Creates the string in the correct format
string StringBuilder(int x, int y, int z) {
	string a;
	stringstream iss;
	iss << "(" << x << ", " << y << ", " << z << ")";
	a = iss.str();
	return a;
}

//This is the queue that will be used during the breadth first search
queue<State> pouring;

//This function finds the optimal way to get to the end goal. It uses
//breadth first search in order to do that. It checks several different paths
//and then chooses the best one.
void Pouring(int JugA, int JugB, int JugC) {
	//Check if combination has already been done
	bool**checked = new bool * [capA + 1];
	for(int i = 0; i < capA + 1; ++i) {
		checked[i] = new bool[capB + 1];
		fill(checked[i], checked[i] + capB + 1, false);
	}

	State states(JugA, JugB, JugC, make_edges(JugA, JugB, JugC));
	pouring.push(states);

	while(!pouring.empty()) {
		JugA = pouring.front().get_A();
		JugB = pouring.front().get_B();
		JugC = pouring.front().get_C();

		checked[JugA][JugB] = true;

		if(ReachedGoal(JugA, JugB)) {
			pouring.front().displayVector();
			is_success = 1;
			break;
		}
		State head = pouring.front();
		pouring.pop();

		//Pouring C to A
		if(JugA < capA) {
			int newA = JugA + JugC;
			int newB = JugB;
			if(newA > capA) {
				newA = capA;
			}
			int newC = JugC - (newA - JugA);
			if(newB > capB) {
				newB = capB;
			}
			stringstream iss;
			if((newA - JugA) > 1) {
				iss << newA - JugA;
				output = "Pour " +  iss.str() + " gallons from C to A. ";
			}
			else {
				iss << newA - JugA;
				output = "Pour " + iss.str() + " gallon from C to A. ";
			}
			if(!checked[newA][newB]) {
				vector<string> solution = head.get_Edges();
				solution.push_back(output + StringBuilder(newA, newB, newC));
				State CtoA(newA, newB, newC, solution);
				pouring.push(CtoA);
			}

		}

		//Pouring B to A
		if(JugA < capA) {
			if(JugB != 0) {

				int newA = JugA + JugB;
				int newC = JugC;


				if(newA > capA) {
					newA = capA;
				}
				int newB = JugB - (newA - JugA);
				if(newB < 0) {
					newB = 0;
				}
				if(newB > capB) {
					newB = capB;
				}
				stringstream iss;
				if((JugB - newB) > 1) {
					iss << JugB - newB;
					output = "Pour " + iss.str() + " gallons from B to A. ";
				}
				else {
					iss << JugB - newB;
					output = "Pour " + iss.str() + " gallon from B to A. ";
				}
				if(!checked[newA][newB]) {
					vector<string> solution = head.get_Edges();
					solution.push_back(output + StringBuilder(newA, newB, newC));
					State BtoA(newA, newB, newC, solution);
					pouring.push(BtoA);
				}
			}

		}

		//Pouring from C to B
		if(JugB < capB) {

			int newA = JugA;
			int newB = JugB + JugC;


			if(newB > capB) {
				newB = capB;
			}

			int newC = JugC - (newB - JugB);
			if(newA > capA) {
				newA = capA;
			}

			stringstream iss;
			if((newB - JugB) > 1) {
				iss << newB - JugB;
				output = "Pour " + iss.str() + " gallons from C to B. ";
			}
			else {
				iss << newB - JugB;
				output = "Pour " + iss.str() + " gallon from to C to B. ";
			}

			if(!checked[newA][newB]) {
				vector<string> solution = head.get_Edges();
				solution.push_back(output + StringBuilder(newA, newB, newC));
				State CtoB(newA, newB, newC, solution);
				pouring.push(CtoB);
			}
		}

		//Pouring from A to B
		if(JugB < capB) {
			if(JugA != 0) {
				int newC = JugC;
				int newA;
				int newB = JugA + JugB;


				if(newB > capB) {
					newB = capB;
					newA = JugA - (newB - JugB);
				}
				else {
					newA = 0;
				}
				if(newA < 0) {
					newA = 0;
				}
				if(newA > capA) {
					newA = capA;
				}
				stringstream iss;
				if((newB - JugB) > 1) {
					iss << newB - JugB;
					output = "Pour " + iss.str() + " gallons from A to B. ";
				}
				else {
					iss << newB - JugB;
					output = "Pour " + iss.str() + " gallon from A to B. ";
				}

				if(!checked[newA][newB]) {
					vector<string> solution = head.get_Edges();
					solution.push_back(output + StringBuilder(newA, newB, newC));
				    State AtoB(newA, newB, newC, solution);
					pouring.push(AtoB);
				}
			}
		}


		//Pouring from B to C
		if(JugA + JugB < capC) {
			if(JugB != 0) {
				int newC = JugC + JugB;
				if(newC > capC) {
					newC = capC;
				}


				int newB = JugC - newC;
				int newA = JugA;

				if(newB > capB) {
					newB = capB;
				}
				if(newB < 0) {
					newB = 0;
				}
				if(newA > capA) {
					newA = capA;
				}

				stringstream iss;
				if((JugB - newB) > 1) {
					iss << JugB - newB;
					output = "Pour " + iss.str() + " gallons from B to C. ";
				}
				else {
					iss << JugB - newB;
					output = "Pour " + iss.str() + " gallon from B to C. ";
				}

				if(!checked[newA][newB]) {
					vector<string> solution = head.get_Edges();
					solution.push_back(output + StringBuilder(newA, newB, newC));
					State BtoC(newA, newB, newC, solution);
					pouring.push(BtoC);
				}

			}
		}

		//Pouring from A to C
		if(JugA + JugB < capC) {
			if(JugA != 0) {
				int newC = JugA + JugC;
				if(newC > capC) {
					newC = capC;
				}
				int newA = JugA - (newC - JugC);
				if(newA > capA) {
					newA = capA;
				}
				if(newA < 0) {
					newA = 0;
				}

				int newB = JugB;
				stringstream iss;
				if((JugA - newA) > 1) {
					iss << JugA - newA;
					output = "Pour " + iss.str() + " gallons from A to C. ";
				}
				else {
					iss << JugA - newA;
					output = "Pour " + iss.str() + " gallon from A to C. ";
				}

				if(!checked[newA][JugB]) {
					vector<string> solution = head.get_Edges();
					solution.push_back(output + StringBuilder(newA, newB, newC));
					State AtoC(newA, newB, newC, solution);
				    pouring.push(AtoC);
				}
			}
		}
	}
	//If no path has been found then No solution will be printed.
	if(!is_success) {
		cout <<  "No solution." << endl;
	}

	//Clears the checked array.
	for(int i = 0; i <= capA; ++i) {
		delete [] checked[i];
	}

	delete [] checked;

}


//This is the main function where all the error checking is done.
int main(int argc, char * const argv[]) {
	if(argc!=7){
		cout<<"Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" <<endl;
		return 0;
	}
	//Checks to see if the correct capacity has been set and if the goal for each jug is correct.
	for(int i = 1; i<=6; i++){
		istringstream iss(argv[i]);
		int number;
		if(!(iss >> number) || number < 0 || (i == 3 && number == 0)) {
			if(i<=3){
				if(i==1){
					cout<<"Error: Invalid capacity '" << argv[i] <<"' for jug A."<<endl;
					return 0;

				}
				if(i==2){
					cout<<"Error: Invalid capacity '" << argv[i] <<"' for jug B."<<endl;
					return 0;

				}
				if(i==3){
					cout<<"Error: Invalid capacity '" << argv[i] <<"' for jug C."<<endl;
					return 0;

				}
			}
			else{
				if(i==4){
					cout<<"Error: Invalid goal '" << argv[i] <<"' for jug A."<<endl;
					return 0;

				}

				if(i==5){
					cout<<"Error: Invalid goal '" << argv[i] <<"' for jug B."<<endl;
					return 0;

				}
				if(i==6){
					cout<<"Error: Invalid goal '" << argv[i] <<"' for jug C."<<endl;
					return 0;
				}
			}
		}
	}



	//This for loop checks to see if each of the goal does not go over the capacity.
	for(int x = 1, y = 4; x <=3 && y <= 6; x++, y++) {
		int temp_x, temp_y;
		stringstream iss_i(argv[x]);
		iss_i >> temp_x;
		istringstream iss_j(argv[y]);
		iss_j >> temp_y;

		if((temp_y > temp_x) && (x == 1)) {
			cout << "Error: Goal cannot exceed capacity of jug A." << endl;
			return 0;
		}

		if((temp_y > temp_x) && (x == 2)) {
			cout << "Error: Goal cannot exceed capacity of jug B." << endl;
			return 0;
		}

		if((temp_y > temp_x) && (x == 3)) {
			cout << "Error: Goal cannot exceed capacity of jug C." << endl;
			return 0;
		}
	}


	//This for loop checks to see if the total gallons exceed the capacity of Jug C.
	int sum_gallons;
	int max;
		sum_gallons = 0;
		istringstream iss(argv[3]);
		iss >> max;
		for (int i = 4; i <= 6; ++i) {
			int temp;
			istringstream it(argv[i]);
			it >> temp;
			sum_gallons = sum_gallons + temp;
		}
		if (sum_gallons != max) {
			cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
			return 0;
		}

		for(int i = 4; i <= 6; ++i) {
			istringstream iss(argv[i]);
			int temp;
			iss >> temp;
			goalState[i - 4] = temp;
		}


		istringstream iss1(argv[1]);
		int temp;
		iss1 >> temp;
		capA = temp;
		istringstream iss2(argv[2]);
		iss2 >> temp;
		capB = temp;
		istringstream iss3(argv[3]);
		iss3 >> temp;
		capC = temp;

		Pouring(0, 0, capC);
}
