################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ABXClient.cpp \
../src/ABX_Client_Application.cpp \
../src/ConfigReader.cpp 

CPP_DEPS += \
./src/ABXClient.d \
./src/ABX_Client_Application.d \
./src/ConfigReader.d 

OBJS += \
./src/ABXClient.o \
./src/ABX_Client_Application.o \
./src/ConfigReader.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I"/Users/pritam/cpp-workspace/ABX_Client_Application/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/ABXClient.d ./src/ABXClient.o ./src/ABX_Client_Application.d ./src/ABX_Client_Application.o ./src/ConfigReader.d ./src/ConfigReader.o

.PHONY: clean-src

