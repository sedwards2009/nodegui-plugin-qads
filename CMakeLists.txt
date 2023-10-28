cmake_minimum_required(VERSION 3.1)
# -------------- Plugin Config ---------------
execute_process(COMMAND node -p "require('@nodegui/nodegui/plugin').CMAKE_HELPER_FILE"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODEGUI_PLUGIN_CMAKE_HELPER
)
string(REPLACE "\n" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
string(REPLACE "\"" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
include("${NODEGUI_PLUGIN_CMAKE_HELPER}")

# -------------- User Config ---------------
set(PLUGIN_ADDON_NAME "nodegui_plugin_qads")

project(${PLUGIN_ADDON_NAME})

if (UNIX AND NOT APPLE)
    include_directories(${Qt6Gui_PRIVATE_INCLUDE_DIRS})
endif()

set(SRCS
    "${CMAKE_JS_SRC}"
    "${PROJECT_SOURCE_DIR}/src/cpp/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/cdockcontainerwidget_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/ncdockcontainerwidget.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/cdockmanager_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/ncdockmanager.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/cdockareawidget_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/ncdockareawidget.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/cdockwidget_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/ncdockwidget.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/cdockareatitlebar_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/ncdockareatitlebar.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/cdockareatabbar_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/ncdockareatabbar.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/cfloatingdockcontainer_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/ncfloatingdockcontainer.hpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/cdocksplitter_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/cdockwidgettab_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/ncdockwidgettab.hpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/ads_globals.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockAreaTabBar.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockAreaTitleBar.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockAreaWidget.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockContainerWidget.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockManager.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockOverlay.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockSplitter.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockWidget.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockWidgetTab.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockingStateReader.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockFocusController.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/ElidingLabel.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/FloatingDockContainer.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/FloatingDragPreview.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/IconProvider.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/DockComponentsFactory.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/AutoHideSideBar.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/AutoHideTab.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/AutoHideDockContainer.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/PushButton.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/ResizeHandle.cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/ads.qrc"
)

if (NOT APPLE)
    set(SRCS "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src/linux/FloatingWidgetTitleBar.cpp" ${SRCS})
    #set(ads_HEADERS linux/FloatingWidgetTitleBar.h ${ads_HEADERS})
endif()

add_library(${PLUGIN_ADDON_NAME} SHARED ${SRCS})

target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src")

AddPluginConfig(${PLUGIN_ADDON_NAME})

if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE ${X11_LIBRARIES})

    # Make the output shared library's RPATH relative so that it can
    # find the other Qt and NodeGui libs even if the dir is moved.

    include_directories(${Qt6Gui_PRIVATE_INCLUDE_DIRS})

    # NodeGui and qode are assumed to be in the same node_modules directory as nodegui-plugin-qhotkey.
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES
        INSTALL_RPATH "\$ORIGIN/../../../@nodegui/nodegui/miniqt/6.4.1/gcc_64/lib:\$ORIGIN/../../../@nodegui/nodegui/build/Release")
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
endif()

if (APPLE)
    find_library(CARBON_LIBRARY Carbon)
    mark_as_advanced(CARBON_LIBRARY)
    target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE ${CARBON_LIBRARY})

    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES
        INSTALL_RPATH "@loader_path/../../../@nodegui/nodegui/miniqt/6.4.1/macos/lib:@loader_path/../../../@nodegui/nodegui/build/Release")
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES SKIP_BUILD_RPATH FALSE)
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
endif()

target_compile_definitions(${PLUGIN_ADDON_NAME} PUBLIC ADS_STATIC)

target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_INC}"
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/src/cpp"
    "${PROJECT_SOURCE_DIR}/Qt-Advanced-Docking-System/src"
)
target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_LIB}"
     Qt6::Core
     Qt6::Gui
     Qt6::Widgets
)
