cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------- Plugin Config ---------------
execute_process(COMMAND node -p "require('@nodegui/nodegui/plugin').CMAKE_HELPER_FILE"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODEGUI_PLUGIN_CMAKE_HELPER
)
string(REPLACE "\n" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
string(REPLACE "\"" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
include("${NODEGUI_PLUGIN_CMAKE_HELPER}")

# -------------- User Config ---------------
set(PLUGIN_ADDON_NAME "nodegui_plugin_multimedia")

project(${PLUGIN_ADDON_NAME})

add_library(${PLUGIN_ADDON_NAME} SHARED  
    "${CMAKE_JS_SRC}"
    # Core
    "${PROJECT_SOURCE_DIR}/src/cpp/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/helper.cpp"
    # Audio
    "${PROJECT_SOURCE_DIR}/src/cpp/audio/qaudiobuffer_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/audio/qaudiobufferoutput_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/audio/qaudiodevice_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/audio/qaudioformat_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/audio/qaudiooutput_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/audio/naudiobufferoutput.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/audio/naudiooutput.hpp"
    # Camera
    "${PROJECT_SOURCE_DIR}/src/cpp/camera/qcameraformat_wrap.cpp"
    # Misc
    "${PROJECT_SOURCE_DIR}/src/cpp/misc/qmediametadata_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/misc/qmediatimerange_wrap.cpp"
    # Playback
    "${PROJECT_SOURCE_DIR}/src/cpp/playback/qmediaplayer_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/playback/qplaybackoptions_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/playback/nmediaplayer.hpp"
    # Video
    "${PROJECT_SOURCE_DIR}/src/cpp/video/qabstractvideobuffer_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/video/qvideoframe_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/video/qvideoframeformat_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/video/qvideosink_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/video/nvideosink.hpp"
    # Widgets
    "${PROJECT_SOURCE_DIR}/src/cpp/widgets/qvideowidget_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/widgets/nvideowidget.hpp"
) 

AddPluginConfig(${PLUGIN_ADDON_NAME})

# Adapted from https://github.com/sedwards2009/nodegui-plugin-qads/blob/main/CMakeLists.txt
if (UNIX AND NOT APPLE)
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES
        INSTALL_RPATH "\$ORIGIN/../../../@nodegui/nodegui/miniqt/6.10.2/gcc_64/lib"
    )
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
endif()

if (APPLE)
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES
        INSTALL_RPATH "@loader_path/../../../@nodegui/nodegui/miniqt/6.10.2/macos/lib"
    )
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
endif()

# Shut up about QOBJECT_SIGNALS
target_compile_options(${PLUGIN_ADDON_NAME} PRIVATE
    $<$<COMPILE_LANG_AND_ID:CXX,GNU,Clang>:-Wno-deprecated -Wno-deprecated-declarations>
)

find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS MultimediaWidgets)

target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE 
    "${CMAKE_JS_INC}" 
    "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_LIB}"
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Multimedia
    Qt6::MultimediaWidgets
)

