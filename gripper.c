/*
 * gripper.c
 *
 *  Created on: Jun 13, 2017
 *      Author: sierrapalmer
 */

#include <khepera/khepera.h>

static int quitReq = 0;

static knet_dev_t * Arm;
static knet_dev_t * Gripper;

int initGripper(){
	kgripper_init();
	Arm = knet_open("Kgripper:Arm", KNET_BUS_I2C, 0, NULL);
	Gripper = knet_open("Kgripper:Gripper", KNET_BUS_I2C,0,NULL);

	if(Arm!=0){
		if(Gripper!=0){
			return 0;
		}else{
			return -1;
		}
	}

	return -2;

}

int quit(int argc, char *argv[], void * data){
	quitReq = 1;
	return 0;
}

int movearm(int argc, char *argv[], void * data){

	printf("Move Arm gripper to position %4u\n", atoi(argv[1]));
	kgripper_Arm_Set_Order(Arm, atoi(argv[1]));
	return 0;
}



void main_but_not_really(int argc, char *argv[]){
//void main_but_not_really(int argc, char *argv[]){
	int maxGTorque = 300;		//maximum gripper torque
	int maxAPosition = 300;		//arm in high position
	int minAPosition = 900;		//arm on the ground

	int Grip_Lim = kgripper_Gripper_Get_Limits(Gripper);

	kgripper_Gripper_Set_Torque(Gripper, maxGTorque);

	kgripper_Arm_Set_Order(Arm,maxAPosition);

	kgripper_Gripper_Set_Order(Gripper, Grip_Lim - 20); //open gripper

	usleep(10000);

	kgripper_Gripper_Set_Order(Gripper, 0); //close gripper

	usleep(10000);

	kgripper_Arm_Set_Order(Arm, minAPosition);

	kgripper_Gripper_Set_Order(Gripper, Grip_Lim -20);

	usleep (10000);

	kgripper_Gripper_Set_Order(Gripper, 0);

	printf("Khepera is finished \n");

}

