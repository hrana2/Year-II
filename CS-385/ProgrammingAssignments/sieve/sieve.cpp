/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Himanshu Rana - hrana2
 * Date        : 9/17/18
 * Description : Sieve of Eratosthenes
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
	//This function is the constructor which calls the sieve function
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
        for(int i = 0; i < limit_ + 1; i++) {
        	is_prime_[i] = true;
        }
    	sieve();
    	cout << endl << "Number of primes found: " << count_num_primes() << endl;
    }

    //deconstructor - deletes and allocates new memory space
    ~PrimesSieve() {
        delete [] is_prime_;
    }

    //a hint to the complier to not try to use this as a method
    inline int num_primes() const {
        return num_primes_;
    }

    //This function formats the output in a desired way in which the maximum number of
    //primes allowed on a single line is 80 divided by the number of digits of the highest prime number
    //It also sets the width by checking if the counter is less than the number of primes allowed per row
    //Else go to the next line and reset counter back to 1
    void display_primes() const {
        // TODO: write code to display the primes in the format specified in the
        // requirements document.
    	const int max_prime_width = num_digits(max_prime_),
    			  primes_per_row = 80 / (max_prime_width +1);
    	int counter = 0;
    	int row = 0;
    	for(int i = 2; i <= limit_; i++) {
    		if(is_prime_[i]) {
    			if(max_prime_width == 2) {
    				counter++;
    				if(counter < num_primes_) {
    					cout << i << " ";
    				}
    				else {
    					cout << i;
    				}
    			}
    			else if(counter == 0) {
    				cout << setw(max_prime_width) << i;
    				counter++;
    			}
    			else if(counter < primes_per_row)  {
    				cout << setw(max_prime_width + 1) << i;
    				counter++;
    			}
    			else {
    				cout << endl  << setw(max_prime_width) << i;
    				counter = 1;
    				row++;
    			}
    		}
    	}

    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    //This function counts the number of primes found within the limit
    int count_num_primes() const {
        // TODO: write code to count the number of primes found
    	int counter = 0;
    	for(int i = 2; i <= limit_; i++) {
    		if(is_prime_[i]) {
    			counter++;
    		}
    	}
    	return counter;

    }

    //This function counts the digits within an integer
    int num_digits(int num) const {
        // TODO: write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
    	int counter = 0;
    	while(num >= 1) {
    		num = num / 10;
    		counter++;
    	}
    	return counter;
    }


    //The sieve function first sets all the values within is_prime_ to true
    //Then it checks to see if the i-value is a prime and if it is then
    //It iterates over the array and changes all the true to false if the j-value is of i squared
    //This function also calculates the maximum prime within the array
    //
    void sieve() {
        // TODO: write sieve algorithm
    	for(int i = 2; i <= limit_; ++i) {
    		is_prime_[i] = true;
    	}

    	for(int i = 2; i < sqrt(limit_); i++) {
    		if(is_prime_[i]) {
    			for(int j = (i * i); j <= limit_; j += i) {
    				is_prime_[j] = false;
    			}
    		}
    	}

    	num_primes_ = count_num_primes();
    	max_prime_ = 0;
    	int x = limit_;
    	while(max_prime_ == 0) {
    		if(is_prime_[x] == true) {
    			max_prime_ = x;
    		}
    		else {
    			--x;
    		}
    	}

    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;


    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve x(limit);
    //cout << endl;
    cout << "Primes up to " << limit << ":" << endl;
    x.display_primes();
    return 0;
}
