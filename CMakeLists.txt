#
# Cyan <https://cyan.fxarena.net>
# Copyright Ole-André Rodlie, FxArena DA.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#

cmake_minimum_required(VERSION 3.0)

project(Cyan VERSION 1.99.4)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(COMPANY "FxArena")
set(COPYRIGHT "Copyright Ole-Andre Rodlie. All rights reserved.")
set(IDENTIFIER "net.fxarena.cyan")
set(MAGICK_PKG_CONFIG "Magick++" CACHE STRING "ImageMagick pkg-config name")
option(BUILD_PLUGIN_COLOR_TRIANGLE "Build color triangle plugin" OFF)
option(DEBUG_TILES "Show tiles for debug purpose" OFF)
option(RUNTIME_WARNINGS "Show warnings during runtime" OFF)

set(HEADERS_API lib/CyanWidgetApi.h)
set(HEADERS_APP app/editor.h)
set(SOURCES_LIB
    lib/CyanAboutDialog.cpp
    lib/CyanCommon.cpp
    lib/CyanImageFormat.cpp
    lib/CyanTileItem.cpp
    lib/CyanLayerItem.cpp
    lib/CyanLayerItemDelegate.cpp
    lib/CyanView.cpp
    lib/CyanColorConvert.cpp
    lib/CyanColorConvertDialog.cpp
    lib/CyanPluginLoader.cpp
    lib/CyanMdi.cpp
    lib/CyanMdiWindow.cpp
    lib/CyanLayerWidget.cpp
    lib/CyanLayerTree.cpp
    lib/CyanLayerTreeItem.cpp
    lib/CyanNewMediaDialog.cpp
    lib/CyanGuideItem.cpp
    lib/CyanBatchWidget.cpp
    lib/qtcolorpicker.cpp
    #lib/qtcolortriangle.cpp
    lib/qtwindowlistmenu.cpp
)
set(HEADERS_LIB
    lib/CyanAboutDialog.h
    lib/CyanCommon.h
    lib/CyanImageFormat.h
    lib/CyanTileItem.h
    lib/CyanLayerItem.h
    lib/CyanLayerItemDelegate.h
    lib/CyanView.h
    lib/CyanColorConvert.h
    lib/CyanColorConvertDialog.h
    lib/CyanPluginLoader.h
    lib/CyanMdi.h
    lib/CyanMdiWindow.h
    lib/CyanLayerWidget.h
    lib/CyanLayerTree.h
    lib/CyanLayerTreeItem.h
    lib/CyanNewMediaDialog.h
    lib/CyanGuideItem.h
    lib/CyanBatchWidget.h
    lib/CyanGlobal.h
    lib/qtcolorpicker.h
    #lib/qtcolortriangle.h
    lib/qtwindowlistmenu.h
)
set(SOURCES_APP
    app/main.cpp
    app/editor.cpp
    app/setup.cpp
    app/color.cpp
    app/viewtool.cpp
    app/layers.cpp
    app/tabs.cpp
)

set(RESOURCES
    share/icons.qrc
    docs/docs.qrc
)

add_definitions(-DCYAN_VERSION="${PROJECT_VERSION}")
add_definitions(-DCYAN_IMAGE_FORMAT_VERSION="${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
add_definitions(-DCYAN_LIBRARY)

find_package(Qt5 5.5 REQUIRED Core Gui Widgets Concurrent Test)
find_package(PkgConfig REQUIRED)
pkg_search_module(MAGICK REQUIRED ${MAGICK_PKG_CONFIG}>=7.0.8)
pkg_search_module(LCMS2 REQUIRED lcms2)
pkg_search_module(FONTCONF REQUIRED fontconfig)

if (APPLE)
    set(FC_FONTS_DIR "<dir>/System/Library/Fonts</dir><dir>/Library/Fonts</dir><dir>~/Library/Fonts</dir>")
    set(FC_CACHE_DIR "<cachedir>~/.cache/fontconfig</cachedir>")
elseif(WIN32)
    set(FC_FONTS_DIR "<dir>WINDOWSFONTDIR</dir><dir>~/AppData/Local/Microsoft/Windows/Fonts</dir>")
    set(FC_CACHE_DIR "<cachedir>LOCAL_APPDATA_FONTCONFIG_CACHE</cachedir>")
else()
    set(FC_FONTS_DIR "<dir>/usr/share/fonts/OTF</dir><dir>/usr/share/fonts/TTF</dir><dir>/usr/share/fonts/Type1</dir><dir>/usr/share/fonts/Speedo</dir><dir>/usr/share/fonts/cyrillic</dir><dir>/usr/share/fonts/misc</dir><dir prefix=\"xdg\">fonts</dir>")
    set(FC_CACHE_DIR "<cachedir prefix=\"xdg\">fontconfig</cachedir><cachedir>~/.fontconfig</cachedir>")
endif()
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/share/fonts.conf.in
    ${CMAKE_CURRENT_BINARY_DIR}/etc/fonts/fonts.conf
    @ONLY
)

include_directories(
    app
    lib
    ${MAGICK_INCLUDE_DIRS}
    ${LCMS2_INCLUDE_DIRS}
    ${FONTCONF_INCLUDE_DIRS}
)

add_compile_options(-Wall -Wextra)
if(CMAKE_BUILD_TYPE MATCHES "^(release|Release|RELEASE)$")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
else()
    add_definitions(-DQT_MESSAGELOGCONTEXT)
endif()
if(${DEBUG_TILES})
    add_definitions(-DSHOW_TILES)
endif()
if(${RUNTIME_WARNINGS})
    add_definitions(-DSHOW_WARN)
endif()

if(APPLE)
    set(ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/${PROJECT_NAME}.icns)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
    set(MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})
    set(MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER})
    set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME})
    set_source_files_properties(${ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
endif()

if(WIN32)
    set(ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/${PROJECT_NAME}.ico)
    set(GUI_TYPE WIN32)
    set(PRODUCT_COMMENTS "${PROJECT_NAME} Pixel Editor")
    set(PRODUCT_COMPANY_NAME ${COMPANY})
    set(PRODUCT_FILE_DESCRIPTION "${PROJECT_NAME} Pixel Editor")
    set(PRODUCT_VERSION "${PROJECT_VERSION}")
    set(PRODUCT_INTERNAL_NAME ${PROJECT_NAME})
    set(PRODUCT_COMPANY_COPYRIGHT ${COPYRIGHT})
    set(PRODUCT_ORIGINAL_FILENAME "${PROJECT_NAME}.exe")
    set(PRODUCT_BUNDLE ${PROJECT_NAME})
    set(WINDOWS_RESOURCE_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/share/${PROJECT_NAME}.rc.in
        ${WINDOWS_RESOURCE_FILE}
        @ONLY
    )
    configure_file(
        ${ICON_FILE}
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.ico
        COPYONLY
    )
endif()

if(APPLE)
    add_executable(
        ${PROJECT_NAME}
        MACOSX_BUNDLE
        ${ICON_FILE}
        ${SOURCES_APP}
        ${SOURCES_LIB}
        ${HEADERS_APP}
        ${HEADERS_LIB}
        ${HEADERS_API}
        ${RESOURCES}
    )
elseif(WIN32)
    add_executable(
        ${PROJECT_NAME}
        WIN32
        ${ICON_FILE}
        ${WINDOWS_RESOURCE_FILE}
        ${SOURCES_APP}
        ${SOURCES_LIB}
        ${HEADERS_APP}
        ${HEADERS_LIB}
        ${HEADERS_API}
        ${RESOURCES}
    )
else()
    add_executable(
        ${PROJECT_NAME}
        ${SOURCES_APP}
        ${SOURCES_LIB}
        ${HEADERS_APP}
        ${HEADERS_LIB}
        ${HEADERS_API}
        ${RESOURCES})
endif()

target_compile_options(${PROJECT_NAME} PRIVATE ${MAGICK_STATIC_CFLAGS})
target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Concurrent
    ${MAGICK_STATIC_LIBRARIES}
    ${LCMS2_LIBRARIES}
    ${MAGICK_STATIC_LDFLAGS}
    ${LCMS2_LDFLAGS}
    ${FONTCONF_LDFLAGS}
)

if(UNIX AND NOT APPLE)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/128x128
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/160x160
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/16x16/apps/${PROJECT_NAME}.png
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/16x16/apps
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/192x192
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/20x20
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/24x24
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/256x256
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/32x32/apps/${PROJECT_NAME}.png
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/32x32/apps
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/36x36
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/48x48
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/512x512
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/64x64
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/72x72
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/icons/hicolor/96x96
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
    )
    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/share/miff.xml
        DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/mime/packages
    )
    install(
        FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/share/${PROJECT_NAME}.desktop
        DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/applications
    )
    install(
        FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/share/icc/ISOcoated_v2_300_bas.icc
        ${CMAKE_CURRENT_SOURCE_DIR}/share/icc/ISOcoated_v2_grey1c_bas.icc
        ${CMAKE_CURRENT_SOURCE_DIR}/share/icc/SWOP2006_Coated5v2.icc
        ${CMAKE_CURRENT_SOURCE_DIR}/share/icc/sRGB2014.icc
        ${CMAKE_CURRENT_SOURCE_DIR}/share/icc/sRGB_IEC61966-2-1_no_black_scaling.icc
        ${CMAKE_CURRENT_SOURCE_DIR}/share/icc/sRGB_v4_ICC_preference.icc
        DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/profiles
    )
    install(
        FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/COPYING
        ${CMAKE_CURRENT_SOURCE_DIR}/GPL_EXCEPTION
        ${CMAKE_CURRENT_SOURCE_DIR}/docs/README.md
        DESTINATION
        ${CMAKE_INSTALL_DOCDIR}-${PROJECT_VERSION}
    )
endif()


# Include Cyan Color Triangle Widget
if(BUILD_PLUGIN_COLOR_TRIANGLE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/plugins/CyanColorTriangle)
endif()
