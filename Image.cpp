#include "Image.h"
#include <iostream>


namespace interface {
	Image::Image(const std::shared_ptr<model::Piece> piece) { updateImage(piece); }

	void Image::updateImage(const std::shared_ptr<model::Piece> piece) {
		this->setPath(piece);
		if (piece != nullptr) {
			image_ = QImage(imagePath_);
			this->pixmap_.setPixmap(imagePath_);
			Coordinates updatedCoordinates = { piece->getPosition().getRank(), piece->getPosition().getFile() };
			qreal x = updatedCoordinates.getX() + constants::StrokeWidth * piece->getPosition().getRank();
			qreal y = updatedCoordinates.getY() + constants::StrokeWidth * piece->getPosition().getFile();
			this->pixmap_.setPos(x, y);
			pixmap_.show();
			this->position_ = piece->getPosition();
		}
	}

	void Image::setPath(const std::shared_ptr<model::Piece> piece) {
		if (piece == nullptr) { 
			this->imagePath_ = "";
			return;
		}

		constants::Type type = piece->getType();
		std::string colorString = piece->getColor().toString();
		QString qstrColor = colorString.c_str();

		switch (type) {
		case constants::KING:
			this->imagePath_ = "images/" + qstrColor + "King.png";
			break;
		case constants::BISHOP:
			this->imagePath_ = "images/" + qstrColor + "Bishop.png";
			break;
		case constants::ROOK:
			this->imagePath_ = "images/" + qstrColor + "Rook.png";
			break;
		}
	}

	QGraphicsPixmapItem& Image::getQtPixmap() { return pixmap_; }
	
	model::Position Image::getImagePosition() const {
		return position_;
	}
}


