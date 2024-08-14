SDCC := sdcc
OPTIONS := -mmcs51 --model-small --iram-size 128 --code-size 4096 
PACKIHX := packihx

BUILD_FOLDER := build
SOURCE_FOLDER := src

main: dependencies
	$(SDCC) $(OPTIONS) $(SOURCE_FOLDER)/main.c $(wildcard $(BUILD_FOLDER)/*.rel) -o $(BUILD_FOLDER)/
	$(PACKIHX) $(BUILD_FOLDER)/main.ihx > $(BUILD_FOLDER)/main.hex

dependencies: $(SOURCE_FOLDER)/lib/*.c $(SOURCE_FOLDER)/screen/*.c
	mkdir -p $(BUILD_FOLDER)
	$(foreach file, $^, $(SDCC) -c $(file) -I src -o $(BUILD_FOLDER)/;)

clean:
	rm -rf $(BUILD_FOLDER)/*
