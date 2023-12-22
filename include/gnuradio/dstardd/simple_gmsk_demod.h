/* -*- c++ -*- */
/*
 * Copyright 2023 gr-dstardd author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DSTARDD_SIMPLE_GMSK_DEMOD_H
#define INCLUDED_DSTARDD_SIMPLE_GMSK_DEMOD_H

#include <gnuradio/dstardd/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dstardd {

/*!
 * \brief <+description of block+>
 * \ingroup dstardd
 *
 */
class DSTARDD_API simple_gmsk_demod : virtual public gr::block {
public:
  typedef std::shared_ptr<simple_gmsk_demod> sptr;

  /*!
   * \brief Return a shared_ptr to a new instance of dstardd::simple_gmsk_demod.
   *
   * To avoid accidental use of raw pointers, dstardd::simple_gmsk_demod's
   * constructor is in a private implementation
   * class. dstardd::simple_gmsk_demod::make is the public interface for
   * creating new instances.
   */
  static sptr make();
};

} // namespace dstardd
} // namespace gr

#endif /* INCLUDED_DSTARDD_SIMPLE_GMSK_DEMOD_H */
