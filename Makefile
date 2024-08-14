COMPILER := sdcc
OPTIONS := -mmcs51 --model-small --iram-size 128 --code-size 4096 

BUILD_FOLDER := build
SOURCE_FOLDER := src

main: dependencies
	$(COMPILER) $(OPTIONS) $(SOURCE_FOLDER)/main.c $(wildcard $(BUILD_FOLDER)/*.rel) -o $(BUILD_FOLDER)/

dependencies: $(SOURCE_FOLDER)/lib/*.c $(SOURCE_FOLDER)/screen/*.c
	mkdir -p $(BUILD_FOLDER)
	$(foreach file, $^, $(COMPILER) -c $(file) -I src -o $(BUILD_FOLDER)/;)

clean:
	rm -rf $(BUILD_FOLDER)/*
