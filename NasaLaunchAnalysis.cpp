//I read the notes at the beginning of the assignment

//this file should read the file "Space_Corrected.csv" and output the average time of day 
//that launches occur.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>
#include "TimeCode.h"

using namespace std;

// takes a string and a single character (delimiter).
// Returns a vector containing the sub-strings between any / all occurrences of the delimiter
vector<string> split(const string& str, char delim) {
    vector<string> result;
    string temp;

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == delim) {
            if (!temp.empty()) {
                result.push_back(temp);  // Push the current substring into the result
                temp.clear();             // Clear the temporary string for the next substring
            }
        } else {
            temp += str[i];  // Append the current character to the temporary substring
        }
    }

    // If there's any remaining substring left after the loop, add it to the result
    if (!temp.empty()) {
        result.push_back(temp);
    }

    return result;
}

// takes a line from the file (a string). Returns the TimeCode object for the
// time embedded in that line. 
TimeCode parse_line(const string& line) {
    vector<string> columns = split(line, ',');
  
    //time is in the format HH:MM:SS or missing
    if (columns.size() > 5) {
        string time_str = columns[4]; // Time is in 5th column

        if (!time_str.empty()) {
            vector<string> time_parts = split(time_str, ' '); //use the spaces in the time column to find actual timecode
            string hourMin = time_parts[1];
            vector<string> hourAndMinute = split(hourMin, ':'); //makes a vector containing the hour and minute

            if (hourAndMinute.size() == 2) { //this will only work if there are 2 parts (the hour and minute)
                unsigned int hours = stoi(hourAndMinute[0]); // convert hour to unsigned int
                unsigned int minutes = stoi(hourAndMinute[1]); // convert minute to unsigned int
                return TimeCode(hours, minutes, 0);
            }
        }
    }
    // Return a dummy time if no valid time data is present
    return TimeCode(0, 0, 0);

}

int main() {
    
    ifstream launchFS;
    string launchTime;

    launchFS.open("Space_Corrected.csv");

    if (!launchFS.is_open()) {
      cout << "Could not open file Space_Corrected.csv" << endl;
      return 1;
    }

    //put all launchtimes in a vector
    vector<TimeCode> launchTimes;
    string line;
    
    //we need to skip the first line which only has the column titles, so we will call it now
    //for it to be skipped in the real loop
    getline(launchFS, line);

    // Read the file line by line and add them to the vector
    while (getline(launchFS, line)) {
        // Parse the line and extract the time
        TimeCode time = parse_line(line);
        if (time.GetHours() > 0 || time.GetMinutes() > 0 || time.GetSeconds() > 0) {
            launchTimes.push_back(time);  // Only add valid time values
        }
    }

    launchFS.close();

    //make a base timecode so that we can add all of them in order to compute the average
    TimeCode TotalTime(0, 0, 0);

    //add all times to average
    for(int i = 0; i < launchTimes.size(); ++i){
        TotalTime = TotalTime + launchTimes[i];
    }

    TimeCode averageTime = TotalTime / launchTimes.size();

    cout << launchTimes.size() << " DATA POINTS" << endl;
    cout << "AVERAGE: " << averageTime.ToString() << endl;

    return 1;
}


