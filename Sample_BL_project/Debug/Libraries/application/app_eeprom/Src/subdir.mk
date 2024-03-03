################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/application/app_eeprom/Src/app_eeprom.c 

OBJS += \
./Libraries/application/app_eeprom/Src/app_eeprom.o 

C_DEPS += \
./Libraries/application/app_eeprom/Src/app_eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/application/app_eeprom/Src/%.o Libraries/application/app_eeprom/Src/%.su Libraries/application/app_eeprom/Src/%.cyclo: ../Libraries/application/app_eeprom/Src/%.c Libraries/application/app_eeprom/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"P:/IOT Workspace/Sample_BL_project/Libraries/EEPROM/Inc" -I"P:/IOT Workspace/Sample_BL_project/Libraries/application/app_eeprom/Inc" -I"P:/IOT Workspace/Sample_BL_project/Libraries/application/app_IOT_AT/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-application-2f-app_eeprom-2f-Src

clean-Libraries-2f-application-2f-app_eeprom-2f-Src:
	-$(RM) ./Libraries/application/app_eeprom/Src/app_eeprom.cyclo ./Libraries/application/app_eeprom/Src/app_eeprom.d ./Libraries/application/app_eeprom/Src/app_eeprom.o ./Libraries/application/app_eeprom/Src/app_eeprom.su

.PHONY: clean-Libraries-2f-application-2f-app_eeprom-2f-Src

