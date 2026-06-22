"""
Embedded Python Blocks:

Each time this file is saved, GRC will instantiate the first class it finds
to get ports and parameters of your block. The arguments to __init__  will
be the parameters. All of them are required to have default values!
"""

import math

import numpy as np
from gnuradio import gr


class blk(gr.sync_block):

    def __init__(self, sample_rate=32000):
        gr.sync_block.__init__(
            self,
            name='ACARS SIGNAL SIMULATOR',
            in_sig=None,
            out_sig=[np.complex64]
        )

        self.sample_rate = sample_rate
        self.prekey = [0,1,1,1,1,1,1,1] * 16
        self.baud_rate = 1200

        self.samples_per_bit = int(self.sample_rate / self.baud_rate)


        self.sample_counter = 0
        self.bit_index = 0
        self.sample_index = 0
        self.phase = 0.0

        self.silence_duration = self.sample_rate * 4

    def work(self, input_items, output_items):
        
        output_size = len(output_items[0])
        total_cycle_samples = self.sample_rate * 4
        
        for i in range(output_size):
            
            if self.sample_counter >= (total_cycle_samples - (self.samples_per_bit * len(self.prekey))) and self.bit_index < len(self.prekey):

                current_bit = self.prekey[self.bit_index]
                freq = 1200.0 if current_bit == 1 else 2400.0
                self.phase += 2*math.pi * freq / self.sample_rate
                if self.phase > 2*math.pi:
                    self.phase -= 2*math.pi

                output_items[0][i] = complex(math.cos(self.phase), math.sin(self.phase))

                self.sample_index += 1
                if self.sample_index >= self.samples_per_bit:
                    self.sample_index = 0
                    self.bit_index += 1

                # if self.bit_index >= len(self.prekey):
                #     self.bit_index = 0

            else:
                output_items[0][i] = complex(0.0, 0.0)

            self.sample_counter += 1

            if self.sample_counter >= total_cycle_samples:
                self.sample_counter = 0
                self.bit_index = 0
                self.sample_index = 0
                self.phase = 0.0
                
        return output_size


