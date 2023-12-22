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
      bool d_verbose;
      unsigned char d_header[41];
      char d_my1[9]="DL9RDZ  ";
      char d_my2[5]="SDR ";
      char d_your[9]="CQCQCQ  ";
      char d_rptr1[9]="DB0VOX A";
      char d_rptr2[9]="DB0VOX G";

      int d_prefixlen=64;  // bytes, i.e. 16 byte=128 bit
      char d_encoded[64/*16*/+85+4+4000];
      int d_encoded_ready=0;

      boost::mutex d_mutex;
      boost::condition_variable_any d_cond;

      void pdu(pmt::pmt_t msg);
      void mkheader();


public:
  dstardd_encoder_impl(bool verbose);
  ~dstardd_encoder_impl();

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

} // namespace dstardd
} // namespace gr

#endif /* INCLUDED_DSTARDD_DSTARDD_ENCODER_IMPL_H */
