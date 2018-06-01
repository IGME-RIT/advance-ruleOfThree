#include "Thing.h"

Thing::Thing(int n) : size(n)
{
	label = static_cast<char>(BASE_LABEL + count++);
	cout << "Basic Constructing..." << (*this) << " via " << __FUNCTION__ << endl;
	data = new int[n];
	fill();
}

Thing::Thing(Thing const& other)
{
	label = static_cast<char>(BASE_LABEL + count++);
	cout << "Copy Constructing...." << (*this) << " via " << __FUNCTION__ << endl;
	size = other.size;
	
	// cout << "Testing data in copy constr: " << data[0] << endl; // won't work because data not set yet in current object!
	
	data = new int[other.size];      // why do we need this?
	for (int i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

Thing& Thing::operator=(Thing const& other) {
	cout << "Copying.............." << (*this) << " via " << __FUNCTION__ << endl;

	if (this != &other) // ensure we're not wasting time with self-assignment
	{
		size = other.size;
		data = new int[other.size];		// if use original data, we'd "link" the two objects and their arrays
		for (int i = 0; i < size; i++)	// deep copy:
		{
			data[i] = other.data[i];	// need to copy each array element
		}
	}

	return *this;						// allow for external calls, like a=b=c=...
}

Thing::~Thing() {
	cout << "Destroying............" << (*this) << " via " << __FUNCTION__ << endl;
	if (*data)
	{
		delete[] data;	// need to manage internally allocated memory
	}
	else
	{
		data = nullptr;
	}
}

int& Thing::operator[](int i)
{
	return data[i];
}

void Thing::print() const {
	cout << "[";

	for (int i = 0; i < size; i++)
	{
		cout << data[i];
		if (i + 1 < size) cout << ',';
	}

	cout << "]" << endl;
}

void Thing::fill() const
{
	for (int i = 0; i < size; i++)
	{
		data[i] = i;
	}
}

ostream& operator<<(ostream& out, const Thing& t)
{
	return out << typeid(t).name() << " " << t.label;  // https://msdn.microsoft.com/en-us/library/fyf39xec.aspx
}

int Thing::count = 0;