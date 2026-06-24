/* -*- c++ -*- */
/*
 * Copyright 2026 NL.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOM_MODULES_ACARS_SIG_GEN_IMPL_H
#define INCLUDED_CUSTOM_MODULES_ACARS_SIG_GEN_IMPL_H

#include <gnuradio/custom_modules/acars_sig_gen.h>

namespace gr {
  namespace custom_modules {

    class acars_sig_gen_impl : public acars_sig_gen
    {
     private:
        int d_sample_rate;
        std::vector<int> d_message;
        int d_samples_per_bit;

        int d_sample_count;
        unsigned int d_bit_index; 
        int d_sample_index;
        float d_phase;

        std::vector<int> generate_bit_message(const std::string &text_string);

     public:
      acars_sig_gen_impl(int sample_rate, const std::string &message);
      ~acars_sig_gen_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace custom_modules
} // namespace gr

#endif /* INCLUDED_CUSTOM_MODULES_ACARS_SIG_GEN_IMPL_H */
