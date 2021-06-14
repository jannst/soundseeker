#!/bin/sh

# Check npm & npx installation
no_npm=false;
if ! npm="$(type -p "npm")" || [ -z $npm ]; then
	no_npm=true;
fi
no_npx=false;
if ! npx="$(type -p "npx")" || [ -z $npx ]; then
	no_npw=true;
fi

# Update node module
if [ "$no_npx" = false ] && [ "$no_npm" = false ] && [ -f "package.json" ]; then
	echo "Updating node modules : "
	echo "npx npm-check-updates -u && npm install"
	npx npm-check-updates -u --packageFile package.json && npm install
fi
