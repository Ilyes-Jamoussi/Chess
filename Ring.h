#pragma once

#include "Piece.h"
#include "LegalMovesShapes.h"

namespace interface {

    class Ring : public QObject, public QGraphicsEllipseItem, public LegalMovesShapes {
    public:

        explicit Ring(const model::Position& position, QGraphicsItem* parent = nullptr)
            : QObject(), QGraphicsEllipseItem(parent) {
            // Draw the circle using the provided position
            drawShape(position);
        }

        void drawShape(const model::Position& position) override {
            qreal x = position.getX() + StrokeWidth * position.getRank() + RingOffset;
            qreal y = position.getY() + StrokeWidth * position.getFile() + RingOffset;

            // Set the outer border for the ring
            this->qShapeRect_.setRect(x, y, RingSize, RingSize);
            setRect(this->qShapeRect_);

            // Set the pen style for the ring's outer edge
            setPen(LegalTakesRingPen);
        }

    private:
    };

}
