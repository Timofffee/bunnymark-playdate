HEAP_SIZE      = 8388208
STACK_SIZE     = 61800

PRODUCT = Bunnymark.pdx

SDK = ${PLAYDATE_SDK_PATH}
ifeq ($(SDK),)
SDK = $(shell egrep '^\s*SDKRoot' ~/.Playdate/config | head -n 1 | cut -c9-)
endif

ifeq ($(SDK),)
$(error SDK path not found; set ENV value PLAYDATE_SDK_PATH)
endif

VPATH += Source

SRC = 	\
        main.c \
        game.c \

UINCDIR = 
UASRC = 
UDEFS = 
UADEFS = 
ULIBDIR =
ULIBS =

include $(SDK)/C_API/buildsupport/common.mk
