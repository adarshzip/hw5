#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool solve(
    const AvailabilityMatrix& avail, 
    size_t dailyNeed, 
    size_t maxShifts, 
    DailySchedule& sched, 
    std::vector<size_t>& shiftCounts, 
    size_t day,
    size_t slot
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    sched.resize(avail.size());    
    for(unsigned int i = 0; i < avail.size(); i++){
        sched[i].resize(dailyNeed);
    }
    std::vector<size_t> shiftCounts(avail[0].size());

    return solve(avail, dailyNeed, maxShifts, sched, shiftCounts, 0, 0);
}

bool solve(
    const AvailabilityMatrix& avail, 
    size_t dailyNeed, 
    size_t maxShifts, 
    DailySchedule& sched, 
    std::vector<size_t>& shiftCounts, 
    size_t day,
    size_t slot
)
{
    if (day == sched.size()){ // finished scheduling
        return true; 
    }
    else if (slot == dailyNeed){ // finished that day
        return solve(avail, dailyNeed, maxShifts, sched, shiftCounts, day + 1, 0);
    }
    else {
        unsigned int start; 
        if(slot == 0){
            start = 0;
        }
        else {
            start = sched[day][slot - 1] + 1;
        }
        for (unsigned int i = start; i < avail[day].size(); i++){
            if (avail[day][i] == 1 && shiftCounts[i] < maxShifts){
                sched[day][slot] = i; 
                shiftCounts[i] += 1; 
                if (solve(avail, dailyNeed, maxShifts, sched, shiftCounts, day, slot + 1)){
                    return true; 
                }
                else {
                    shiftCounts[i] -= 1; 
                }
            }
        }
    }

    return false; 
}
