################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/application/app_IOT_AT/Src/app_IOT_AT.c 

OBJS += \
./Libraries/application/app_IOT_AT/Src/app_IOT_AT.o 

C_DEPS += \
./Libraries/application/app_IOT_AT/Src/app_IOT_AT.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/application/app_IOT_AT/Src/%.o Libraries/application/app_IOT_AT/Src/%.su Libraries/application/app_IOT_AT/Src/%.cyclo: ../Libraries/application/app_IOT_AT/Src/%.c Libraries/application/app_IOT_AT/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"P:/IOT Workspace/Sample_BL_project/Libraries/EEPROM/Inc" -I"P:/IOT Workspace/Sample_BL_project/Libraries/application/app_eeprom/Inc" -I"P:/IOT Workspace/Sample_BL_project/Libraries/application/app_IOT_AT/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-application-2f-app_IOT_AT-2f-Src

clean-Libraries-2f-application-2f-app_IOT_AT-2f-Src:
	-$(RM) ./Libraries/application/app_IOT_AT/Src/app_IOT_AT.cyclo ./Libraries/application/app_IOT_AT/Src/app_IOT_AT.d ./Libraries/application/app_IOT_AT/Src/app_IOT_AT.o ./Libraries/application/app_IOT_AT/Src/app_IOT_AT.su

.PHONY: clean-Libraries-2f-application-2f-app_IOT_AT-2f-Src

