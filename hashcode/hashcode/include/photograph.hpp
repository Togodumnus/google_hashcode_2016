#pragma once

#include "collection.hpp"

// necessary because of mutual inclusion
class collection;

class photograph{

	private:


	public:
		photograph();
		bool belongs_to_collection(collection&);

};
