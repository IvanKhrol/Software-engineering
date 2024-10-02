set(EXEC task_3)

if ("${OS_TYPE}" EQUAL "UNKNOWN")
  message(FATAL_ERROR "Unknown type of OS")
else()
  if ("${OS_TYPE}" EQUAL "WINDOWS")
    add_compile_definitions(WINDOWS_SYSTEM)
    add_compile_options(
      "/O2"
    )
  endif()

  if ("${OS_TYPE}" EQUAL "LINUX")
    add_compile_definitions(LINUX_SYSTEM)
    add_compile_options(
      "-Wall"
      "-Wextra"
      "-O2"
    )
  endif()
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(UI_HEADERS
  ${PROJECT_ROOT_DIR}/sources/mainwindow/mainwindow.ui 
  ${PROJECT_ROOT_DIR}/sources/MouseHandler/mousehandler.ui
)

set(HEADERS
  ${PROJECT_ROOT_DIR}/sources/mainwindow/mainwindow.hpp
  ${PROJECT_ROOT_DIR}/sources/MouseHandler/mousehandler.hpp
)

set (SOURCES
  ${PROJECT_ROOT_DIR}/sources/main.cpp
  ${PROJECT_ROOT_DIR}/sources/mainwindow/mainwindow.cpp
  ${PROJECT_ROOT_DIR}/sources/MouseHandler/mousehandler.cpp
)

qt_add_executable(${EXEC} 
  MANUAL_FINALIZATION
  ${RESOURCES}
  ${SOURCES} 
  ${HEADERS} 
  ${UI_HEADERS}
)

include_directories(
    ${PROJECT_ROOT_DIR}/sources/
    ${PROJECT_ROOT_DIR}/include/
)

target_link_libraries(${EXEC} PRIVATE 
  Qt6::Core 
  Qt6::Widgets 
  Qt6::Gui
)
