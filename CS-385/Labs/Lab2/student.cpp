/*
 * student.cpp
 *
 *  Created on: Sep 7, 2018
 *      Author: himanshu_rana99
 *
 *      hrana2
 *      "I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana
 */

//by the time the constructor completes all member variables must be initialized
//the order in which the variables are initialized then you have to name it in the same way


#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

class Student {

public:
	Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} { }

	string full_name() const {
		return first_ + " " + last_;
	}

	float gpa() const {
		return gpa_;
	}
	 int id() const {
		return id_;
	 }

	 void print_info() const {
		 cout << fixed << full_name() << ", GPA: " << setprecision(2) << gpa() << ", ID: " << id() << endl;
	 }

private:
	string first_, last_;
	float gpa_;
	int id_;


};


vector<Student> find_failing_students(const vector<Student> &students) {
	vector<Student> failing_students;
	 // Iterates through the students vector, appending each student whose gpa is
	 // less than 1.0 to the failing_students vector.
	for(auto it = students.cbegin(); it != students.cend(); ++it) {
		if(it->gpa() < 1.0) {
			failing_students.push_back(*it);
		}

	}
	return failing_students;


}

void print_students(const vector<Student> &students) {
	// Iterates through the students vector, calling print_info() for each student.
	for(auto it = students.cbegin(); it != students.cend(); ++it) {
		it->print_info();
	}

}



int main() {
	string first_name, last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;

	do {
		cout << "Enter student's first name: ";
		cin >> first_name;
		cout << "Enter student's last name: ";
		cin >> last_name;
		gpa = -1;

		while(gpa < 0 || gpa > 4) {
			cout << "Enter student's GPA (0.0-4.0): ";
			cin >> gpa;
		}

		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout << "Add another student to database (Y/N)? ";
		cin >> repeat;

	} while (repeat == 'Y' || repeat == 'y');


	cout << endl << "All students:" << endl;
	print_students(students);

	cout << endl << "Failing students:";
	 // TODO
	 // Print a space and the word 'None' on the same line if no students are failing.
	 // Otherwise, print each failing student on a separate line.
	vector<Student> failing_students = find_failing_students(students);
	if(failing_students.empty()) {
		cout << " None";
	} else {
		cout << endl;
		print_students(failing_students);
	}

	return 0;
}


