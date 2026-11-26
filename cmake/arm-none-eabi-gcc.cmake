set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(DEFINED ENV{ARM_TC})
  set(_ARM_TC_ROOT "$ENV{ARM_TC}")
elseif(DEFINED ENV{GNU_TOOLS_FOR_STM32_COMPILER_PATH})
  set(_ARM_TC_ROOT "$ENV{GNU_TOOLS_FOR_STM32_COMPILER_PATH}")
else()
  set(_ARM_TC_ROOT "$ENV{HOME}/.local/opt/gnu-tools-for-stm32-13.3.rel1")
endif()

find_program(ARM_NONE_EABI_GCC arm-none-eabi-gcc
  HINTS "${_ARM_TC_ROOT}/bin" REQUIRED)
find_program(ARM_NONE_EABI_GXX arm-none-eabi-g++
  HINTS "${_ARM_TC_ROOT}/bin")
find_program(ARM_NONE_EABI_AR arm-none-eabi-ar
  HINTS "${_ARM_TC_ROOT}/bin" REQUIRED)
find_program(ARM_NONE_EABI_RANLIB arm-none-eabi-ranlib
  HINTS "${_ARM_TC_ROOT}/bin" REQUIRED)

set(CMAKE_C_COMPILER "${ARM_NONE_EABI_GCC}" CACHE FILEPATH "GNU Arm C compiler")
set(CMAKE_ASM_COMPILER "${ARM_NONE_EABI_GCC}" CACHE FILEPATH "GNU Arm assembler driver")
set(CMAKE_AR "${ARM_NONE_EABI_AR}" CACHE FILEPATH "GNU Arm archiver")
set(CMAKE_RANLIB "${ARM_NONE_EABI_RANLIB}" CACHE FILEPATH "GNU Arm ranlib")
if(ARM_NONE_EABI_GXX)
  set(CMAKE_CXX_COMPILER "${ARM_NONE_EABI_GXX}" CACHE FILEPATH "GNU Arm C++ compiler")
endif()
