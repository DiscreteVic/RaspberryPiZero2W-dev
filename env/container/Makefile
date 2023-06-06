IMG_NAME=zero2w
CONT_NAME=$(IMG_NAME)-cont 
SRC_DIR=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))/../../

	
build: build-image build-container

build-image: 
	@docker build -t $(IMG_NAME) .

build-container:
	@docker run -it --name $(CONT_NAME)  --privileged -v /dev/bus/usb:/dev/bus/usb -v $(SRC_DIR):/root/shared/ -p 3333:3333 -p 4444:4444 -p 6666:6666 $(IMG_NAME)  /bin/bash

remove: remove-container remove-image

remove-container:
	@docker stop $(CONT_NAME)
	@docker rm $(CONT_NAME)

remove-image:
	@docker image rm $(IMG_NAME):latest


start:
	@docker start $(CONT_NAME)

stop:
	@docker stop $(CONT_NAME)


run:
	@docker exec -it $(CONT_NAME) /bin/bash


export:
	@ docker export $(CONT_NAME) > $(IMG_NAME).tar

import:
	@ cat $(IMG_NAME).tar | docker import - $(IMG_NAME):new