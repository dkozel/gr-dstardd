/* -*- c++ -*- */
/*
 * Copyright 2023 gr-dstardd author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSTARDD_SIMPLE_GMSK_DEMOD_IMPL_H
#define INCLUDED_DSTARDD_SIMPLE_GMSK_DEMOD_IMPL_H

#include <gnuradio/dstardd/simple_gmsk_demod.h>

namespace gr {
namespace dstardd {

class simple_gmsk_demod_impl : public simple_gmsk_demod {
private:
  // Nothing to declare in this block.

public:
  simple_gmsk_demod_impl();
  ~simple_gmsk_demod_impl();

  // Where all the action really happens
  int work(int noutput_items, gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace dstardd
} // namespace gr

#endif /* INCLUDED_DSTARDD_SIMPLE_GMSK_DEMOD_IMPL_H */
