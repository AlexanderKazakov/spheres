#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
#include <list>
#include <array>

#include "config.hpp"


/**
 * Struct represents a point in D-dimensional space
 */
template<int D>
struct Point {
	
	typedef std::array<real, D> Data; ///< coordinates array
	
	Point() {
		index = 0;
		for (int i = 0; i < D; i++) {
			(*this)(i) = 0;
		}
	}
	
	Point(const Data& data, const size_t index_ = 0) :
			p(data), index(index_) { }
	
	
	/**
	 * Construct point from vector. First value in vector is index
	 * and next ones are coordinates of the point.
	 */
	Point(const std::vector<real>& indexAndCoords) :
			index( (size_t)(indexAndCoords.at(0)) ) {
		assert(indexAndCoords.size() == D + 1);
		for (int i = 0; i < D; i++) {
			(*this)(i) = indexAndCoords[(size_t)i + 1];
		}
	}
	
	
	/// coordinates
	real  operator()(const int i) const { return p[(size_t)i]; }
	real& operator()(const int i)       { return p[(size_t)i]; }
	
	
	/**
	 * Lexicographical comparison
	 */
	bool operator<(const Point& other) const {
		for (int i = 0; i < D; i++) {
			if ( (*this)(i) < other(i) ) {
				return true;
			} else if ( (*this)(i) > other(i) ) {
				return false;
			}
		}
		return false;
	}
	

	
	Point& operator+=(const Point& other) {
		for (int i = 0; i < D; i++) {
			(*this)(i) += other(i);
		}
		return (*this);
	}
	
	
	Point operator-(const Point& other) const {
		Point ans;
		for (int i = 0; i < D; i++) {
			ans(i) = (*this)(i) - other(i);
		}
		return ans;
	}
	
	
	Point operator/(const real denominator) const {
		Point ans;
		for (int i = 0; i < D; i++) {
			ans(i) = (*this)(i) / denominator;
		}
		return ans;
	}
	
	
	real squaredLength() const {
		real ans = 0;
		for (int i = 0; i < D; i++) {
			ans += (*this)(i) * (*this)(i);
		}
		return ans;
	}
	
	
	size_t getIndex() const { return index; }
	
	
	
private:
	/// Data
	Data p;          ///< coordinates
	size_t index;    ///< number
	
	
};


/**
 * Struct represents a sphere in D-dimensional space
 */
template<int D>
struct Sphere {
	
	typedef Point<D> PointD;
	
	
	/**
	 * Is sphere contains the given point inside.
	 * @param radiusExtensionRatio extension of radius to prevent
	 * inexactness in center and radius estimation
	 */
	bool contains(const PointD& p, const real radiusExtensionRatio = 1) const {
		const real extendedRadius = radius * radiusExtensionRatio;
		return (p - center).squaredLength() <= extendedRadius * extendedRadius;
	}
	
	
	/**
	 * @see contains
	 * Remove all points which are not "contained"
	 */
	void removeOuterPoints(const real radiusExtensionRatio = 1) {
		auto p = points.begin();
		while (p != points.end()) {
			if (contains(*p, radiusExtensionRatio)) {
				++p;
			} else {
				p = points.erase(p);
			}
		}
	}
	
	
	/**
	 * Reestimate the center according to the stored points
	 */
	void recalculateCenter() {
		assert(points.size() > 0);
		
		PointD summ;
		for (int i = 0; i < D; i++) {
			summ(i) = 0;
		}
		
		for (const auto& p : points) {
			summ += p;
		}
		
		center = summ / (real)(points.size());
	}
	
	
	/// Data
	PointD               center;
	real                 radius = 0;
	std::list<PointD>    points; ///< captured points
	
};



#endif // POINT_HPP



