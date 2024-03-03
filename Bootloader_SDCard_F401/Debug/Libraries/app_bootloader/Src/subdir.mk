################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/app_bootloader/Src/app_bootloader.c 

OBJS += \
./Libraries/app_bootloader/Src/app_bootloader.o 

C_DEPS += \
./Libraries/app_bootloader/Src/app_bootloader.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/app_bootloader/Src/%.o Libraries/app_bootloader/Src/%.su Libraries/app_bootloader/Src/%.cyclo: ../Libraries/app_bootloader/Src/%.c Libraries/app_bootloader/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I"P:/IOT Workspace/Bootloader_SDCard_F401/Libraries/app_bootloader/Inc" -I"P:/IOT Workspace/Bootloader_SDCard_F401/Libraries/EEPROM/Inc" -I../Core/Inc -I"P:/IOT Workspace/Bootloader_SDCard_F401/Libraries/SDCard/Inc" -I../FATFS/Target -I../FATFS/App -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-app_bootloader-2f-Src

clean-Libraries-2f-app_bootloader-2f-Src:
	-$(RM) ./Libraries/app_bootloader/Src/app_bootloader.cyclo ./Libraries/app_bootloader/Src/app_bootloader.d ./Libraries/app_bootloader/Src/app_bootloader.o ./Libraries/app_bootloader/Src/app_bootloader.su

.PHONY: clean-Libraries-2f-app_bootloader-2f-Src

