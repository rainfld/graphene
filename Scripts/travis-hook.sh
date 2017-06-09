#!/bin/bash

set -e

# Install a recent ruby (default is 1.9.3)
rvm install 2.3.0
rvm use 2.3.0

# Get the latest Travis code
cd ~/builds
git clone https://github.com/travis-ci/travis-build.git

# Install travis-build to generate a .sh out of .travis.yml
cd travis-build
gem install travis
echo y | (travis whoami || true)
ln -s `pwd` ~/.travis/travis-build
bundle install

# Compile .travis.xml
cd ~/builds/oscarlab/graphene
BRANCH=`git rev-parse --abbrev-ref HEAD`
travis compile | sed -e s/--branch\\\\=\\\\\'\\\\\'/--branch\\\\=\\\\\'\\\\$BRANCH\\\\\'/g > /tmp/ci.sh

# Run Travis
bash /tmp/ci.sh
