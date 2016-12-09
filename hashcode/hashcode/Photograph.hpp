#pragma once

#include <string>
#include <vector>
#include <array>
#include <ostream>

#include "Location.hpp"

using PhotographLine = std::array<std::string, 2>;

class Collection;
struct Shoot;

/**
 * Photograph
 */
class Photograph : public Location {
	private:
		Shoot* m_shoot = nullptr;

		/**
		 * collections the photograph belongs to
		 */
		std::vector<Collection*> m_collections;

		friend std::ostream& operator<<(std::ostream&, const Photograph&);

	public:
		explicit Photograph(PhotographLine);
		explicit Photograph(LocationUnit latitude, LocationUnit longitude);
		virtual ~Photograph();
		Photograph& operator=(const Photograph& photograph);
		Photograph(const Photograph& photograph);

		bool addToCollection(Collection*);

		inline Shoot* getShoot() {
			return m_shoot;
		}

		inline void setShoot(Shoot* shoot) {
			m_shoot = shoot;
		}
};
