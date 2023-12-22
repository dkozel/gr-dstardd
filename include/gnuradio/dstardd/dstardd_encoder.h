/* -*- c++ -*- */
/*
 * Copyright 2023 gr-dstardd author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSTARDD_DSTARDD_ENCODER_H
#define INCLUDED_DSTARDD_DSTARDD_ENCODER_H

#include <gnuradio/dstardd/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dstardd {

/*!
 * \brief <+description of block+>
 * \ingroup dstardd
 *
 */
class DSTARDD_API dstardd_encoder : virtual public gr::block {
public:
  typedef std::shared_ptr<dstardd_encoder> sptr;

  /*!
   * \brief Return a shared_ptr to a new instance of dstardd::dstardd_encoder.
   *
   * To avoid accidental use of raw pointers, dstardd::dstardd_encoder's
   * constructor is in a private implementation
   * class. dstardd::dstardd_encoder::make is the public interface for
   * creating new instances.
   */
  static sptr make(bool verbose);
};

} // namespace dstardd
} // namespace gr

#endif /* INCLUDED_DSTARDD_DSTARDD_ENCODER_H */
