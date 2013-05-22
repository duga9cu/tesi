#!/bin/sh
CURRENT_DIR=`pwd`

MODULE_NAME=${TARGET_NAME}.${EXECUTABLE_EXTENSION}

RELEASE_SS="Release"
DEBUG_SS="Debug"

if [[ "$CONFIGURATION" =~ "${DEBUG_SS}" ]]
then
    echo "Debug configuration."
elif [[ "$CONFIGURATION" =~ "${RELEASE_SS}" ]]
then
    cd "${BUILD_DIR}/${CONFIGURATION}"
    echo "Copying ${MODULE_NAME} to ${AUDACITY_MODULES_PATH}"
    cp  "${MODULE_NAME}" "${AUDACITY_MODULES_PATH}"
    cd ${CURRENT_DIR}
fi

exit 0
