#!/bin/bash
# Make work directory if not exist
if [ ! -d ./work ]; then
	mkdir work
fi

NB_USER='jovyan'
HOST_PORT=8888
GUEST_PORT=8888
CONTAINER_NAME='jupyter'
IMAGE_NAME='jupyter_base'

#docker run --rm -v `pwd`/work:/home/$NB_USER/work -p $HOST_PORT:$GUEST_PORT --name $CONTAINER_NAME -it $IMAGE_NAME jupyter notebook --allow-root
docker run --rm -v `pwd`/work:/home/$NB_USER/work -p $HOST_PORT:$GUEST_PORT --name $CONTAINER_NAME -it $IMAGE_NAME jupyter notebook --allow-root
 
