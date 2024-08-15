# Compiler settings
SDCC := sdcc
SDCC_OPTIONS := -mmcs51 --model-small --iram-size 128 --code-size 4096 
PACKIHX := packihx

# Programmer settings
AVRDUDE := avrdude
AVRDUDE_OPTIONS := -C avrdude.conf -c arduino_as_isp -p AT89S51 

# Project diretories
BUILD_FOLDER := build
SOURCE_FOLDER := src

# Entry point
MAIN_FILE_NAME := main
MAIN_SOURCE_FILE := $(MAIN_FILE_NAME).c
MAIN_IHX_FILE := $(MAIN_FILE_NAME).ihx
MAIN_HEX_FILE := $(MAIN_FILE_NAME).hex

main: clean dependencies
	$(SDCC) $(SDCC_OPTIONS) $(SOURCE_FOLDER)/$(MAIN_SOURCE_FILE) $(wildcard $(BUILD_FOLDER)/*.rel) -o $(BUILD_FOLDER)/
	$(PACKIHX) $(BUILD_FOLDER)/$(MAIN_IHX_FILE) > $(BUILD_FOLDER)/$(MAIN_HEX_FILE)

dependencies: $(SOURCE_FOLDER)/lib/*.c $(SOURCE_FOLDER)/screen/*.c
	mkdir -p $(BUILD_FOLDER)
	$(foreach file, $^, $(SDCC) -c $(file) -I src -o $(BUILD_FOLDER)/;)

signature:
	$(AVRDUDE) $(AVRDUDE_OPTIONS) -P $(PORT) -U signature:r:-:h

flash:
	$(AVRDUDE) $(AVRDUDE_OPTIONS) -P $(PORT) -U flash:w:"$(BUILD_FOLDER)/$(MAIN_HEX_FILE)":a

clean:
	rm -rf $(BUILD_FOLDER)/*
