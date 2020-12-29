CXX      = g++
CXX_FILE = $(wildcard *.cpp)
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE))
CXXFLAGS = -O2 -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0

all:
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe


#cxx = g++ is the name of the GNU complier 
# wildcard is going to look through all the files with the extension .cpp file and assign the name to cxx_file
#target will be the name of the file output without the .cpp 
#-g means to debug information 
#-wall means warn on all things 
#-Werror means turn all warnings into errors 
#-pedantic-error means to be more annoying about compilation errors 
#-fmessage-length sets the error line length to 0 
#the all statement translate g++ -g -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0 gcd.cpp -o gcd
#-o means output filename
#make clean cleans up the executible 
#make clean && make 
