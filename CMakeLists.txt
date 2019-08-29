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

project(Cyan VERSION 1.9.0)
set(PROJECT_VERSION_TYPE "Alpha")
if(NOT PROJECT_VERSION_TWEAK)
    set(PROJECT_VERSION_TWEAK 0)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(COMPANY "FxArena DA")
set(COPYRIGHT "Copyright Ole-Andre Rodlie, FxArena DA. All rights reserved.")
set(IDENTIFIER "net.fxarena.cyan")
set(WEBSITE "https://cyan.fxarena.net")
set(INSTALLER_ID "0830D6C5-BB35-41E6-B694-971AA1CC8059")
set(MAGICK_PKG_CONFIG "Magick++" CACHE STRING "ImageMagick pkg-config name")

set(
    HEADERS_API
    lib/CyanWidgetApi.h
)
set(
    SOURCES_LIB
    lib/CyanImageFormat.cpp
    lib/CyanTileItem.cpp
    lib/CyanLayerItem.cpp
    lib/CyanView.cpp
    lib/CyanColorConvert.cpp
    lib/qtcolorpicker.cpp
    lib/qtcolortriangle.cpp
    lib/qtwindowlistmenu.cpp
)
set(
    HEADERS_LIB
    lib/CyanImageFormat.h
    lib/CyanTileItem.h
    lib/CyanLayerItem.h
    lib/CyanView.h
    lib/CyanColorConvert.h
    lib/CyanGlobal.h
    lib/qtcolorpicker.h
    lib/qtcolortriangle.h
    lib/qtwindowlistmenu.h
)
set(
    SOURCES_APP
    app/cyan_common.cpp
    app/layers/cyan_layertree.cpp
    app/layers/cyan_layertreeitem.cpp
    app/layers/cyan_layerwidget.cpp
    app/widgets/cyan_textwidget.cpp
    app/widgets/colorrgb.cpp
    app/widgets/colorcmyk.cpp
    app/widgets/colorhsv.cpp
    app/dialogs/newmediadialog.cpp
    app/dialogs/convertdialog.cpp
    app/main.cpp
    app/editor.cpp
    app/about.cpp
    app/setup.cpp
    app/color.cpp
    app/viewtool.cpp
    app/messages.cpp
    app/layers.cpp
    app/tabs.cpp
    app/mdi.cpp
)
set(
    HEADERS_APP
    app/cyan_common.h
    app/layers/cyan_layertree.h
    app/layers/cyan_layertreeitem.h
    app/layers/cyan_layerwidget.h
    app/widgets/cyan_textwidget.h
    app/widgets/colorrgb.h
    app/widgets/colorcmyk.h
    app/widgets/colorhsv.h
    app/dialogs/newmediadialog.h
    app/dialogs/convertdialog.h
    app/editor.h
    app/mdi.h
)
set(
    RESOURCES
    share/icons_bundle.qrc
    share/splash.qrc
    docs/docs2.qrc
)

add_definitions(-DCYAN_VERSION="${PROJECT_VERSION}")
add_definitions(-DCYAN_IMAGE_FORMAT_VERSION="${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
add_definitions(-DCYAN_VERSION_MAJOR="${PROJECT_VERSION_MAJOR}")
add_definitions(-DCYAN_VERSION_MINOR="${PROJECT_VERSION_MINOR}")
add_definitions(-DCYAN_VERSION_PATCH="${PROJECT_VERSION_PATCH}")
add_definitions(-DCYAN_VERSION_TYPE="${PROJECT_VERSION_TYPE}")
add_definitions(-DCYAN_GIT="$ENV{GIT}")
add_definitions(-DCYAN_LIBRARY)

if(MINGW)
    add_definitions(-DUSE_FC)
endif()
if(COMPILER_MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
endif()

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(MAGICK REQUIRED ${MAGICK_PKG_CONFIG})
pkg_search_module(LCMS2 REQUIRED lcms2)
pkg_search_module(FONTCONF REQUIRED fontconfig)

include_directories(
    app
    app/layers
    app/widgets
    app/dialogs
    lib
    ${MAGICK_INCLUDE_DIRS}
    ${LCMS2_INCLUDE_DIRS}
    ${FONTCONF_INCLUDE_DIRS}
)

add_compile_options(-Wall -Wextra)
if(CMAKE_BUILD_TYPE MATCHES "^(release|Release|RELEASE)$")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

if(APPLE)
    set(ICON_FILE ${RESOURCE_FOLDER}/icons/${PROJECT_NAME}.icns)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7")
    set_source_files_properties(${PROJECT_NAME}.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
    set(MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})
    set(MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER})
    set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME})
endif()

if(WIN32)
    set(ICON_FILE ${CC_RESOURCE_FOLDER}/icons/${PROJECT_NAME}.ico)
    set(GUI_TYPE WIN32)
    set(PRODUCT_COMMENTS "${PROJECT_NAME} Image Editor")
    set(PRODUCT_COMPANY_NAME ${COMPANY})
    set(PRODUCT_FILE_DESCRIPTION "${PROJECT_NAME} Image Editor")
    set(PRODUCT_VERSION "${PROJECT_VERSION}")
    set(PRODUCT_INTERNAL_NAME ${PROJECT_NAME})
    set(PRODUCT_COMPANY_COPYRIGHT ${COPYRIGHT})
    set(PRODUCT_ORIGINAL_FILENAME "${PROJECT_NAME}.exe")
    set(PRODUCT_BUNDLE ${PROJECT_NAME})
    set(WINDOWS_RESOURCE_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/share/${PROJECT_NAME}.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc
        @ONLY
    )
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/share/${PROJECT_NAME}.iss.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.iss
        @ONLY)
endif()

if(MINGW OR APPLE)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/share/fonts.conf.in
        ${CMAKE_CURRENT_BINARY_DIR}/fonts/fonts.conf
        @ONLY
    )
endif()

add_executable(
    ${PROJECT_NAME}
    ${SOURCES_APP}
    ${HEADERS_APP}
    ${HEADERS_API}
    ${RESOURCES}
)
add_library(
    ${PROJECT_NAME}Api
    SHARED
    ${SOURCES_LIB}
    ${HEADERS_LIB}
    ${HEADERS_API}
)
target_compile_options(${PROJECT_NAME} PRIVATE ${MAGICK_CFLAGS})
target_compile_options(${PROJECT_NAME}Api PRIVATE ${MAGICK_CFLAGS})
target_link_libraries(
    ${PROJECT_NAME}
    ${PROJECT_NAME}Api
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Concurrent
    ${MAGICK_LIBRARIES}
    ${LCMS2_LIBRARIES}
    ${MAGICK_LDFLAGS}
    ${LCMS2_LDFLAGS}
    ${FONTCONF_LDFLAGS}
)
target_link_libraries(
    ${PROJECT_NAME}Api
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Concurrent
    ${MAGICK_LIBRARIES}
    ${LCMS2_LIBRARIES}
    ${MAGICK_LDFLAGS}
    ${LCMS2_LDFLAGS}
)

if(MINGW)
    set(MINGW_ROOT "/opt/Cyan-mxe/usr/x86_64-w64-mingw32.shared" CACHE STRING "MINGW/MXE root dir")
    set(QT_ROOT "${MINGW_ROOT}/qt5" CACHE STRING "Qt root dir")
    set(
        DLLS
        ${MINGW_ROOT}/bin/libbz2.dll
        ${MINGW_ROOT}/bin/libHalf-12.dll
        ${MINGW_ROOT}/bin/libjpeg-9.dll
        ${MINGW_ROOT}/bin/libpangowin32-1.0-0.dll
        ${MINGW_ROOT}/bin/libwinpthread-1.dll
        ${MINGW_ROOT}/bin/libcairo-2.dll
        ${MINGW_ROOT}/bin/libharfbuzz-0.dll
        ${MINGW_ROOT}/bin/liblcms2-2.dll
        ${MINGW_ROOT}/bin/libpcre16-0.dll
        ${MINGW_ROOT}/bin/libexpat-1.dll
        ${MINGW_ROOT}/bin/libiconv-2.dll
        ${MINGW_ROOT}/bin/liblzma-5.dll
        ${MINGW_ROOT}/bin/libpcre-1.dll
        ${MINGW_ROOT}/bin/libffi-6.dll
        ${MINGW_ROOT}/bin/libIex-2_2-12.dll
        ${MINGW_ROOT}/bin/libMagick++-7.Q16HDRI-Cyan-4.dll
        ${MINGW_ROOT}/bin/libpcre2-16-0.dll
        ${MINGW_ROOT}/bin/libfontconfig-1.dll
        ${MINGW_ROOT}/bin/libIexMath-2_2-12.dll
        ${MINGW_ROOT}/bin/libMagickCore-7.Q16HDRI-Cyan-6.dll
        ${MINGW_ROOT}/bin/libpixman-1-0.dll
        ${MINGW_ROOT}/bin/libfreetype-6.dll
        ${MINGW_ROOT}/bin/libIlmImf-2_2-22.dll
        ${MINGW_ROOT}/bin/libMagickWand-7.Q16HDRI-Cyan-6.dll
        ${MINGW_ROOT}/bin/libpng16-16.dll
        ${MINGW_ROOT}/bin/zlib1.dll
        ${MINGW_ROOT}/bin/libgcc_s_seh-1.dll
        ${MINGW_ROOT}/bin/libIlmImfUtil-2_2-22.dll
        ${MINGW_ROOT}/bin/libopenjp2.dll
        ${MINGW_ROOT}/bin/libstdc++-6.dll
        ${MINGW_ROOT}/bin/libglib-2.0-0.dll
        ${MINGW_ROOT}/bin/libIlmThread-2_2-12.dll
        ${MINGW_ROOT}/bin/libpango-1.0-0.dll
        ${MINGW_ROOT}/bin/libtiff-5.dll
        ${MINGW_ROOT}/bin/libgobject-2.0-0.dll
        ${MINGW_ROOT}/bin/libImath-2_2-12.dll
        ${MINGW_ROOT}/bin/libpangocairo-1.0-0.dll
        ${MINGW_ROOT}/bin/libwebp-7.dll
        ${MINGW_ROOT}/bin/libgomp-1.dll
        ${MINGW_ROOT}/bin/libintl-8.dll
        ${MINGW_ROOT}/bin/libpangoft2-1.0-0.dll
        ${MINGW_ROOT}/bin/libwebpmux-3.dll
        )
    set(
        QT_DLLS
        ${QT_ROOT}/bin/Qt5Concurrent.dll
        ${QT_ROOT}/bin/Qt5Core.dll
        ${QT_ROOT}/bin/Qt5Gui.dll
        ${QT_ROOT}/bin/Qt5Widgets.dll
        )
    add_custom_command(
        TARGET
        ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${DLLS}
        ${CMAKE_CURRENT_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy
        ${QT_DLLS}
        ${CMAKE_CURRENT_BINARY_DIR}/
    )
    configure_file(${QT_ROOT}/plugins/platforms/qwindows.dll ${CMAKE_CURRENT_BINARY_DIR}/platforms/qwindows.dll COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/COPYING ${CMAKE_CURRENT_BINARY_DIR}/docs/COPYING COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/share/icons/${PROJECT_NAME}.ico ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.ico COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/README.md ${CMAKE_CURRENT_BINARY_DIR}/docs/README.md COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/ChangeLog.md ${CMAKE_CURRENT_BINARY_DIR}/docs/ChangeLog.md COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/FatCow.txt ${CMAKE_CURRENT_BINARY_DIR}/docs/Icons.txt COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/ICC.txt ${CMAKE_CURRENT_BINARY_DIR}/docs/ICC.txt COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Nokia.txt ${CMAKE_CURRENT_BINARY_DIR}/docs/Nokia.txt COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/share/icc/rgb.icc ${CMAKE_CURRENT_BINARY_DIR}/profiles/rgb.icc COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/share/icc/cmyk.icc ${CMAKE_CURRENT_BINARY_DIR}/profiles/cmyk.icc COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/share/icc/gray.icc ${CMAKE_CURRENT_BINARY_DIR}/profiles/gray.icc COPYONLY)
endif()

if(UNIX AND NOT APPLE)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(DIRECTORY ${RESOURCE_FOLDER}/hicolor DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons)
    install(FILES ${RESOURCE_FOLDER}/${PROJECT_NAME}.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
    install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_DOCDIR}-${PROJECT_VERSION})
endif()

#enable_testing()
#set(TEST_SOURCES src/tst_cyan.cpp src/FXX.cpp res/tests.qrc)
#set(TEST_HEADERS src/FXX.h)
#set(TEST_RESOURCE_FILES res/tests.qrc)
#add_executable(tests ${TEST_SOURCES} ${TEST_HEADERS} ${TEST_RESOURCES_FILES})
#target_link_libraries(tests Qt5::Test)
#target_link_libraries(tests ${MAGICK_LIBRARIES} ${LCMS2_LIBRARIES} ${MAGICK_LDFLAGS} ${LCMS2_LDFLAGS})
#add_test(NAME tests COMMAND tests)