#!/bin/bash
cd "$(dirname "$0")"
echo "npm install"
npm install
rm -rf ./public
hugo --gc --minify
