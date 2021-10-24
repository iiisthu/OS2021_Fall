#ifndef BOAT_GRADER_H_
#define BOAT_GRADER_H_

#include<stdio.h>
#include <iostream>


namespace proj2 {
	
enum BOAT_ERROR {
    CONDITION_MISMATCH = 0,
    ADULT_RIDE = 1,
    WRONG_ANSWER = 2
};	

class BoatGrader {

    /**
     * BoatGrader consists of functions to be called to show that
     * your solution is properly synchronized. This version simply
     * prints messages to standard out, so that you can watch it.
     * You cannot submit this file, as we will be using our own
     * version of it during grading.

     * Note that this file includes all possible variants of how
     * someone can get from one island to another. Inclusion in
     * this class does not imply that any of the indicated actions
     * are a good idea or even allowed.
     */
public:
     
    template <class T>
	inline void boatAssert(bool condition, char const *msg, T error) {
	    if (!condition) {
	        std::cerr << msg << std::endl;
	        error_occured = true;
	        throw error;
	    }
	}
	
	BoatGrader(int i, int j);
   ~BoatGrader(){};
	
	void initializeChild();
	
	void initializeAdult();

    /* ChildRowToMolokai should be called when a child pilots the boat
       from Oahu to Molokai */
    void ChildRowToMolokai() ;

    /* ChildRowToOahu should be called when a child pilots the boat
       from Molokai to Oahu*/
    void ChildRowToOahu();

    /* ChildRideToMolokai should be called when a child not piloting
       the boat disembarks on Molokai */
    void ChildRideToMolokai() ;

    /* ChildRideToOahu should be called when a child not piloting
       the boat disembarks on Oahu */
    void ChildRideToOahu() ;

    /* AdultRowToMolokai should be called when a adult pilots the boat
       from Oahu to Molokai */
    void AdultRowToMolokai() ;

    /* AdultRowToOahu should be called when a adult pilots the boat
       from Molokai to Oahu */
    void AdultRowToOahu() ;

    /* AdultRideToMolokai should be called when an adult not piloting
       the boat disembarks on Molokai */
    void AdultRideToMolokai() ;

    /* AdultRideToOahu should be called when an adult not piloting
       the boat disembarks on Oahu */
    void AdultRideToOahu() ;
    
    int adultsLeft();
    
    int childrenLeft();
    
    bool passed();
    
    int points();
    
private:
	int childrenInit;
	int adultInit;
    int children_on_oahu;
    int adults_on_oahu;
    int children_on_molokai;
    int adults_on_molokai;
    int passenger_spaces;
    int passenger_to_oahu;
    bool boat_on_oahu;
    bool error_occured;
    
    
};

}
#endif // BOAT_GRADER_H_
