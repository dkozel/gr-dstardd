/* -*- c++ -*- */
/*
 * Copyright 2023 gr-dstardd author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dstardd_decoder_impl.h"
#include <gnuradio/io_signature.h>
#include "codec/dstardd.h"

namespace gr {
namespace dstardd {

using input_type = float;
using output_type = float;

dstardd_decoder::sptr dstardd_decoder::make(bool verbose) {
  return gnuradio::make_block_sptr<dstardd_decoder_impl>(verbose);
}

/*
 * The private constructor
 */
dstardd_decoder_impl::dstardd_decoder_impl(bool verbose)
    : gr::block(
          "dstardd_decoder",
          gr::io_signature::make(1, 1, sizeof(input_type)),
          gr::io_signature::make(0, 0, 0))
    {
        dstar_init();
        d_state = DSTAR_SYNC;
        d_verbose = 1;
        message_port_register_out(pmt::mp("pdu"));
    }

/*
 * Our virtual destructor.
 */
dstardd_decoder_impl::~dstardd_decoder_impl() {}

int dstardd_decoder_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
  {
  const char *in = (const char *) input_items[0];
      for(int i=0; i<ninput_items[0]; i++) {
         if(d_state==DSTAR_SYNC) { 
            d_pattern = (d_pattern<<1) | (in[i]&1);
            if((d_pattern&DSTAR_SYNC_MASK)==DSTAR_SYNC_FLAG) {
               d_state = DSTAR_HEAD;
               d_bitcount = 0;
            }
         }
         else if (d_state==DSTAR_HEAD) {
            d_headbits[d_bitcount++] = in[i]&1;
            if(d_bitcount>=DSTAR_HEADBITS) {
               d_state = DSTAR_DATA;
               d_bitcount = 0;
               unsigned char head[HEADBITS/8+1];
               d_datalen = dstar_decode_head(d_headbits, head);
               if(d_verbose) { dstar_printhead(head, d_datalen, 0); }
	       if(d_datalen<0) {
		       	// Invalid header CRC
		  d_state = DSTAR_SYNC;
	       } else {
                  d_datalen = (d_datalen + 4) * 8;   // bits, including 4 byte CRC
	       }
            }
         }
         else if (d_state==DSTAR_DATA) { 
            if((d_bitcount&7)==0) d_data[d_bitcount>>3] = 0;
            d_data[d_bitcount>>3] |= (in[i] << (d_bitcount&7));
            d_bitcount++;
            if(d_bitcount >= d_datalen) {
               unsigned char ethframe[d_bitcount/8];
               dstar_decode_data(d_data, d_bitcount/8, ethframe);
               pmt::pmt_t vector = pmt::init_u8vector(d_bitcount/8, ethframe);
               pmt::pmt_t pdu = pmt::cons(pmt::PMT_NIL, vector);
               message_port_pub(pmt::mp("pdu"), pdu);
               d_state = DSTAR_SYNC;
            }
         }
      }
      
      consume_each(ninput_items[0]);
      return 0;
}

} /* namespace dstardd */
} /* namespace gr */
