#ifndef Coordinates_H
#define Coordinates_H
#include "LibConstants.h"	


namespace interface {
	struct Coordinates {
		Coordinates(int rank, int file) : x_(rank * constants::TileWidth), y_(file * constants::TileHeight) {};

		void setCoordinates(int file, int rank) {
			x_ = rank * constants::TileWidth;
			y_ = file * constants::TileHeight;
		}

		int getX() const { return x_; }
		int getY() const { return y_; }
	private:
		int x_, y_;
	};
};

#endif
