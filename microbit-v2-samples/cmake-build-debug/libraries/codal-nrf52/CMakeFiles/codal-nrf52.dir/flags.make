# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# compile ASM with /usr/bin/arm-none-eabi-gcc
# compile C with /usr/bin/arm-none-eabi-gcc
# compile CXX with /usr/bin/arm-none-eabi-g++
ASM_DEFINES = 

ASM_INCLUDES = -I/mnt/d/University/421/microbit-v2-samples/libraries -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/inc -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/inc/cmsis -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/mdk -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/templates -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/templates/nRF52833 -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/drivers/include -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/drivers/src -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/core -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/driver-models -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/drivers -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/streams -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/types

ASM_FLAGS =  -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -fno-exceptions -fno-unwind-tables --specs=nosys.specs -mcpu=cortex-m4 -mthumb -g   -DAPP_TIMER_V2 -DAPP_TIMER_V2_RTC1_ENABLED -DNRF_DFU_TRANSPORT_BLE=1 -DSOFTDEVICE_PRESENT -DNRF52833_XXAA -DNRF52833 -DTARGET_MCU_NRF52833 -DNRF5 -DNRF52833 -D__CORTEX_M4 -DS113 -DTOOLCHAIN_GCC -D__START=target_start

C_DEFINES = 

C_INCLUDES = -I/mnt/d/University/421/microbit-v2-samples/libraries -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/inc -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/inc/cmsis -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/mdk -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/templates -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/templates/nRF52833 -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/drivers/include -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/drivers/src -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/core -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/driver-models -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/drivers -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/streams -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/types

C_FLAGS =  -Wno-expansion-to-defined -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -fno-exceptions -fno-unwind-tables -ffunction-sections -fdata-sections -Wall -Wextra -Wno-unused-parameter -std=c99 --specs=nosys.specs -Warray-bounds -include "/mnt/d/University/421/microbit-v2-samples/build/codal_extra_definitions.h" -I"/mnt/d/University/421/microbit-v2-samples/utils/cmake/toolchains/ARM_GCC" -DNRFX_PRS_ENABLED=0 -g   -DAPP_TIMER_V2 -DAPP_TIMER_V2_RTC1_ENABLED -DNRF_DFU_TRANSPORT_BLE=1 -DSOFTDEVICE_PRESENT -DNRF52833_XXAA -DNRF52833 -DTARGET_MCU_NRF52833 -DNRF5 -DNRF52833 -D__CORTEX_M4 -DS113 -DTOOLCHAIN_GCC -D__START=target_start

CXX_DEFINES = 

CXX_INCLUDES = -I/mnt/d/University/421/microbit-v2-samples/libraries -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/inc -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/inc/cmsis -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/mdk -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/templates -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/templates/nRF52833 -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/drivers/include -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-nrf52/nrfx/drivers/src -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/core -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/driver-models -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/drivers -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/streams -I/mnt/d/University/421/microbit-v2-samples/libraries/codal-core/./inc/types

CXX_FLAGS =  -Wno-expansion-to-defined -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -fno-exceptions -fno-unwind-tables -ffunction-sections -fdata-sections -Wall -Wextra -Wno-unused-parameter -std=c++11 -fwrapv -fno-rtti -fno-threadsafe-statics -fno-exceptions -fno-unwind-tables -Wl,--gc-sections -Wl,--sort-common -Wl,--sort-section=alignment -Wno-array-bounds -include "/mnt/d/University/421/microbit-v2-samples/build/codal_extra_definitions.h" -I"/mnt/d/University/421/microbit-v2-samples/utils/cmake/toolchains/ARM_GCC" -g   -DAPP_TIMER_V2 -DAPP_TIMER_V2_RTC1_ENABLED -DNRF_DFU_TRANSPORT_BLE=1 -DSOFTDEVICE_PRESENT -DNRF52833_XXAA -DNRF52833 -DTARGET_MCU_NRF52833 -DNRF5 -DNRF52833 -D__CORTEX_M4 -DS113 -DTOOLCHAIN_GCC -D__START=target_start
