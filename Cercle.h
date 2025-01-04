#pragma once

#include "LegalMovesShapes.h"

using namespace constants;

namespace interface {

    class Circle : public QObject, public QGraphicsEllipseItem, public LegalMovesShapes {
    public:
        explicit Circle(const model::Position& position, QGraphicsItem* parent = nullptr)
            : QObject(), QGraphicsEllipseItem(parent), qBrush_(LegalMovesCircleColor) {
            // Draw the circle using the provided position
            drawShape(position);
        }

        void drawShape(const model::Position& position) override {
            qreal x = position.getX() + StrokeWidth * position.getRank() + CircleOffset;
            qreal y = position.getY() + StrokeWidth * position.getFile() + CircleOffset;
            

            // Set the rectangle of the ellipse
            this->qShapeRect_.setRect(x, y, CircleSize, CircleSize);
            setRect(this->qShapeRect_);

            // Set the pen style and brush color for the circle
            setPen(Qt::NoPen);
            setBrush(qBrush_);
        }

        QBrush getBrush() const { return qBrush_; }

    private:
        QBrush qBrush_; // Brush representing the color of the circle
    };

}
