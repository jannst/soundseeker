#!/bin/sh

echo "Installing node modules : "
echo "npm install"
npm install
./update.sh
hugo --gc --minify
