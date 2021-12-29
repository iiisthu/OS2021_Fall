#ifndef BOAT_H_
#define BOAT_H_

#include<stdio.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

#include "boatGrader.h"

namespace proj2{
class Boat{
public:
	Boat();
    ~Boat(){};
	bool boatInO;
    int num_children_O;
    int num_adults_O;
    int num_children_M;
    int num_adults_M;
	std::mutex mtx;
    std::condition_variable children_condition_O;
    std::condition_variable children_condition_M;
	std::condition_variable adults_condition_O;
	std::condition_variable adults_condition_M;
    bool gameover;
    bool is_adult_go;
	bool is_pilot;
	void begin(int, int, BoatGrader*);
	void adult_itinerary(BoatGrader*);
	void child_itinerary(BoatGrader*);
};
//void adult_itinerary(Boat *boat, BoatGrader *bg);
//void child_itinerary(Boat *boat, BoatGrader *bg);
}

#endif // BOAT_H_
