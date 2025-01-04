#include "Color.h"

namespace model {
	Color::Color() = default;
	Color::Color(std::string color) :color_(color) {}
		
	bool Color::operator== (const Color& autre) const { return color_ == autre.color_; }
	bool Color::operator!= (const Color& autre) const { return color_ != autre.color_; }
	std::string Color::toString() const { return this->color_;}
}