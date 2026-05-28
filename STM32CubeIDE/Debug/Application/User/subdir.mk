################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/arrLED.c \
../Application/User/button.c \
../Application/User/elevator_ctrl.c \
../Application/User/fnd.c \
C:/kdigital/ARM_cortexm4/project_elevater/Src/gpio.c \
../Application/User/led.c \
C:/kdigital/ARM_cortexm4/project_elevater/Src/main.c \
../Application/User/servo.c \
../Application/User/stepper.c \
C:/kdigital/ARM_cortexm4/project_elevater/Src/stm32f4xx_hal_msp.c \
C:/kdigital/ARM_cortexm4/project_elevater/Src/stm32f4xx_it.c \
../Application/User/syscalls.c \
../Application/User/sysmem.c \
C:/kdigital/ARM_cortexm4/project_elevater/Src/tim.c \
C:/kdigital/ARM_cortexm4/project_elevater/Src/usart.c 

OBJS += \
./Application/User/arrLED.o \
./Application/User/button.o \
./Application/User/elevator_ctrl.o \
./Application/User/fnd.o \
./Application/User/gpio.o \
./Application/User/led.o \
./Application/User/main.o \
./Application/User/servo.o \
./Application/User/stepper.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_it.o \
./Application/User/syscalls.o \
./Application/User/sysmem.o \
./Application/User/tim.o \
./Application/User/usart.o 

C_DEPS += \
./Application/User/arrLED.d \
./Application/User/button.d \
./Application/User/elevator_ctrl.d \
./Application/User/fnd.d \
./Application/User/gpio.d \
./Application/User/led.d \
./Application/User/main.d \
./Application/User/servo.d \
./Application/User/stepper.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_it.d \
./Application/User/syscalls.d \
./Application/User/sysmem.d \
./Application/User/tim.d \
./Application/User/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/%.o Application/User/%.su Application/User/%.cyclo: ../Application/User/%.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE" -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE/Application/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/gpio.o: C:/kdigital/ARM_cortexm4/project_elevater/Src/gpio.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE" -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE/Application/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/main.o: C:/kdigital/ARM_cortexm4/project_elevater/Src/main.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE" -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE/Application/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32f4xx_hal_msp.o: C:/kdigital/ARM_cortexm4/project_elevater/Src/stm32f4xx_hal_msp.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE" -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE/Application/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32f4xx_it.o: C:/kdigital/ARM_cortexm4/project_elevater/Src/stm32f4xx_it.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE" -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE/Application/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/tim.o: C:/kdigital/ARM_cortexm4/project_elevater/Src/tim.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE" -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE/Application/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/usart.o: C:/kdigital/ARM_cortexm4/project_elevater/Src/usart.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE" -I"C:/kdigital/ARM_cortexm4/project_elevater/STM32CubeIDE/Application/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User

clean-Application-2f-User:
	-$(RM) ./Application/User/arrLED.cyclo ./Application/User/arrLED.d ./Application/User/arrLED.o ./Application/User/arrLED.su ./Application/User/button.cyclo ./Application/User/button.d ./Application/User/button.o ./Application/User/button.su ./Application/User/elevator_ctrl.cyclo ./Application/User/elevator_ctrl.d ./Application/User/elevator_ctrl.o ./Application/User/elevator_ctrl.su ./Application/User/fnd.cyclo ./Application/User/fnd.d ./Application/User/fnd.o ./Application/User/fnd.su ./Application/User/gpio.cyclo ./Application/User/gpio.d ./Application/User/gpio.o ./Application/User/gpio.su ./Application/User/led.cyclo ./Application/User/led.d ./Application/User/led.o ./Application/User/led.su ./Application/User/main.cyclo ./Application/User/main.d ./Application/User/main.o ./Application/User/main.su ./Application/User/servo.cyclo ./Application/User/servo.d ./Application/User/servo.o ./Application/User/servo.su ./Application/User/stepper.cyclo ./Application/User/stepper.d ./Application/User/stepper.o ./Application/User/stepper.su ./Application/User/stm32f4xx_hal_msp.cyclo ./Application/User/stm32f4xx_hal_msp.d ./Application/User/stm32f4xx_hal_msp.o ./Application/User/stm32f4xx_hal_msp.su ./Application/User/stm32f4xx_it.cyclo ./Application/User/stm32f4xx_it.d ./Application/User/stm32f4xx_it.o ./Application/User/stm32f4xx_it.su ./Application/User/syscalls.cyclo ./Application/User/syscalls.d ./Application/User/syscalls.o ./Application/User/syscalls.su ./Application/User/sysmem.cyclo ./Application/User/sysmem.d ./Application/User/sysmem.o ./Application/User/sysmem.su ./Application/User/tim.cyclo ./Application/User/tim.d ./Application/User/tim.o ./Application/User/tim.su ./Application/User/usart.cyclo ./Application/User/usart.d ./Application/User/usart.o ./Application/User/usart.su

.PHONY: clean-Application-2f-User

