#include <iostream>
#include <sstream>
using namespace std;

#include "TimeCode.h"

//initializes each variable hr, min, sec, and t
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){

    t = (hr * 3600) + (min * 60) + sec;

    //account for rollover when assigning
    min = min + (sec / 60);
    sec = sec % 60;
        

    hr = hr + (min / 60);
    min = min % 60;
    

}


//copy constructor so that we can modify a version of the time without losing the original
TimeCode::TimeCode(const TimeCode& tc){
    t = tc.t;
}

void TimeCode::SetHours(unsigned int hours){
    if (hours < 0){
        throw invalid_argument("time cannot be negative");
    }

    unsigned int min= GetMinutes();
    unsigned int sec = GetSeconds();

    t = (hours * 3600) + (min * 60) + sec;
}

void TimeCode::SetMinutes(unsigned int minutes){
    if (minutes > 59){
        throw invalid_argument("minutes must be less than 60");
    } else if (minutes < 0) {
        throw invalid_argument("time cannot be negative");
    } else {
        unsigned int hours = GetHours();
        unsigned int seconds = GetSeconds();

        t = (hours * 3600) + (minutes * 60) + seconds;
    }
}

void TimeCode::SetSeconds(unsigned int seconds){
    if (seconds > 59){
        throw invalid_argument("Seconds must be less than 60");
    } else if (seconds < 0){
        throw invalid_argument("time cannot be negative");
    } else {
        unsigned int hours = GetHours();
        unsigned int minutes = GetMinutes();

        t = (hours * 3600) + (minutes * 60) + seconds;
    }
}

void TimeCode::reset(){
    t = 0;
}

unsigned int TimeCode::GetHours() const{
    return t/3600;
}

unsigned int TimeCode::GetMinutes() const{
    return (t % 3600) / 60;
}

unsigned int TimeCode::GetSeconds() const{
    return t % 60;
}

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
    hr = GetHours();
    min = GetMinutes();
    sec = GetSeconds();
}

long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
    return hr * 3600 + min * 60 + sec;
}

string TimeCode::ToString() const{
    //convert to seconds first so that if input is in an incorrect format it can be 
    //outputted with the correct one
    unsigned int h = t / 3600;
    unsigned int m = (t % 3600) / 60;
    unsigned int s = t % 60;

    if (s < 10 && m < 10){ 
        return to_string(h) + ":0" + to_string(m) + ":0" + to_string(s);
    }
    if (s < 10){
        return to_string(h) + ":" + to_string(m) + ":0" + to_string(s);
    }
    if (m < 10){
        return to_string(h) + ":0" + to_string(m) + ":" + to_string(s);
    }
    return to_string(h) + ":" + to_string(m) + ":" + to_string(s);
    
}

TimeCode TimeCode::operator+(const TimeCode& other) const{
    //make new variable stand in for t so that we can add both t's together
    long long unsigned int totalSeconds = t + other.t; 

    //convert back to hr/min/sec format
    //we will use this method for add, subtract, multiply, and divide
    unsigned int h = totalSeconds / 3600;
    unsigned int m = (totalSeconds % 3600) / 60;
    unsigned int s = totalSeconds % 60;

    return TimeCode(h, m, s);
}

TimeCode TimeCode::operator-(const TimeCode& other) const{
    if (other.t > t){
        throw invalid_argument("Time Cannot be negative.");
    }else{
        long long unsigned int totalSeconds = t - other.t;
        unsigned int h = totalSeconds / 3600;
        unsigned int m = (totalSeconds % 3600) / 60;
        unsigned int s = totalSeconds % 60;
        return TimeCode(h, m, s);
    }
}

TimeCode TimeCode::operator*(double a) const{
    //cant multiply by negatives
    if (a < 0){
        throw invalid_argument("time cannot be negative");
    } else{
        //must static cast into long long unsigned int becasue a is a double in the parameter
        long long unsigned int totalSeconds = static_cast<long long unsigned int>(t * a);
        unsigned int h = totalSeconds / 3600;
        unsigned int m = (totalSeconds % 3600) / 60;
        unsigned int s = totalSeconds % 60;
        return TimeCode(h, m, s);
    }
}

TimeCode TimeCode::operator/(double a) const{
    //no dividing by zero!
    if (a == 0){
        throw invalid_argument("cannot divide by 0");
    } else if (a < 0){
        //or a negative number
        throw invalid_argument("time cannot be negative");
    } else {
        long long unsigned int totalSeconds = static_cast<long long unsigned int>(t / a);
        unsigned int h = totalSeconds / 3600;
        unsigned int m = (totalSeconds % 3600) / 60;
        unsigned int s = totalSeconds % 60;
        return TimeCode(h, m, s);
    }
}

bool TimeCode::operator == (const TimeCode& other) const{
    return t == other.t;
}

bool TimeCode::operator != (const TimeCode& other) const{
    return t != other.t;
}

bool TimeCode::operator < (const TimeCode& other) const{
    return t < other.t;
}

bool TimeCode::operator <= (const TimeCode& other) const{
    return t <= other.t;
}

bool TimeCode::operator > (const TimeCode& other) const{
    return t > other.t;
}

bool TimeCode::operator >= (const TimeCode& other) const{
    return t >= other.t;
}

