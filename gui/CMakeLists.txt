project (idso1070-gui)

add_subdirectory(resources)

# add gtkmm
find_package(Gtkmm REQUIRED)
include_directories(${GTKMM_INCLUDE_DIRS})

# add liquidsdr
find_package(LiquidSdr REQUIRED)
include_directories(${LIQUIDDSP_INCLUDE_DIRS})

add_executable(idso1070-gui main.cxx ScopeWidget.cxx SettingsWidget.cxx AppWindow.cxx TransmissionLogDialog.cxx)
target_link_libraries (idso1070-gui idso1070 resources ${GTKMM_LIBRARIES} ${LIQUIDDSP_LIBRARIES})

install (TARGETS idso1070-gui DESTINATION ${CMAKE_INSTALL_BINDIR})