#include<string>

#include "boatGrader.h" 

namespace proj2 {
	BoatGrader::BoatGrader(int i, int j){
		boatAssert(j >=2, "invalid children num", CONDITION_MISMATCH);
    	childrenInit = j;
    	adultInit=i;
        children_on_oahu = j;
        adults_on_oahu = i;
        children_on_molokai = 0;
        adults_on_molokai = 0;
        passenger_spaces = 1;
        passenger_to_oahu = 1;
        boat_on_oahu = true;
        error_occured = false;
    }
    void BoatGrader:: initializeChild(){
		printf("A child has been created.\n");
	}
	
	//NEW ADDITION FOR 2014
	void BoatGrader:: initializeAdult(){
		printf("An adult has been created.\n");
	}

    /* ChildRowToMolokai should be called when a child pilots the boat
       from Oahu to Molokai */
    void BoatGrader:: ChildRowToMolokai() {
        boatAssert(children_on_oahu > 0 && boat_on_oahu && childrenInit > 0, "wrong Child rowing to Molokai.\n", CONDITION_MISMATCH);
        children_on_oahu--;
        children_on_molokai++;
        passenger_spaces++;
        boat_on_oahu = false;
		printf("**Child rowing to Molokai.\n");
    }

    /* ChildRowToOahu should be called when a child pilots the boat
       from Molokai to Oahu*/
    void BoatGrader:: ChildRowToOahu() {
    	boatAssert(children_on_molokai > 0 && !boat_on_oahu && childrenInit > 0, "wrong Child rowing to Oahu.\n", CONDITION_MISMATCH);
        children_on_molokai--;
        children_on_oahu++;
        passenger_to_oahu++;
        boat_on_oahu = true;
		printf("**Child rowing to Oahu.\n");
    }

    /* ChildRideToMolokai should be called when a child not piloting
       the boat disembarks on Molokai */
    void BoatGrader:: ChildRideToMolokai() {
    	boatAssert(children_on_oahu > 0 && passenger_spaces > 0 && childrenInit > 0, "wrong Child arrived on Molokai as a passenger.\n", CONDITION_MISMATCH);
        children_on_oahu--;
        children_on_molokai++;
        passenger_spaces--;
		printf("**Child arrived on Molokai as a passenger.\n");
    }

    /* ChildRideToOahu should be called when a child not piloting
       the boat disembarks on Oahu */
    void BoatGrader:: ChildRideToOahu() {
    	boatAssert(children_on_molokai > 0 && passenger_to_oahu > 0 && childrenInit > 0, "wrong Child arrived on Oahu as a passenger.\n", CONDITION_MISMATCH);
        children_on_molokai--;
        children_on_oahu++;
        passenger_to_oahu--;
		printf("**Child arrived on Oahu as a passenger.\n");
    }

    /* AdultRowToMolokai should be called when a adult pilots the boat
       from Oahu to Molokai */
    void BoatGrader:: AdultRowToMolokai() {
    	boatAssert(adults_on_oahu > 0 && boat_on_oahu && adultInit > 0, "wrong Adult rowing to Molokai.\n", CONDITION_MISMATCH);
        adults_on_oahu--;
        adults_on_molokai++;
        boat_on_oahu = false;
		printf("**Adult rowing to Molokai.\n");
    }

    /* AdultRowToOahu should be called when a adult pilots the boat
       from Molokai to Oahu */
    void BoatGrader:: AdultRowToOahu() {
    	boatAssert(adults_on_molokai > 0 && !boat_on_oahu && adultInit > 0, "wrong Adult rowing to Oahu.\n", CONDITION_MISMATCH);
        adults_on_oahu++;
        adults_on_molokai--;
        boat_on_oahu = true;
		printf("**Adult rowing to Oahu.\n");
    }

    /* AdultRideToMolokai should be called when an adult not piloting
       the boat disembarks on Molokai */
    void BoatGrader:: AdultRideToMolokai() {
    	boatAssert(false, "adult can not ride as passenger", ADULT_RIDE);
        error_occured = true;
		printf("**Adult arrived on Molokai as a passenger.\n");
    }

    /* AdultRideToOahu should be called when an adult not piloting
       the boat disembarks on Oahu */
    void BoatGrader:: AdultRideToOahu() {
    	boatAssert(false, "adult can not ride as passenger", ADULT_RIDE);
        error_occured = true;
		printf("**Adult arrived on Oahu as a passenger.\n");
    }
    

    int BoatGrader::adultsLeft() {
        return adults_on_oahu;
    }

    int BoatGrader::childrenLeft() {
        return children_on_oahu;
    }

    bool BoatGrader:: passed() {
        return children_on_oahu == 0 && adults_on_oahu == 0;
    }

    int BoatGrader::points() {
        if(error_occured)
            return 0;
        return children_on_oahu != 0 || adults_on_oahu != 0 ? 1 : 2;
    }
}
