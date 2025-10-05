#!/bin/bash
set -e

PROJECT_NAME="SDE"
BUILD_TYPE="release"
BUILD_DIR="build"

if [[ "$#" -gt 0 ]]; then
    case "$1" in
        -d|--debug)
            BUILD_TYPE="debug"
            ;;
        *)
            echo "Unknown option: $1"
            echo "Usage: $0 [-d|--debug]"
            exit 1
            ;;
    esac
fi

echo "building as $BUILD_TYPE"
cmake -S . -B "$BUILD_TYPE/$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

echo "building w/ cmake"
cmake --build "$BUILD_TYPE/$BUILD_DIR" --config "$BUILD_TYPE" -j$(nproc)

if [[ -f "$BUILD_TYPE/$BUILD_DIR/$PROJECT_NAME" ]]; then
    cp "$BUILD_TYPE/$BUILD_DIR/$PROJECT_NAME" "$BUILD_TYPE/"

    echo "build successful: $BUILD_TYPE/$PROJECT_NAME"
else
    echo "build failure: no executable found"
    exit 1
fi

"./$BUILD_TYPE/$PROJECT_NAME"
