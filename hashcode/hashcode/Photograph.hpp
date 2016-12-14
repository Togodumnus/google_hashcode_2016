#pragma once

#include <string>
#include <vector>
#include <array>
#include <ostream>

#include "Location.hpp"
#include "Collection.hpp"

using PhotographLine = std::array<std::string, 2>;

class Collection;
struct Shoot;

/**
 * Photograph
 */
class Photograph : public Location {
	private:
		int m_id;
		Shoot* m_shoot = nullptr;

		/**
		 * collections the photograph belongs to
		 */
		std::vector<Collection*> m_collections;

		friend std::ostream& operator<<(std::ostream&, const Photograph&);

	public:
		explicit Photograph(int, PhotographLine);
		virtual ~Photograph();
		Photograph& operator=(const Photograph& photograph);
		explicit Photograph(const Photograph&);

		bool addToCollection(Collection*);

		inline int getId() const {
			return m_id;
		}

		inline Shoot* getShoot() {
			return m_shoot;
		}

		inline void setShoot(Shoot* shoot) {
			m_shoot = shoot;
		}

		bool isInTimeRanges(unsigned long int);
};
