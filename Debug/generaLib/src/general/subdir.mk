################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../generaLib/src/general/generalLib.c 

C_DEPS += \
./generaLib/src/general/generalLib.d 

OBJS += \
./generaLib/src/general/generalLib.o 


# Each subdirectory must supply rules for building sources it contributes
generaLib/src/general/%.o: ../generaLib/src/general/%.c generaLib/src/general/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-generaLib-2f-src-2f-general

clean-generaLib-2f-src-2f-general:
	-$(RM) ./generaLib/src/general/generalLib.d ./generaLib/src/general/generalLib.o

.PHONY: clean-generaLib-2f-src-2f-general

