set(the_description "Text Detection and Recognition")
ocv_define_module(text opencv_ml opencv_imgproc opencv_core opencv_features2d opencv_dnn OPTIONAL opencv_highgui WRAP python java)

pkg_check_modules(GLIB REQUIRED glib-2.0)
if (GLIB_FOUND)
    message(STATUS "glib:   YES")
else()
    message(STATUS "glib:   NO")
endif()

pkg_check_modules(PANGO REQUIRED pangocairo)
if (PANGO_FOUND)
    message(STATUS "pango:   YES")
    target_include_directories(${the_module} PUBLIC ${PANGO_INCLUDE_DIRS})
    target_link_libraries(${the_module} INTERFACE ${PANGO_LDFLAGS})
else()
    message(STATUS "pango:   NO")
endif()

if(NOT CMAKE_CROSSCOMPILING OR OPENCV_FIND_TESSERACT)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
    find_package(Tesseract QUIET)
    if(Tesseract_FOUND)
        message(STATUS "Tesseract:   YES")
        set(HAVE_TESSERACT 1)
        ocv_include_directories(${Tesseract_INCLUDE_DIR})
        ocv_target_link_libraries(${the_module} ${Tesseract_LIBRARIES})
    else()
        message(STATUS "Tesseract:   NO")
    endif()
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/text_config.hpp.in
    ${CMAKE_BINARY_DIR}/text_config.hpp @ONLY)

ocv_include_directories(${CMAKE_CURRENT_BINARY_DIR})

ocv_add_testdata(samples/ contrib/text
    FILES_MATCHING PATTERN "*.xml" PATTERN "*.xml.gz" REGEX "scenetext[0-9]+.jpg"
    )
