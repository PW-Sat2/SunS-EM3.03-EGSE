# -- User definitions ---------------------------

HAL_PATH = AVR-HAL/HAL
APP_NAME = SUNS_EM3_EGSE

BOARD = ARDUINONANO328P_8MHZ

INCLUDES = \
  -I . \
  -I app/inc

SRCS = \
  main.cpp


include $(HAL_PATH)/build.make

