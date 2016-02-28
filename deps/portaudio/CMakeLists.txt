set(PORTAUDIO_URL
        "https://subversion.assembla.com/svn/portaudio/portaudio/trunk"
        CACHE STRING "Location of portaudio svn repository")

# Rev. 1944 contains fix for:
#   https://www.assembla.com/spaces/portaudio/tickets/228-ksguid-lib-linker-issues
set(PORTAUDIO_REV
        "1944"
        CACHE STRING "Portaudio svn revision to check out")

add_custom_target(ext_portaudio_patch
        SOURCES portaudio_cmakelists.txt.in)

ExternalProject_Add(ext_portaudio
        PREFIX "${EXTERNALS_WORK_DIR}"
        SOURCE_DIR "${EXTERNALS_WORK_DIR}/src/portaudio"
        BINARY_DIR "${EXTERNALS_WORK_DIR}/build/portaudio"
        INSTALL_DIR "${EXTERNALS_INSTALL_DIR}"
        SVN_REPOSITORY ${PORTAUDIO_URL}
        SVN_REVISION -r ${PORTAUDIO_REV}
        UPDATE_COMMAND ""
        PATCH_COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/portaudio_cmakelists.txt.in
                ${EXTERNALS_WORK_DIR}/src/portaudio/CMakeLists.txt
        CMAKE_ARGS
            ${PLATFORM_CMAKE_ARGS}
            -G ${CMAKE_GENERATOR}
            -DCMAKE_INSTALL_PREFIX=${EXTERNALS_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
