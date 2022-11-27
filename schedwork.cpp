

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


bool solveHelper(int row, int col,const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int days, int workers );
bool isValid( int i, const size_t maxShifts, DailySchedule& sched, int row, int col );
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below

   int days = avail.size();
   int workers = avail[0].size();

  //initialize all cells of the sched matrix to a default value, INT8_MAX
   for(int j = 0; j < days; j++) {
       sched.push_back(vector<Worker_T>());
       for(int k = 0; k < (int) dailyNeed; k++) {
           sched[j].push_back(INT8_MAX);
       }
   }

   //start with the very first shift of the very first day
   return solveHelper(0,0, avail, dailyNeed, maxShifts, sched, days, workers);

}

bool solveHelper(int row, int col,const AvailabilityMatrix& avail, 
    const size_t dailyNeed, 
    const size_t maxShifts,
    DailySchedule& sched, int days, int workers ) {

    //reached the end of the sched matrix and so the sched is done
    if ( row == days ) {
        return true;
    }
    if (sched[row][col] == INT8_MAX) {
        for(int i = 0; i < workers; i++ ) {
          //check if worker has availability for that day
            if ( avail[row][i] == 1 ) {
                sched[row][col] = i;
                //check if the worker CAN be scheduled by calling isValid
                if ( isValid(i, maxShifts, sched, row, col)  ) {
                  //at the last column so move to the next row
                    if ( col == ((int)dailyNeed - 1) ) {
                        if (solveHelper( row + 1, 0, avail, dailyNeed, maxShifts, sched, days, workers ) == true) {
                            return true;
                        }
                    }
                    //move to the next column
                    else {
                        if (solveHelper( row, col + 1, avail, dailyNeed, maxShifts, sched, days, workers ) == true) {
                            return true;
                        }
                    }
                }

            }

        }
        //worker could not be scheduled so set the cell back to its default state to be looked at again  
        sched[row][col] = INT8_MAX;
    }
    else {
        if ( col == ( (int)dailyNeed - 1 ) ) {
            return solveHelper( row + 1, 0, avail, dailyNeed, maxShifts, sched, days, workers );

        }
        else {
            return solveHelper( row, col + 1, avail, dailyNeed, maxShifts, sched, days, workers );

        }
    }
    return false;
}

bool isValid( int i, const size_t maxShifts, DailySchedule& sched, int row, int col ) {
  //checking to see if that worker already has a shift scheduled for that day
    for ( int j = 0; j < sched[row].size(); j++ ) {
        if ( j == col ) {
            continue;
        }
        if ( sched[row][j] == i ) {
            return false;
        }

    }
    //checking to see how many shifts the worker has in total
    int count = 0;
    for(int j = 0; j < sched.size(); j++) {
       for(int k = 0; k < sched[row].size(); k++) {
           if( sched[j][k] == i) {
               count++;
           }
        }
   }
   if(count > (int) maxShifts) {
       return false;
   }
    return true; 
}


