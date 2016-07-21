#ifndef SEPARATOR_HPP
#define SEPARATOR_HPP

#include <set>

#include "CsvUtils.hpp"
#include "Geometry.hpp"


/**
 * Class to divide given points 
 * between set of spheres they belongs to.
 * @tparam D dimensionality of points
 */
template<int D>
class Separator {
public:
	typedef Point<D> PointD;
	
	Separator(const CsvUtils::Table& table, const real rMin_, const real rMax_) :
			rMin(rMin_), rMax(rMax_) {
		print("Number of given points: ", table.size());
		/// make sorted set of given points
		for (const auto& line : table) {
			points.insert(line);
		}
	}
	
	
	CsvUtils::Table separate() {
		
		estimateSpheres();
		separatePointsBetweenExistingSpheres(FirstGuessRadiusExtensionRatio);
		checkMissingPoints();
		
		int counter = 0;
		real radiusExtensionRatio = FirstGuessRadiusExtensionRatio;
		do {
			assert(++counter < 20);
			radiusExtensionRatio = 1 + (radiusExtensionRatio - 1) / 2;
			correctSpheresParameters(radiusExtensionRatio);
			separatePointsBetweenExistingSpheres(radiusExtensionRatio);
		} while (numberOfPointsInSpheres() != points.size());
		
		checkMissingPoints();
		return makeSeparatedTable();
	}
	
	
	
private:
	typedef std::set<PointD>              PointsSet;
	typedef typename PointsSet::iterator  PointIter;
	
	/// Extend radius of spheres on the first step of the algorithm
	/// in order to capture all points which the sphere owns.
	/// As far the distance between two spheres centers
	/// is more than bigger diameter, the sphere can't capture all
	/// another's points.
	static constexpr real FirstGuessRadiusExtensionRatio = 2;
	
	
	PointsSet points;             ///< lexicographically sorted points
	const real rMin, rMax;        ///< bounds on possible spheres radiuses
	std::list<Sphere<D>> spheres; ///< found spheres
	
	
	void estimateSpheres() {
	/// estimate existing spheres
		
		for (PointIter p = points.begin(); p != points.end(); ++p) {
		/// plane front propagation along x-axis
			
			bool sphereFound = false;
			for (auto& s : spheres) {
				if (s.contains(*p, FirstGuessRadiusExtensionRatio)) {
					/// containing sphere is already exist
					sphereFound = true;
					break;
				}
			}
			
			if ( !sphereFound ) {
			/// containing sphere does not exist yet
				Sphere<D> s;
				real radius = estimateRadius(p);
				s.radius = radius;
				/// sphere are in front of the point
				s.center = *p;
				s.center(0) += radius;
				spheres.push_back(s);
			}
		}
		
		print("Number of found spheres: ", spheres.size());
	}
	
	
	void separatePointsBetweenExistingSpheres(const real radiusExtensionRatio) {
	/// clean all spheres and separate points between them
		
		for (auto& s : spheres) {
			s.points.clear();
		}
		
		for (PointIter p = points.begin(); p != points.end(); ++p) {
			for (auto& s : spheres) {
				if (s.contains(*p, radiusExtensionRatio)) {
					s.points.push_back(*p);
				}
			}
		}
	}
	
	
	void checkMissingPoints() const {
		auto pointsCopy = points;
		for (const auto& s : spheres) {
			for (const auto p : s.points) {
				pointsCopy.erase(p);
			}
		}
		assert(pointsCopy.size() == 0);
	}
	
	
	void correctSpheresParameters(const real radiusExtensionRatio) {
	/// correct spheres properties
		for (auto& s : spheres) {
			s.removeOuterPoints(radiusExtensionRatio);
			s.recalculateCenter();
		}
	}
	
	
	size_t numberOfPointsInSpheres() const {
		size_t totalPointNumber = 0;
//		print("----------------------");
		for (const auto& s : spheres) {
//			print("Sphere: ", s.points.size(), s.center(0), s.center(1), s.center(2));
			totalPointNumber += s.points.size();
		}
//		print("----------------------");
		print("Total points number: ", totalPointNumber);
//		print("----------------------");
		return totalPointNumber;
	}
	
	
	
	real estimateRadius(const PointIter) const {
		return rMax;
	}
	
	
	
	CsvUtils::Table makeSeparatedTable() const {
		CsvUtils::Table table;
		int sphereNumber = 0;
		for (const auto& s : spheres) {
			for (const auto& p : s.points) {
				table.push_back(makeLineFromPoint(p, sphereNumber));
			}
			++sphereNumber;
		}
		return table;
	}
	
	
	CsvUtils::Line makeLineFromPoint(const PointD& p, const int sphereNumber) const {
		CsvUtils::Line line;
		line.push_back((real)p.getIndex());
		for (int i = 0; i < D; i++) {
			line.push_back(p(i));
		}
		line.push_back((real)sphereNumber);
		return line;
	}
	
};


#endif // SEPARATOR_HPP
