#ifndef __LAYER_H_
#define __LAYER_H_

#include <cassert>
#include <iostream>
#include <iomanip>

class layer_t {
public: 
	layer_t(unsigned H_, unsigned W_, unsigned C_, 
			unsigned R_, unsigned S_, unsigned K_, 
			unsigned stride, unsigned padding) 
	: H(H_), W(W_), C(C_), 
	  R(R_), S(S_), K(K_), 
	  stride(stride), padding(padding) {
		OH = (H - R + 2 * padding) / stride + 1;
		OW = (W - S + 2 * padding) / stride + 1;
		input_size = H * W * C;
		filter_size = R * S * C;
		filters_size = filter_size * K;
		output_size = OH * OW * K; 
		total_size = input_size + filters_size + output_size;
		init_data();	
	}

	~layer_t() {
		fin_data();
	}

	void init_data() {
		zero = new float;
		input_data = new float[input_size];
		filters_data = new float[filters_size];
		output_data = new float[output_size]();
		for(unsigned i = 0; i < input_size; i++) { input_data[i] = 1; }
		for(unsigned i = 0; i < filters_size; i++) { filters_data[i] = 1; }
	}
	void fin_data() {
		delete zero;
		delete [] input_data;
		delete [] filters_data;
		delete [] output_data;
	}

	float input(unsigned w_, unsigned h_, unsigned c_) {
		unsigned idx = w_ + W * (h_ + H * c_);
		assert(idx <= input_size);
		if(w_ >= W || h_ >= H || c_ >= C)
			return 0;
		else
			return input_data[idx];
	}

	float filter(unsigned s_, unsigned r_, unsigned c_, unsigned k_) {
		unsigned idx = s_ + S * (r_ + R * (c_ + C * k_));
		assert(idx <= filters_size);
		if(s_ >= S || r_ >= R || c_ >= C || k_ >= K)
			return 0;
		else
			return filters_data[idx];
	}

	float* output(unsigned ow_, unsigned oh_, unsigned k_) {
		unsigned idx = ow_ + OW * (oh_ + OH * k_);
		assert(idx <= output_size);
		if(ow_ >= OW || oh_ >= OH || k_ >= K)
			return zero;
		else
			return output_data + idx;
	}

	unsigned H;
	unsigned W;
	unsigned C;
	unsigned R;
	unsigned S;
	unsigned K;
	unsigned stride;
	unsigned padding;
	unsigned OH;
	unsigned OW;
	
	unsigned input_size;
    unsigned filter_size;
    unsigned filters_size;
    unsigned output_size;
    unsigned total_size;

	float *input_data;
	float *filters_data;
	float *output_data;
	float *zero;

	void print_stats();
	void print_output();
};

void layer_t::print_stats() {
	std::cout << "\n***************************** Layer Stats *****************************" << std::endl;
	std::cout << "H\tW\tC\tR\tS\tK\tOH\tOW" << std::endl;
	std::cout <<  H << "\t" << W << "\t" << C << "\t" << R  << "\t" << S << "\t" << K << "\t" << OH << "\t" << OW << "\n" << std::endl;
	std::cout << "Stride\tPadding" << std::endl;
	std::cout << stride << "\t" << padding << "\n" << std::endl;
	std::cout << "Total # of multiplication operations(R x S x C x OH x OW x K): " << filter_size * output_size << "\n" << std::endl;
	std::cout << "# of data in an tiled input(H x W x C): " << input_size << std::endl;
	std::cout << "An tiled input size: " << std::fixed << std::setprecision(2) << input_size*4.0/1024 << " KB\n" << std::endl;
	std::cout << "# of data in a tiled filter(R x S x C): " << filter_size << std::endl;
	std::cout << "A tiled filter size:  " << std::fixed << std::setprecision(2) << filter_size*4.0/1024 << " KB\n" << std::endl;
	std::cout << "Total # of tiled flter data(R x S x C x K): " << filters_size << std::endl;
	std::cout << "Total tiled filters size: " << std::fixed << std::setprecision(2) << filters_size*4.0/1024 << " KB\n" << std::endl;
	std::cout << "# of data in an tiled output(OH x OW x K): " << output_size << std::endl;
	std::cout << "An tiled output size: " << std::fixed << std::setprecision(2) << output_size*4.0/1024 << " KB\n" << std::endl;
	std::cout << "Total tiled data size(KB): " << std::fixed << std::setprecision(2) << total_size*4.0/1024 << " KB" << std::endl;
	std::cout << "Total tiled data size(MB): " << std::fixed << std::setprecision(2) << total_size*4.0/1024/1024 << " MB" << std::endl;
	std::cout << "***********************************************************************" << std::endl;
}

void layer_t::print_output() {
	for(unsigned k = 0; k < 1; k++) {
		std::cout << "K: " << k << std::endl;
		for(unsigned oh = 0; oh < OH; oh++) {
			for(unsigned ow = 0; ow < OW; ow++) {
				std::cout << *output(ow, oh, k) << " ";	
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

#endif
