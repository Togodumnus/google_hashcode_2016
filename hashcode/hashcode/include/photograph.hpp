#pragma once

#include "collection.hpp"
#include <vector>
// necessary because of mutual inclusion
class collection;

class photograph{

	private:
	std::vector<collection*> m_collections;

	public:
		photograph();
		bool belongs_to_collection(collection&);

};
