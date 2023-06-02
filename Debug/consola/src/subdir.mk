################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../consola/src/main.c 

C_DEPS += \
./consola/src/main.d 

OBJS += \
./consola/src/main.o 


# Each subdirectory must supply rules for building sources it contributes
consola/src/%.o: ../consola/src/%.c consola/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-consola-2f-src

clean-consola-2f-src:
	-$(RM) ./consola/src/main.d ./consola/src/main.o

.PHONY: clean-consola-2f-src

