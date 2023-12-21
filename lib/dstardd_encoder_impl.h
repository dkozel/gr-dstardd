/* -*- c++ -*- */
/*
 * Copyright 2023 gr-dstardd author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSTARDD_DSTARDD_ENCODER_IMPL_H
#define INCLUDED_DSTARDD_DSTARDD_ENCODER_IMPL_H

#include <gnuradio/dstardd/dstardd_encoder.h>

namespace gr {
namespace dstardd {

class dstardd_encoder_impl : public dstardd_encoder {
private:
  // Nothing to declare in this block.

public:
  dstardd_encoder_impl();
  ~dstardd_encoder_impl();

  // Where all the action really happens
  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace dstardd
} // namespace gr

#endif /* INCLUDED_DSTARDD_DSTARDD_ENCODER_IMPL_H */
