/* -*- c++ -*- */
/*
 * Copyright 2026 NL.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOM_MODULES_ACARS_SIG_GEN_H
#define INCLUDED_CUSTOM_MODULES_ACARS_SIG_GEN_H

#include <gnuradio/custom_modules/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace custom_modules {

    /*!
     * \brief <+description of block+>
     * \ingroup custom_modules
     *
     */
    class CUSTOM_MODULES_API acars_sig_gen : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<acars_sig_gen> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of custom_modules::acars_sig_gen.
       *
       * To avoid accidental use of raw pointers, custom_modules::acars_sig_gen's
       * constructor is in a private implementation
       * class. custom_modules::acars_sig_gen::make is the public interface for
       * creating new instances.
       */
      static sptr make(int sample_rate, const std::string &message);
    };

  } // namespace custom_modules
} // namespace gr

#endif /* INCLUDED_CUSTOM_MODULES_ACARS_SIG_GEN_H */
