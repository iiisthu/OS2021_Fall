#include<stdio.h>
#include<string>

#include "boat.h"
#include "boatGrader.h"

int main(int argc, char *argv[]){
	if (argc < 3){
        printf("\nUsage %s [adult num] [children num] \n", argv[0]);
        exit(1);
    }
    int adults = atoi(argv[1]);
    int children = atoi(argv[2]);
	proj2::BoatGrader* bg = new proj2::BoatGrader(adults,children); 
	proj2::Boat* boat = new proj2::Boat();
	boat->begin(adults,children, bg);
	int k = bg->childrenLeft();
	bg->boatAssert(k == 0, "Left children on oahu", proj2::WRONG_ANSWER);
	int l = bg->adultsLeft();
	bg->boatAssert(l == 0, "Left adults on oahu", proj2::WRONG_ANSWER);
	printf("pass the test!\n");
	delete bg;
	delete boat;
	return 0;
}

