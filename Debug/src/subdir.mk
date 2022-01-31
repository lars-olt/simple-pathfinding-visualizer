################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AStarAlgorithm.cpp \
../src/DijkstraAlgorithm.cpp \
../src/Node.cpp \
../src/NodeGrid.cpp \
../src/Pathfinding\ Visualiser.cpp \
../src/Screen.cpp 

CPP_DEPS += \
./src/AStarAlgorithm.d \
./src/DijkstraAlgorithm.d \
./src/Node.d \
./src/NodeGrid.d \
./src/Pathfinding\ Visualiser.d \
./src/Screen.d 

OBJS += \
./src/AStarAlgorithm.o \
./src/DijkstraAlgorithm.o \
./src/Node.o \
./src/NodeGrid.o \
./src/Pathfinding\ Visualiser.o \
./src/Screen.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Pathfinding\ Visualiser.o: ../src/Pathfinding\ Visualiser.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Pathfinding Visualiser.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/AStarAlgorithm.d ./src/AStarAlgorithm.o ./src/DijkstraAlgorithm.d ./src/DijkstraAlgorithm.o ./src/Node.d ./src/Node.o ./src/NodeGrid.d ./src/NodeGrid.o ./src/Pathfinding\ Visualiser.d ./src/Pathfinding\ Visualiser.o ./src/Screen.d ./src/Screen.o

.PHONY: clean-src

