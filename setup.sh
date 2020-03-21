#!/bin/bash

# User instructions
echo "Verlet Integration set-up tool"
echo ""
echo "Select CMAKE generator (invalid index will quit the installer):"
echo "    0 => Custom"
echo "    1 => Visual Studio 2019"
echo "    2 => Visual Studio 2017"
echo "    3 => Visual Studio 2015"
echo "    4 => Visual Studio 2013"
echo ""
printf "Choice: "
read -r choice

# Set the chosen CMAKE generator
generator=""
case $choice in
    0)
        printf "Generator name: "
        read -r generator
        ;;

    1)
        generator="Visual Studio 16 2019"
        ;;

    2)
        generator="Visual Studio 15 2017"
        ;;
    
    3)
        generator="Visual Studio 14 2015"
        ;;
        
    4)
        generator="Visual Studio 12 2013"
        ;;

    *)
        exit
        ;;
esac

# Get GLAD to generate the necessary files
pushd _deps/glad
python -m glad --generator=c --out-path=GL --reproducible --profile=core
popd

# Ensure we have a build directory
mkdir -p build

# Generate project files
pushd build
cmake .. -G "$generator" -A x64
popd
