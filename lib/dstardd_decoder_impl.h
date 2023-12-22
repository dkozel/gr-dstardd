/* -*- c++ -*- */
/*
 * Copyright 2023 gr-dstardd author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSTARDD_DSTARDD_DECODER_IMPL_H
#define INCLUDED_DSTARDD_DSTARDD_DECODER_IMPL_H

#include <gnuradio/dstardd/dstardd_decoder.h>

enum { DSTAR_SYNC, DSTAR_HEAD, DSTAR_DATA };
#define DSTAR_SYNC_MASK 0x00FFFFFFU
#define DSTAR_SYNC_FLAG 0x00557650U
#define DSTAR_HEADBITS (660+16)
#define DSTAR_MAXDATA 4096

namespace gr {
namespace dstardd {

class dstardd_decoder_impl : public dstardd_decoder {
private:
      bool d_verbose;
      int d_state;
      int d_pattern;
      int d_bitcount;
      unsigned char d_headbits[DSTAR_HEADBITS];
      unsigned char d_data[DSTAR_MAXDATA];
      int d_datalen;

public:
  dstardd_decoder_impl(bool verbose);
  ~dstardd_decoder_impl();

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace dstardd
} // namespace gr

#endif /* INCLUDED_DSTARDD_DSTARDD_DECODER_IMPL_H */
