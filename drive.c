/*
 * drive.c
 *
 *  Created on: May 31, 2017
 *      Author: stpalmer
 */

#include <khepera/khepera.h>
#include <signal.h>

#define RotSpeedL 120
#define RotSpeedR 120

static knet_dev_t* dsPic;

int left, right;


int main(int argc, char *argv[]){
	left = RotSpeedL;	//set the left wheel speed (encoder ticks)
	right = RotSpeedR; 	//set the right wheel speed (encoder ticks)

	int accinc = 10;	//acceleration increment
	int accdiv = 0;		//acceleration divider
	int minspacc = 20;	//minimum speed acceleration
	int minspdec = 1;	//minimum speed deceleration
	int maxsp = 400;	//maximum speed


	int kh4RegIdle = 0;
	int kh4RegSpeedProfile = 2;

	//kb_set_debug_level(2);
	printf("libKhepera Template Program\n\n");

	printf("Entering the rest of the code\n\n");
	//initiate libkhepera and robot access
	if (kh4_init(argc ,argv)!=0){
		printf("\nERROR: could not initiate the libkhepera!\n\n");
		return -1;
	}

	//open robot socket and store the handle in their respective pointers
	dsPic = knet_open("Khepera4:dsPic",KNET_BUS_I2C,0,NULL);

	if(dsPic == NULL){
		printf("\nERROR: could not initiate communication with Kh4 dspic\n\n:");
		return -2;
	}

	printf("\nSet speed profile \n\n");
	kh4_SetSpeedProfile(accinc, accdiv, minspacc, minspdec, maxsp, dsPic);

	printf("\nSet new mode\n\n");
	kh4_SetMode(kh4RegSpeedProfile,dsPic);

	printf("\nStart driving forward\n\n");
	kh4_set_speed(left,right,dsPic); //drive forward
}

