/* -*- c++ -*- */
/*
 * Copyright 2023 gr-dstardd author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSTARDD_DSTARDD_DECODER_H
#define INCLUDED_DSTARDD_DSTARDD_DECODER_H

#include <gnuradio/dstardd/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dstardd {

/*!
 * \brief <+description of block+>
 * \ingroup dstardd
 *
 */
class DSTARDD_API dstardd_decoder : virtual public gr::sync_block {
public:
  typedef std::shared_ptr<dstardd_decoder> sptr;

  /*!
   * \brief Return a shared_ptr to a new instance of dstardd::dstardd_decoder.
   *
   * To avoid accidental use of raw pointers, dstardd::dstardd_decoder's
   * constructor is in a private implementation
   * class. dstardd::dstardd_decoder::make is the public interface for
   * creating new instances.
   */
  static sptr make();
};

} // namespace dstardd
} // namespace gr

#endif /* INCLUDED_DSTARDD_DSTARDD_DECODER_H */
