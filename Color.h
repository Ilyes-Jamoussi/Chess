#ifndef Color_H
#define Color_H

#include <string>

namespace model {
	class Color {
	public:
		Color(std::string color);
		Color();

		bool operator== (const Color& autre) const;
		bool operator!= (const Color& autre) const;

		std::string toString() const;
	private:
		std::string color_ = "None";
	};
}


#endif