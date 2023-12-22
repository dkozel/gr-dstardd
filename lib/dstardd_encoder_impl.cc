/* -*- c++ -*- */
/*
 * Copyright 2023 gr-dstardd author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dstardd_encoder_impl.h"
#include <gnuradio/io_signature.h>
#include "codec/dstardd.h"

namespace gr {
namespace dstardd {

using input_type = float;
using output_type = char;

dstardd_encoder::sptr dstardd_encoder::make(std::string my_call, std::string dst_call, std::string rptr1_call, std::string rptr2_call, bool verbose) {
  return gnuradio::make_block_sptr<dstardd_encoder_impl>(my_call, dst_call, rptr1_call, rptr2_call, verbose);
}

/*
 * The private constructor
 */
dstardd_encoder_impl::dstardd_encoder_impl(std::string my_call, std::string dst_call, std::string rptr1_call, std::string rptr2_call, bool verbose)
    : gr::block(
          "dstardd_encoder",
          gr::io_signature::make(0, 0, 0),
          gr::io_signature::make(1, 8*4096 , sizeof(output_type)))
          
          {
      mkheader();
      dstar_init();
      message_port_register_in(pmt::mp("pdu"));
      set_msg_handler(pmt::mp("pdu"), [this](pmt::pmt_t msg) {this->pdu(msg); });
      set_output_multiple(8*8192);  // large enough for large packet

      my_call.insert(0, 8 - my_call.length(), ' ');
      dst_call.insert(0, 8 - dst_call.length(), ' ');
      rptr1_call.insert(0, 8 - rptr1_call.length(), ' ');
      rptr2_call.insert(0, 8 - rptr2_call.length(), ' ');

      strcpy(d_my1, my_call.c_str());
      strcpy(d_your, dst_call.c_str());
      strcpy(d_rptr1, rptr1_call.c_str());
      strcpy(d_rptr2, rptr2_call.c_str());
      
          }

/*
 * Our virtual destructor.
 */
dstardd_encoder_impl::~dstardd_encoder_impl() {}

void dstardd_encoder_impl::mkheader() {
       d_header[0]=0x80;
       d_header[1]=d_header[2]=0;
       memcpy(d_header+3, d_rptr1, 8);
       memcpy(d_header+11, d_rptr2, 8);
       memcpy(d_header+19, d_your, 8);
       memcpy(d_header+27, d_my1, 8);
       memcpy(d_header+35, d_my2, 4);
    }


void dstardd_encoder_impl::pdu(pmt::pmt_t msg)
    {
       pmt::pmt_t vector = pmt::cdr(msg);
       size_t len = pmt::blob_length(vector);
       size_t offset = 0;
       unsigned char encoded[85+len+4 +16*4]; // +16: plus experiental padding
       len = dstar_encode(d_header, reinterpret_cast<const unsigned char*>(pmt::u8vector_elements(vector).data()), len, encoded);
       if(d_verbose) { 
	      dstar_printhead(d_header, len-85, 1);
       }
      
       boost::lock_guard<gr::thread::mutex> lock{d_mutex};
       if(d_encoded_ready) { 
	       std::cout << "Encoded buffer overflow - dropping message\n";
	       std::cout << "(left bytes is "<<d_encoded_ready<<")\n";
       }
       // 01-Sequence and Sync 
       memset(d_encoded, 0x55, d_prefixlen);
       memcpy(d_encoded+d_prefixlen, "\x76\x50", 2);
       memcpy(d_encoded+d_prefixlen+2, encoded, len);
       d_encoded_ready = d_prefixlen + 2 + len;
       d_cond.notify_one(); 
    }
    
int dstardd_encoder_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      unsigned char *out= (unsigned char *) output_items[0];

      boost::unique_lock<boost::mutex> lock(d_mutex);
      if(!d_encoded_ready) { d_cond.timed_wait(lock, boost::posix_time::milliseconds(10)); }
      if(!d_encoded_ready) { return 0; }

      /* Process output data from d_encoded */
      if(noutput_items < d_encoded_ready + 2 + d_prefixlen/8) {
         std::cout << "noutput_items: " << noutput_items << " vs needed: " << 
		 (d_encoded_ready+2+d_prefixlen/8) << "\n";
         d_encoded_ready=0;
         return 0; // TODO FIXME -- should never happen
      }
      std::cout << "TX: Output of a block w/ " << d_encoded_ready << " bytes\n";
      memcpy(out, d_encoded, d_encoded_ready);
      noutput_items = d_encoded_ready;
      d_encoded_ready=0;
      return noutput_items;
    }


} /* namespace dstardd */
} /* namespace gr */
