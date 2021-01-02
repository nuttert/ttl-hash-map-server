export PROJECT_NAME = l1-memory-cache
.PHONY: $(PROJECT_NAME)
build:
	mkdir -p build
	cd ./build && cmake .. -D TEST_MODE=FALSE -D PROJECT_NAME=$(PROJECT_NAME) && make
run:
	mkdir -p build
	cd ./build && cmake .. -D TEST_MODE=FALSE -D PROJECT_NAME=$(PROJECT_NAME) && make && ./$(PROJECT_NAME)
run-test:
	mkdir -p build
	cd ./build && cmake .. -D TEST_MODE=TRUE -D PROJECT_NAME=$(PROJECT_NAME) && make && ./$(PROJECT_NAME)
