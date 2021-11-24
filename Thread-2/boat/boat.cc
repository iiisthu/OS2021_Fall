#include <thread>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include "boat.h"

namespace proj2{
	
Boat::Boat(){
    bool boatInO;
    int num_children_O;
    int num_adults_O;
    int num_children_M;
    int num_adults_M;
    std::condition_variable children_condition_O;
    std::condition_variable children_condition_M;
    std::condition_variable adults_condition_O;
    std::condition_variable adults_condition_M;
    bool gameover;
    bool is_pilot;
    bool is_adult_go;
}
void Boat:: begin(int a, int b, BoatGrader *bg){
    num_children_O = b;
    num_adults_O = a;
    num_children_M = 0;
    num_adults_M = 0;
    boatInO = true;
    std::mutex mtx;
    gameover = false;
    is_pilot = true;
    is_adult_go = false;
    std::thread threads[a+b];
    for (int i = 0; i < b; ++i){
        threads[i] = std::thread(&Boat::child_itinerary, this, std::ref(bg));
    }
    for (int i = 0; i < a; ++i){
        threads[i+b] = std::thread(&Boat::adult_itinerary, this, std::ref(bg));
    }
    for (int i = 0; i < a+b; ++i){
        threads[i].join();
    }
    return;
}
void Boat:: adult_itinerary(BoatGrader *bg){
    bg->initializeAdult();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::this_thread::yield();
    std::unique_lock<std::mutex> lck(mtx);
    while(!(is_adult_go && boatInO)){
        adults_condition_O.wait(lck);
        if(gameover) return;
    }
    bg->AdultRowToMolokai();
    num_adults_M++;
    num_adults_O--;
    boatInO = false;
    is_adult_go = false;
    children_condition_M.notify_one();
    adults_condition_M.wait(lck);
    if(gameover) return;
}
void Boat:: child_itinerary(BoatGrader *bg){
    bg->initializeChild();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::this_thread::yield();
    std::unique_lock<std::mutex> lck(mtx);
    while(!gameover){
        if(boatInO){
            if(is_adult_go){
                adults_condition_O.notify_one();
                children_condition_O.wait(lck);
                if(gameover) return;
            }
            if(is_pilot){
                bg->ChildRowToMolokai();
                num_children_O--;
                num_children_M++;
                is_pilot = false;
                children_condition_O.notify_one();
                children_condition_M.wait(lck);
                if(gameover) return;
            }else{
                bg->ChildRideToMolokai();
                boatInO = false;
                num_children_O--;
                num_children_M++;
                is_pilot = true;
                if(num_adults_O==0 && num_children_O==0){
                    gameover = true;
                }
                if(gameover){
                    std::cout<<"Success!"<<std::endl;
                    children_condition_M.notify_all();
                    adults_condition_M.notify_all();
                    return;
                }
                if(num_adults_O!=0 && num_children_O==0){
                    is_adult_go = true;
                }
                children_condition_M.notify_one();
                children_condition_M.wait(lck);
                if(gameover) return;
            }
        }else{
            bg->ChildRowToOahu();
            boatInO = true;
            num_children_O++;
            num_children_M--;
            if(is_adult_go){
                adults_condition_O.notify_one();
            }else{
                children_condition_O.notify_one();
            }
            children_condition_O.wait(lck);
            if(gameover) return;
        }
    }
}
}