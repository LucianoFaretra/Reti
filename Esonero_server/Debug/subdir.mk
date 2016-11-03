################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../connection.c \
../initializeEnvironment.c \
../main.c \
../sendReceive.c 

OBJS += \
./connection.o \
./initializeEnvironment.o \
./main.o \
./sendReceive.o 

C_DEPS += \
./connection.d \
./initializeEnvironment.d \
./main.d \
./sendReceive.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


