# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT dstardd_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT dstardd_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND dstardd_python_files
    dstardd_decoder_python.cc
    dstardd_encoder_python.cc
    simple_gmsk_demod_python.cc python_bindings.cc)

gr_pybind_make_oot(dstardd ../../.. gr::dstardd "${dstardd_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET dstardd_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:dstardd_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/dstardd/)

install(
    TARGETS dstardd_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/dstardd
    COMPONENT pythonapi)
