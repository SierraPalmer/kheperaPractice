/*
 * drive.c
 *
 *  Created on: May 31, 2017
 *      Author: stpalmer
 */

#include <khepera/khepera.h>
#include <signal.h>

static knet_dev_t* dsPic;

int left, right;


int main(int argc, char *argv[]){
	left = 10;	//set the left wheel speed (encoder ticks)
	right = 10; 	//set the right wheel speed (encoder ticks)

	kb_set_debug_level(2);
	printf("libKhepera Template Program\r\n");

	//initiate libkhepera and robot access
	if (kh4_init(argc ,argv)!=0){
		printf("\nERROR: could not initiate the libkhepera!\n\n");
		return -1;
	}

	//open robot socket and store teh handle in their respective pointers
	dsPic = knet_open("Khepera4:dsPic",KNET_BUS_I2C,0,NULL);

	if(dsPic == NULL){
		printf("\nERROR: could not initiate communication with Kh4 dspic\n\n:");
		return -2;
	}
	kh4_set_speed(left,right,dsPic);
}

