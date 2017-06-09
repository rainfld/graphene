#!/bin/bash

set -x

sudo docker run -it --rm -u travis \
	-v $(git rev-parse --show-toplevel):/home/travis/builds/oscarlab/graphene \
	quay.io/travisci/travis-jvm \
	/bin/bash -lc ". ~/builds/oscarlab/graphene/Scripts/travis-hook.sh"
