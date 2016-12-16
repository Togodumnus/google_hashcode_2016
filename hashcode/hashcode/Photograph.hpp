#pragma once

#include <string>
#include <vector>
#include <array>
#include <ostream>
#include <numeric>

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
	explicit Photograph(LocationUnit latitude, LocationUnit longitude);
	virtual ~Photograph();
	Photograph& operator=(const Photograph& photograph);
	Photograph(const Photograph& photograph);

	bool addToCollection(Collection*);

	std::vector<Collection*>& getCollections() {
		return m_collections;
	}

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

	//for multiindex
	inline LocationUnit getLatitude() const {
		return m_latitude;
	}
	inline LocationUnit getLongitude() const {
		return m_longitude;
	}

	inline unsigned int getValue() const {
			return std::accumulate(
				m_collections.begin(), m_collections.end(),
				0,
				[](unsigned int s, Collection* c) {
					return s + c->getValue();
				}
			);
		}
};
