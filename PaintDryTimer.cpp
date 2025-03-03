
#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;


struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};

long long int get_time_remaining(DryingSnapShot dss){
	time_t current = time(0);
    
    long long int timeElapsed = current - dss.startTime;

    //figure out each component so that we can make the total time it needs to dry into a timecode
    //in order to subract timeelapsed from it
    unsigned int dryingHours = dss.timeToDry->GetHours();
    unsigned int dryingMinutes = dss.timeToDry->GetMinutes();
    unsigned int dryingSeconds = dss.timeToDry->GetSeconds();
    unsigned long long int dryingTime = dss.timeToDry->ComponentsToSeconds(dryingHours, dryingMinutes, dryingSeconds);

    unsigned long long int remainingTime = dryingTime - timeElapsed;

    if (remainingTime < 0){
        remainingTime = 0;
    }

	return remainingTime;
}

//this should make the outputs match the example outputs
string drying_snap_shot_to_string(DryingSnapShot dss){
    TimeCode* dryTime = dss.timeToDry;
    TimeCode remainder = TimeCode(0,0, get_time_remaining(dss)); //time remaining is in seconds so we have to convert it to a timecode


    string output = dss.name + " (takes " + dryTime->ToString() + " to dry) time remaining: " + remainder.ToString();
    return output;
}


double get_sphere_sa(double rad){
    if (rad < 0) {
        throw invalid_argument("radius cannot be negative");
    }
	double surfaceArea = 4 * pow(rad, 2) * M_PI; //equation for sa of a sphere is 4(pi)(r^2)
	return surfaceArea;
}


//calculates the amount of time an object needs to dry
TimeCode *compute_time_code(double surfaceArea){
	TimeCode* timeToDry = new TimeCode(0, 0, surfaceArea); //it is the same as the surface area in cm
	return timeToDry;
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);

	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	
    //when time to dry is 0
    dss.timeToDry = new TimeCode(0, 0, 0);
    ans = get_time_remaining(dss);
    assert(ans == 0);  // Time remaining should be 0 when drying time is zero
    delete dss.timeToDry;

    // Testing drying_snap_shot_to_string
    DryingSnapShot dss2;
    dss2.startTime = time(0);  // Reset the start time
    dss2.timeToDry = new TimeCode(0, 10, 5);  // 10 minutes and 5 seconds
    dss2.name = "Batch_Test";
    string result = drying_snap_shot_to_string(dss2);
    assert(result == "Batch_Test(takes 0:10:5 to dry) time remaining: 0:10:5");  // Check the formatting
    delete dss2.timeToDry;

	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	
    //sphere radius is 0
    double sa2 = get_sphere_sa(0);
    assert(sa2 == 0);

	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// Get time remaining, should be close to 5 minutes if tested immediately
    DryingSnapShot dss3;
    dss3.startTime = time(0);  
    dss3.timeToDry = new TimeCode(0, 5, 0);  
    long long int remainingTime = get_time_remaining(dss3);
    assert(remainingTime >= 0);  // Time should be positive when tested right after start time
    assert(remainingTime <= 300); // It should be less than or equal to 5 minutes

    delete dss3.timeToDry;

    //test for multiple dryingsnapshots
    vector<DryingSnapShot> dryingSnapShots;
    for (int i = 1; i <= 3; ++i) {
        DryingSnapShot dss;
        dss.name = "Batch_" + to_string(i);
        dss.startTime = time(0) - i * 10;  // Simulate different start times

        double radius = 5.0 * i;
        double sa = get_sphere_sa(radius);
        dss.timeToDry = compute_time_code(sa);
        
        dryingSnapShots.push_back(dss);
    }

    // for (int i = 0; i < dryingSnapShots.size(); ++i){
    //     cout << drying_snap_shot_to_string(dryingSnapShots[i]) << endl;
    // }
    
    assert(dryingSnapShots.size() == 3);  //make sure theres 3 (i was having an issue where it would just run infinitely)

	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	tests();
    // vector<DryingSnapShot> dryingSnapShots;
    // char userInput;
    
    // cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
    // cin >> userInput;

    // while(userInput != 'q' && userInput != 'Q'){
    //     if(userInput == 'A' || userInput == 'a'){
    //         DryingSnapShot dss;
    //         dss.name = "Batch_" + to_string(rand()); //give the batch a random name

    //         //compute time it needs to dry
    //         double radius;
    //         cout << "radius: ";
    //         cin >> radius; 
    //         double sa = get_sphere_sa(radius);
    //         TimeCode *tc = compute_time_code(sa);

    //         //add to vector so that it can be referenced in the future
    //         dryingSnapShots.push_back(dss);
    //         cout << drying_snap_shot_to_string(dss) << endl;

    //         //get a new input
    //         cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
    //         cin >> userInput;
    //     } else if (userInput == 'V' || userInput == 'v'){
    //         //check if it actually has anything in it first
    //         if (dryingSnapShots.empty()) {
    //             cout << "No drying snapshots available." << endl;
    //         } else { //output each dryingSnapShot
    //             for (int i = 0; i < dryingSnapShots.size(); ++i){
    //                 cout << drying_snap_shot_to_string(dryingSnapShots[i]);
    //             }
    //         }
    //     } else {
    //         cout << "Please choose a valid option: (A)dd, (V)iew Current Items, (Q)uit: ";
    //         cin >> userInput;
    //     }
    // }

    // for (int i = 0; i < dryingSnapShots.size(); ++i){
    //     delete dryingSnapShots[i].timeToDry;
    // }
    // dryingSnapShots.clear();

	return 0;
}