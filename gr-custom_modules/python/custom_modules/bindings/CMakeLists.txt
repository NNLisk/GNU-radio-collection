# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT custom_modules_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT custom_modules_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND custom_modules_python_files
    acars_sig_gen_python.cc python_bindings.cc)

gr_pybind_make_oot(custom_modules ../../.. gr::custom_modules "${custom_modules_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET custom_modules_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:custom_modules_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/custom_modules/)

install(
    TARGETS custom_modules_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/custom_modules
    COMPONENT pythonapi)
