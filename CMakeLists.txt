cmake_minimum_required(VERSION 3.0)
project(vdagent-win)

if(MSVC)
    # generate PDB files
    # see https://stackoverflow.com/questions/28178978/how-to-generate-pdb-files-for-release-build-with-cmake-flags/31264946
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF" CACHE STRING "" FORCE)

    # find using vcpkg packages
    find_package(libpng CONFIG REQUIRED)
    find_path(PNG_INCLUDE_DIR NAMES png.h)

    set(PNG_LIBRARY png_static)
    set(ZLIB_LIBRARY)
    set(COMMSUPPW_LIBRARY comsuppw)
else(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -s")

    find_package(PNG REQUIRED)
    set(COMMSUPPW_LIBRARY)
endif(MSVC)

include_directories(common . spice-protocol ${PNG_INCLUDE_DIR})
add_definitions(-DUNICODE -D_UNICODE -DOLDMSVCRT -DWINVER=0x0601)

add_executable(vdagent WIN32
    common/vdcommon.cpp
    common/vdcommon.h
    common/vdlog.cpp
    common/vdlog.h
    vdagent/display_configuration.cpp
    vdagent/display_configuration.h
    vdagent/desktop_layout.cpp
    vdagent/desktop_layout.h
    vdagent/display_setting.cpp
    vdagent/display_setting.h
    vdagent/file_xfer.cpp
    vdagent/file_xfer.h
    vdagent/vdagent.cpp
    vdagent/as_user.cpp
    vdagent/as_user.h
    vdagent/image.cpp
    vdagent/image.h
    vdagent/imagepng.cpp
    vdagent/imagepng.h
    vdagent/shell.cpp
    vdagent/shell.h
    vdagent/vdagent.rc
)
target_link_libraries(vdagent
    ${PNG_LIBRARY}
    ${ZLIB_LIBRARY}
    wtsapi32
    uuid
    ole32
    oleaut32
    ${COMMSUPPW_LIBRARY}
)

add_executable(vdservice
    common/stdint.h
    common/vdcommon.cpp
    common/vdcommon.h
    common/vdlog.cpp
    common/vdlog.h
    vdservice/vdservice.cpp
    vdservice/vdservice.rc
)
target_link_libraries(vdservice
    wtsapi32
)
