find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)
qt_standard_project_setup(REQUIRES 6.8)

set(APP_SOURCES
    main.cc
    application/dqc_application.cc
    src/dqc_proprty.cc
    src/dqc_model.cc
    )

set(APP_HEADERS
    version.hxx
    application/dqc_application.hxx
    src/dqc_proprty.hxx
    src/dqc_model.hxx
    )

qt_add_executable(
    ${EXECUTABLE_NAME}
    ${APP_SOURCES}
    ${APP_HEADERS}
)

qt_add_qml_module(
    ${EXECUTABLE_NAME}
    URI dynamic_qml_component
    VERSION 1.0
    QML_FILES
        Main.qml
        qml/constants/qmldir
        qml/constants/Constants.qml
        qml/contents/DQC_Rectangle.qml
)

target_include_directories(
    ${EXECUTABLE_NAME}
    PUBLIC
    "${CMAKE_BINARY_DIR}/configured_files/include"
)

target_link_libraries(
    ${EXECUTABLE_NAME}
    PRIVATE
    Qt6::Quick
    Qt6::Widgets
)
