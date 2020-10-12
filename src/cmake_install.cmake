# Install script for directory: /opt/workspace/flameshot-ocr/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/flameshot" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/flameshot")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/flameshot"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/opt/workspace/flameshot-ocr/src/flameshot")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/flameshot" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/flameshot")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/flameshot"
         OLD_RPATH "/opt/Qt5.14.2/5.14.2/gcc_64/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/flameshot")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE DIRECTORY FILES "/opt/workspace/flameshot-ocr/src/share/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/flameshot/translations" TYPE FILE FILES
    "/opt/workspace/flameshot-ocr/src/Internationalization_ca.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_cs.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_de_DE.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_es.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_eu.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_fr.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_hu.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_it_IT.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_ja.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_ka.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_ko.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_nl.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_nl_NL.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_pl.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_pt_BR.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_ru.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_sk.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_sr_SP.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_sv_SE.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_tr.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_uk.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_zh_CN.qm"
    "/opt/workspace/flameshot-ocr/src/Internationalization_zh_TW.qm"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/opt/workspace/flameshot-ocr/src/cli/cmake_install.cmake")
  include("/opt/workspace/flameshot-ocr/src/config/cmake_install.cmake")
  include("/opt/workspace/flameshot-ocr/src/core/cmake_install.cmake")
  include("/opt/workspace/flameshot-ocr/src/utils/cmake_install.cmake")
  include("/opt/workspace/flameshot-ocr/src/widgets/cmake_install.cmake")
  include("/opt/workspace/flameshot-ocr/src/tools/cmake_install.cmake")

endif()

