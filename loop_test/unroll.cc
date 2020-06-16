/*
 * Copyright (c) 2006 The Regents of The University of Michigan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Steve Reinhardt
 */

#include <iostream>

#include "layer.h"

using namespace std;

int main()
{
	cout << "Loop Unrolling Test(Unrolled)!" << endl;
	layer_t alex_conv_1(227, 227, 3, 11, 11, 96, 4, 1);
	layer_t &layer = alex_conv_1;
	
	//layer.print_stats();

	//for(unsigned k = 0; k < layer.K; k++) {
	cout << "Convolutional Layer Execution Start!(K=1, C=1)" << endl;
	for(unsigned k = 0; k < 1; k++) {
		for(unsigned oh = 0; oh < layer.OH; oh++) {
			for(unsigned ow = 0; ow < layer.OW; ow++) {
				//for(unsigned c = 0; c < layer.C; c++) {
				for(unsigned c = 0; c < 1; c++) {
					for(unsigned r = 0; r < layer.R; r ++) {
						for(unsigned s = 0; s < layer.S; s += 4) {
							unsigned h = oh * layer.stride + r;
							unsigned w = ow * layer.stride + s;
							*layer.output(ow, oh, k) += layer.input(w, h, c) * layer.filter(s + 0, r, c, k);
							*layer.output(ow, oh, k) += layer.input(w, h, c) * layer.filter(s + 1, r, c, k);
							*layer.output(ow, oh, k) += layer.input(w, h, c) * layer.filter(s + 2, r, c, k);
							*layer.output(ow, oh, k) += layer.input(w, h, c) * layer.filter(s + 3, r, c, k);
						}
					}
				}
			}
		}
	}
	
	cout << "Convolutional Layer Execution Finish!" << endl;
	//layer.print_output();

	return 0;
}
