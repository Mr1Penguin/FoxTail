#pragma once

#include <iterator>
#include <vector>
#include <nanorange.hpp>

namespace FoxTail {
	template<class T, class P, class F>
	auto replace_or_push_back(std::vector<T> & vec, P pred, F factory) {
		auto it = nano::find_if(vec, pred);
		if (it == vec.end()) {
			vec.push_back(factory());
			return false;
		}
		else {
			*it = factory();
			return true;
		}
	}

	template<class T, class P, class F>
	auto find_if_or_push_back(std::vector<T> & vec, P pred, F factory) {
		auto it = nano::find_if(vec, pred);
		if (it == vec.end()) {
			vec.push_back(factory());
			it = vec.end() - 1;
		}
		
		return it;
	}
}