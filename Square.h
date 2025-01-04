#pragma once
#ifndef Square_H
#define Square_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QGraphicsView>
#include <QRectF>
#include <QMouseEvent>
#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>
#include <QGraphicsSceneMouseEvent>

#include "Position.h"
#include "Piece.h"

namespace interface {
	class Square : public QObject, public QGraphicsRectItem{
		Q_OBJECT;
	public:
		Square() = delete;
		Square(model::Position position);

		void resetSquareColor();
		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		void updateSquareImage(const model::Piece* piece);
		void changeColor(const QColor& squareColor, const QPen& StrokePen);

		QGraphicsPixmapItem& getImageQtPixmap();
		QBrush getQColor() const;
		QRect getQRect() const;
		model::Position getPosition() const;

	private:
		QBrush qBrush_;
		const model::Position position_;
		QRect qSquare_;
		QPainter qPainter_;

	signals:
		void SquareSelected(const int /*rank*/, const int /*file*/);
		void SquareDeselected(const int /*rank*/, const int /*file*/);
	};
}

#endif