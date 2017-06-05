################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../receive.c 

OBJS += \
./receive.o 

C_DEPS += \
./receive.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-poky-linux-gnueabi-gcc -I/opt/poky/1.8/sysroots/cortexa8hf-vfp-neon-poky-linux-gnueabi/usr/include -O0 -g3 -Wall -c -march=armv7-a -mfloat-abi=hard -mfpu=neon -mtune=cortex-a8 --sysroot=/opt/poky/1.8/sysroots/cortexa8hf-vfp-neon-poky-linux-gnueabi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


