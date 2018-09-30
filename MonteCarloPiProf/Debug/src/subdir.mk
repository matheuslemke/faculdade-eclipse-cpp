################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MonteCarloPiProf.cpp 

OBJS += \
./src/MonteCarloPiProf.o 

CPP_DEPS += \
./src/MonteCarloPiProf.d 


# Each subdirectory must supply rules for building sources it contributes
src/MonteCarloPiProf.o: ../src/MonteCarloPiProf.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/MonteCarloPiProf.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


