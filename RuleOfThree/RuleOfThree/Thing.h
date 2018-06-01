#pragma once
#include <Windows.h>
#include <iostream>
#include <typeinfo>
using namespace std;
static const char BASE_LABEL = 'a';

class Thing {
public:

	// Constructor:
	Thing(int size);

	// Copy constructor:
	Thing(const Thing& other);

	// Copy assignment overload:
	Thing& operator=(const Thing& other);

	// Destructor:
	~Thing();

	// Handy overload of [] for accessing internal array:
	int& operator[](int i);

	// Output:
	void print() const;
	friend std::ostream& operator<<(std::ostream&, const Thing&);

private:
	int size;          // size of array
	int* data;         // array of data
	char label;        // "name" of object
	static int count;  // current object count
	void fill() const; // fill array with values for testing

};