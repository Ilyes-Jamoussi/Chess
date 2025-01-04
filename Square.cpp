#include "Square.h"


using namespace constants;
namespace interface {

	Square::Square(model::Position position)
		: position_(position) {
		resetSquareColor();
		qreal x = position.getX() + StrokeWidth * position.getRank();
		qreal y = position.getY() + StrokeWidth * position.getFile();
		qSquare_.setRect(x, y, TileWidth, TileHeight);

		setRect(this->getQRect());
		setBrush(this->getQColor());
	}

	void Square::resetSquareColor() {
		QPen pen = (position_.isSumEven()) ? Tile1Color : Tile2Color;
		setPen(pen);
		qBrush_ = position_.isSumEven() ? Tile1Color : Tile2Color;
	}

	void Square::mousePressEvent(QGraphicsSceneMouseEvent* event) {
		if (event->button() == Qt::LeftButton) {
				emit SquareSelected(position_.getRank(), position_.getFile());
		}
	}

	void Square::changeColor(const QColor& squareColor,const QPen& StrokePen) {
		setPen(StrokePen);
		qBrush_ = squareColor;
	}

	QBrush Square::getQColor() const {
		return qBrush_;
	}

	QRect Square::getQRect() const {
		return qSquare_;
	}

	 model::Position Square::getPosition() const { 
		return position_; }
}


