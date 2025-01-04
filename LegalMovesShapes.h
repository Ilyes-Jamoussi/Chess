#pragma once

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPainter>

#include "Piece.h"

namespace interface {
	class LegalMovesShapes {
	public:

		LegalMovesShapes() = default;
		virtual ~LegalMovesShapes() = default;

		virtual void drawShape(const model::Position& position) = 0;
		virtual  QRect getShapeQRect() const { return qShapeRect_; }
	protected:
		QPainter qPainter_;
		QRect qShapeRect_;
	};
}