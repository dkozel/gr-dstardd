/* -*- c++ -*- */
/*
 * Copyright 2023 gr-dstardd author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "simple_gmsk_demod_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace dstardd {

using input_type = gr_complex;
using output_type = char;

simple_gmsk_demod::sptr simple_gmsk_demod::make() {
  return gnuradio::make_block_sptr<simple_gmsk_demod_impl>();
}

/*
 * The private constructor
 */
simple_gmsk_demod_impl::simple_gmsk_demod_impl()
    : gr::block("simple_gmsk_demod",
          gr::io_signature::make(1, 1, sizeof(input_type)),
          gr::io_signature::make(1, 1, sizeof(output_type))) {}

/*
 * Our virtual destructor.
 */
simple_gmsk_demod_impl::~simple_gmsk_demod_impl() {}

#define SAMPLES_PER_BIT 4
    void
    simple_gmsk_demod_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
       ninput_items_required[0] = noutput_items*SAMPLES_PER_BIT;
    }

#define PLLMAX 10000U
#define PLLINC (PLLMAX/SAMPLES_PER_BIT)
#define INC (PLLINC/32*2)

    char
    simple_gmsk_demod_impl::procbit(int bit)
    {
      static int prevbit = 0;
      static int pll = 0;
      if(bit != prevbit) { 
          if(pll < PLLMAX/2U) { pll += INC; }
          else { pll -= INC; }
      }
      prevbit = bit;
      pll += PLLINC;
      if(pll > PLLMAX) {
         pll -= PLLMAX;
         return bit;
      }
      return -1; 
    }

int simple_gmsk_demod_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      int nout = 0;
      int i;
      int N = ninput_items[0]-1;
      gr_complex tmp[N];
      float demod[N];
      // FM demodulator
      for(i=0; i<N; i++) {
         tmp[i] = gr_complex(
            in[i].real()*in[i+1].real() + in[i].imag()*in[i+1].imag(),
            in[i+1].real()*in[i].imag() - in[i].real()*in[i+1].imag());
      }
      for(i=0; i<N; i++) {
         demod[i] = std::atan2(tmp[i].real(), tmp[i].imag());
      }
      // hard decision / block sync pll
      for(i=0; i<N-SAMPLES_PER_BIT; i++) {
         float bit=0;
         for(int j=0; j<SAMPLES_PER_BIT; j++) bit += demod[i+j];
         char b = procbit(bit<0);
	 if(b>=0) {
            out[nout] = b;
            nout++;
            if(nout>=noutput_items) break;
         }
      }
      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (i);

      // Tell runtime system how many output items we produced.
      return nout;
    }

} /* namespace dstardd */
} /* namespace gr */
