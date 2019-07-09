# project specific files
SRC = matrix.c
SRC += config_led.c

# For platform and packs
ARM_ATSAM = SAMD51J18A
MCU = cortex-m4

CUSTOM_MATRIX = yes

# Unicode
UNICODEMAP_ENABLE = yes

# Custom RGB matrix handling
RGB_MATRIX_ENABLE = custom
RGB_MATRIX_CUSTOM_USER = yes
EXTRAFLAGS += -DLED_HITS_TO_REMEMBER=64
EXTRAFLAGS += -DRGB_MATRIX_STARTUP_MODE=RGB_MATRIX_CUSTOM_reactive_gradient

# Misc
BOOTMAGIC_ENABLE = yes       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = yes         # Console for debug(+400)
DEBUG_ENABLE = yes
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover
VIRTSER_ENABLE = yes         # USB Serial Driver
RAW_ENABLE = no             # Raw device
LEADER_ENABLE = yes
