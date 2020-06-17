#include <iostream>

#include "layer.h"

using namespace std;

int main()
{
	cout << "Loop Unrolling Test(Unrolled)!" << endl;
	layer_t alex_conv_1(227, 227, 3, 11, 11, 96, 4, 1);
	layer_t &layer = alex_conv_1;
	
	//layer.print_stats();

	cout << "Convolutional Layer Execution Start!" << endl;
	for(unsigned k = 0; k < layer.K; k++) {
		for(unsigned oh = 0; oh < layer.OH; oh++) {
			for(unsigned ow = 0; ow < layer.OW; ow++) {
				for(unsigned c = 0; c < layer.C; c++) {
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
