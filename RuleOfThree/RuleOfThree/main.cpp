// BIG-THREE
// summary and reminders from previous examples 
// see http://www.learncpp.com/cpp-tutorial/915-shallow-vs-deep-copying/
//
// Copy constructors copy non-static values of one object to another object
//   * resembles cloning
//   * creates one object from another object, using same data values
//   * does SHALLOW copy by default
//   * you can customize, usually to do a deep copy
//
// Copy-assignment overload (=operator):
//   * lets you copy values to existing object via assignment
//   * is using stack-allocated objects, not an alias--copies data members between objects
//   * does shallow copy unless you define it to do otherwise (usually, a deep copy)
//   * standard pattern: usually check to see if input object is 'this', and return *this to allow a=b=c...
//   * when using dynamically allocated objects (pointers), p=q will create an alias (p gets address of q's pointee--doesn't call =op!)

// memory testing: 
// https://www.youtube.com/watch?v=HUZW8m_3XvE
// https://blogs.msdn.microsoft.com/vcblog/2014/06/04/native-memory-diagnostic-tools-for-visual-studio-14-ctp/
// https://blogs.msdn.microsoft.com/visualstudioalm/2014/11/13/memory-usage-tool-while-debugging-in-visual-studio-2015/

#include "Thing.h"
#include <conio.h>

int main() {

	cout << "\n-------------------------------------------------" << endl;
	cout << "Basic stack construction: " << endl;
	cout << "-------------------------------------------------" << endl;
	
	Thing a(10);
	a.print();

	cout << "\n-------------------------------------------------" << endl;
	cout << "Basic heap construction: " << endl;
	cout << "-------------------------------------------------" << endl;
	
	Thing* b = new Thing(10);
	b->print();

	cout << "\n-------------------------------------------------" << endl;
	cout << "Stack Big Three: " << endl;
	cout << "-------------------------------------------------" << endl;
	
	Thing c(5);
	
	for (int i = 0; i < 5; i++)
	{
		c[i] *= 10;
	}
	
	Thing d(5);
	d = c;
	d.print();
	
	for (int i = 0; i < 5; i++)
	{ 
		c[i] += 1;
	}
	
	c.print();
	d.print();
	
	Thing e(d);
	e.print();
	
	for (int i = 0; i < 5; i++)
	{
		d[i] *= 2;
	}
	
	c.print();
	d.print();
	e.print();

	cout << "\n-------------------------------------------------" << endl;
	cout << "Heap Big Three: " << endl;
	cout << "-------------------------------------------------" << endl;

	cout << "Attempting to call BigThree, but we're only getting aliases:" << endl;
	Thing* f = new Thing(4);
	Thing* f1 = f;
	Thing* f2(f);  // see https://social.msdn.microsoft.com/Forums/vstudio/en-US/39beafe7-c867-470c-9aae-8ba91e50b814/is-there-a-default-copy-constructor-for-pointer-objects?forum=vcgeneral               
	f->print();
	f1->print();
	f2->print();

	cout << "\nTry to change f, but no good:" << endl;
	for (int i = 0; i < 5; i++)
	{
		(*f)[i] *= 10;
	}

	f->print();
	f1->print();
	f2->print();

	cout << "\nUse pointers to call BigThree and do deep copies/clones:" << endl;
	Thing* g = new Thing(4);
	Thing* h = new Thing(*g);
	g->print();
	h->print();

	cout << "\nChanging h doesn't affect g:" << endl;
	for (int index = 0; index < 4; index++)
	{
		(*h)[index] *= 10;
	}
	g->print();
	h->print();

	cout << "\nDo deep copy via assignment now:" << endl;
	*g = *h;
	g->print();
	h->print();

	cout << "\nChanging h doesn't affect g:" << endl;
	for (int index = 0; index < 4; index++)
	{
		(*h)[index] *= 10;
	}
	g->print();
	h->print();

	cout << "\n-------------------------------------------------" << endl;
	cout << "\nIt's clobbering time!" << endl;
	cout << "-------------------------------------------------" << endl;
	delete b;
	f1 = nullptr;
	f2 = nullptr;
	delete f;      // causes crash if we don't check if data actually exists (the issue is f1 and f2 removing data when we attempted to copy object) 
	delete g;
	delete h;

	_getch();
}