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

	kh4_set_speed(left,right,dsPic);
}

