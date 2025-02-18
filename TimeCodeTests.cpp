
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	assert(tc.ToString() == "0:0:0");
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	assert(tc3.ToString() == "5:14:21");

	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	//rollover values
	TimeCode tc1 = TimeCode(7, 61, 61);
	tc1.GetComponents(h,m,s);

	
	cout << "PASSED!" << endl << endl;
}

void TestAdd(){
	cout << "Testing Add" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 + tc2;
	assert(tc3.ToString() == "1:50:0");
	
	//add nothing
	TimeCode tc4 = TimeCode(0,0,0);
	TimeCode tc5 = tc1 + tc4;
	assert(tc5.ToString() == "1:0:0");

	cout << "PASSED!" << endl << endl;
}

void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	//attempting to subract a larger number from a smaller number
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
	}

	//subracting 0
	TimeCode tc6 = TimeCode(0,0,0);
	TimeCode tc7 = tc1 - tc6;
	assert(tc7.ToString() == "1:0:0");
	
	cout << "PASSED!" << endl << endl;
}

void TestMultiply(){
	cout << "Testing Multiply" << endl;

	//testing whole number
	TimeCode tc = TimeCode(2, 2, 2);
	double a = 2;
	TimeCode tc1 = tc * a;
	assert(tc1.ToString() == "4:4:4");

	//testing 
	double b = 1.5;
	TimeCode tc2 = tc * b;
	assert(tc2.ToString() == "3:3:3");

	//testing multiplication by 0 < a < 1
	double c = .5;
	TimeCode tc3 = tc * c;
	assert(tc3.ToString() == "1:1:1");

	// testing multiplication by -1 (should be invalid)
	try {
		double d = -1;
		TimeCode tc4 = tc * d;
		assert(false);
	} catch (const invalid_argument &e){
	}
	 
	//testing multiplication by 0
	double d = 0;
	TimeCode tc4 = tc * d;
	assert(tc4.ToString() == "0:0:0");

	cout << "PASSED" << endl << endl;
}

void TestDivide(){
	cout << "Testing Divide" << endl;
	//random safe division a > 1
	TimeCode tc = TimeCode(2, 2, 2);
	double a = 2;
	TimeCode tc1 = tc / a;
	assert(tc1.ToString() == "1:1:1");

	//random safe division 0 < a < 1
	double b = .5;
	TimeCode tc2 = tc / b;
	assert(tc2.ToString() == "4:4:4");

	//attempting to divide by 0
	double c = 0;
	try{
		TimeCode tc3 = tc / c;
		assert(false);
	} catch (const invalid_argument&e){
	}

	cout << "PASSED!" << endl << endl;
}

void TestEquality(){
	//testing equal
	TimeCode tc1 = TimeCode(5,5,5);
	TimeCode tc2 = TimeCode(5,5,5);
	assert(tc1 == tc2);

	//testing unequal
	TimeCode tc3 = TimeCode(1,1,1);
	assert(tc1 != tc3);
	
}

void TestGreater(){
	cout << "Testing Greater" << endl;
	
	//testing one thats greater
    TimeCode tc1 = TimeCode(5, 5, 5);  
    TimeCode tc2 = TimeCode(4, 59, 59); 
    assert(tc1 > tc2);  
    
    //testing one thats not greater
    TimeCode tc3 = TimeCode(3, 0, 0);  
    assert(!(tc3 > tc1)); 
    
    cout << "PASSED!" << endl << endl;
}

void TestLess(){
	cout << "Testing Less" << endl;
		
	//testing one thats less
	TimeCode tc1 = TimeCode(5, 5, 5);  
	TimeCode tc2 = TimeCode(3, 0, 0);  
	assert(tc2 < tc1); 
	
	//testing one thats greater 
	TimeCode tc3 = TimeCode(4, 59, 59); 
	assert(!(tc1 < tc3));  
		
	cout << "PASSED!" << endl << endl;
}

void TestSetHours(){
	cout << "Testing SetHours" << endl;

	//test valid change 
	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetHours(15); 
	assert(tc.ToString() == "15:5:9");

	//test invalid change
	try {
		tc.SetHours(-1);
	} catch (const invalid_argument&e){
	}

	cout << "PASSED!" << endl << endl;
}

void TestSetMinutes()
{
	cout << "Testing SetMinutes" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
	}

	try {
		tc.SetMinutes(-1);
		assert(false);
	} catch (const invalid_argument &e){

	}

	cout << "PASSED!" << endl << endl;
}

void TestSetSeconds(){
	cout << "Testing SetSeconds" << endl;

	TimeCode tc = TimeCode(8, 5, 9);

	// test valid change
	tc.SetSeconds(15); 
	cout << tc.ToString() << endl;
	assert(tc.ToString() == "8:5:15");

	// test invalid change
	try
	{
		tc.SetSeconds(80);  
		assert(false);
	}
	catch (const invalid_argument &e)
	{}

	try {
		tc.SetSeconds(-1);
		assert(false);
	} catch(const invalid_argument &e){
	}

	cout << "PASSED!" << endl << endl;
}

void TestGetHours(){
	cout << "Testing GetHours" << endl;
	TimeCode tc = TimeCode(1,2,43);
	unsigned int hour = tc.GetHours();
	assert(hour == 1);

	cout << "PASSED!" << endl << endl;
}

void TestGetMins(){
	cout << "Testing GetMins" << endl;

	TimeCode tc = TimeCode(1,2,3);
	unsigned int min = tc.GetMinutes();
	assert(min == 2);

	cout << "Passed! " << endl << endl;
}

void TestGetSecs(){
	cout << "Testing GetSeconds" << endl;

	TimeCode tc = TimeCode(1,2,3);
	unsigned int sec = tc.GetSeconds();
	assert(sec == 3);

	cout << "PASSED!" << endl;
}
	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestSetHours();
	TestSetMinutes();
	TestSetSeconds();
	TestSubtract();
	TestMultiply();
	TestDivide();
	TestEquality();
	TestGreater();
	TestLess();
	TestGetHours();
	TestGetMins();
	TestGetSecs();
	TestAdd();


	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
