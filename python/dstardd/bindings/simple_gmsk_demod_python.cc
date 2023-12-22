/*
 * Copyright 2023 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually
 * edited  */
/* The following lines can be configured to regenerate this file during cmake */
/* If manual edits are made, the following tags should be modified accordingly.
 */
/* BINDTOOL_GEN_AUTOMATIC(0) */
/* BINDTOOL_USE_PYGCCXML(0) */
/* BINDTOOL_HEADER_FILE(simple_gmsk_demod.h) */
/* BINDTOOL_HEADER_FILE_HASH(da625b256a447a5b5fd384472f01505c) */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/dstardd/simple_gmsk_demod.h>
// pydoc.h is automatically generated in the build directory
#include <simple_gmsk_demod_pydoc.h>

void bind_simple_gmsk_demod(py::module &m) {

  using simple_gmsk_demod = gr::dstardd::simple_gmsk_demod;

  py::class_<simple_gmsk_demod, gr::block, gr::basic_block,
             std::shared_ptr<simple_gmsk_demod>>(m, "simple_gmsk_demod",
                                                 D(simple_gmsk_demod))

      .def(py::init(&simple_gmsk_demod::make), D(simple_gmsk_demod, make))

      ;
}
