################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/EEPROM/Src/ee24.c 

OBJS += \
./Libraries/EEPROM/Src/ee24.o 

C_DEPS += \
./Libraries/EEPROM/Src/ee24.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/EEPROM/Src/%.o Libraries/EEPROM/Src/%.su Libraries/EEPROM/Src/%.cyclo: ../Libraries/EEPROM/Src/%.c Libraries/EEPROM/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"P:/IOT Workspace/Sample_BL_project/Libraries/EEPROM/Inc" -I"P:/IOT Workspace/Sample_BL_project/Libraries/application/app_eeprom/Inc" -I"P:/IOT Workspace/Sample_BL_project/Libraries/application/app_IOT_AT/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-EEPROM-2f-Src

clean-Libraries-2f-EEPROM-2f-Src:
	-$(RM) ./Libraries/EEPROM/Src/ee24.cyclo ./Libraries/EEPROM/Src/ee24.d ./Libraries/EEPROM/Src/ee24.o ./Libraries/EEPROM/Src/ee24.su

.PHONY: clean-Libraries-2f-EEPROM-2f-Src

