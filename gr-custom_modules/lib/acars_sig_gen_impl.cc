/* -*- c++ -*- */
/*
 * Copyright 2026 NL.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "acars_sig_gen_impl.h"

namespace gr {
  namespace custom_modules {

    using output_type = gr_complex;
    acars_sig_gen::sptr
    acars_sig_gen::make(int sample_rate, const std::string &message)
    {
      return gnuradio::make_block_sptr<acars_sig_gen_impl>(
        sample_rate, message);
    }


    /*
     * The private constructor
     */
    acars_sig_gen_impl::acars_sig_gen_impl(int sample_rate, const std::string &message)
      : gr::sync_block("acars_sig_gen",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(1 /* min outputs */, 1 /*max outputs */, sizeof(output_type))),
        d_sample_rate(sample_rate),
        d_bit_index(0),
        d_sample_index(0),
        d_sample_count(0),
        d_phase(0.0f)
    {
      int baud_rate = 1200;
      d_samples_per_bit = d_sample_rate / baud_rate;

      std::vector<int> prekey = {0,1,1,1,1,1,1,1};
      for(int i = 0; i < 16; ++i) {
          d_message.insert(d_message.end(), prekey.begin(), prekey.end());
      }

      std::vector<int> payload = generate_bit_message(message);
      d_message.insert(d_message.end(), payload.begin(), payload.end());
    }

    /*
     * Our virtual destructor.
     */
    acars_sig_gen_impl::~acars_sig_gen_impl()
    {
    }

    // generates a bit message from string
    std::vector<int> 
    acars_sig_gen_impl::generate_bit_message(const std::string &message) {
        std::vector<int> out_stream;

        for (char charact : message) {
            int value = static_cast<int>(charact);

            if (value > 127) {
                throw std::runtime_error("outside 7-bit range");
            }

            for (int i = 0; i < 7; i++) {
                int bit = (value >> i) & 1;
                out_stream.push_back(bit);
            }
        }

        return out_stream;
    }

    int
    acars_sig_gen_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      auto out = static_cast<output_type*>(output_items[0]);

      int total_cycle_samples = d_sample_rate * 8;

      // if message is not fully sent or the clock run out i.e. sample count is more than 8*sample rate i.e. 8 seconds
      // > keep sending message bits

      for (int i = 0; i < noutput_items; i++) {
          if (d_sample_count > (total_cycle_samples - (d_samples_per_bit * d_message.size())) && d_bit_index < d_message.size()) {
              int current_bit = d_message[d_bit_index];
              float freq = (current_bit == 1) ? 1200.0f : 2400.0f;

              d_phase += 2.0f * M_PI * freq / d_sample_rate;
              if (d_phase > 2.0f * M_PI) d_phase -= 2.0f * M_PI;

              out[i] = std::polar(1.0f, d_phase);

              // progress to nex bit
              d_sample_index++;
              if (d_sample_index >= d_samples_per_bit) {
                  d_sample_index = 0;
                  d_bit_index++;
              }
          } else {
              // radio silence before sending message again
              out[i] = std::polar(0.0f, 0.0f);
          } 
          d_sample_count++;

          // if samples over 8*samplerate
          if (d_sample_count > total_cycle_samples) {
              d_bit_index = 0;
              d_sample_index = 0;
              d_sample_count = 0;
              d_phase = 0.0f;
          }
      }
      return noutput_items;
    }

  } /* namespace custom_modules */
} /* namespace gr */
