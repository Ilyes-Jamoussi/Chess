#pragma once
#include <Qobject>
#include <QGraphicsRectItem>

#include "LibConstants.h"
#include "Piece.h"
#include "Color.h"

namespace interface {
	class Image : public QObject, public QGraphicsRectItem {
	public:
		Image() = default;
		Image(const std::shared_ptr<model::Piece> piece);

		void updateImage(const std::shared_ptr<model::Piece> piecee);
		void setPath(const std::shared_ptr<model::Piece> piece);

		QGraphicsPixmapItem& getQtPixmap();
		model::Position getImagePosition() const;

		~Image() = default;
	private:
		QImage image_;
		QString imagePath_ = "";
		QGraphicsPixmapItem pixmap_;
		model::Position position_;
	};

}