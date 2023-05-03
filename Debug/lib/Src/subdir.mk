################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/Src/LCD_I2C.c 

OBJS += \
./lib/Src/LCD_I2C.o 

C_DEPS += \
./lib/Src/LCD_I2C.d 


# Each subdirectory must supply rules for building sources it contributes
lib/Src/%.o lib/Src/%.su lib/Src/%.cyclo: ../lib/Src/%.c lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/CODE/STM/STM_F4_LCD_I2C/lib/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-Src

clean-lib-2f-Src:
	-$(RM) ./lib/Src/LCD_I2C.cyclo ./lib/Src/LCD_I2C.d ./lib/Src/LCD_I2C.o ./lib/Src/LCD_I2C.su

.PHONY: clean-lib-2f-Src

