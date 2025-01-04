#pragma once

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>
#include <string>
#include <QPen>


namespace constants {

    enum Type { KING, ROOK, BISHOP, EMPTY };

    enum class GameTag {
        EmptyGame,
        TopalovVsPolgar2008,
        BudnikovVsNovik1991,
        VladimorovVsPalatnik1977,
    };

    // Board size constants
    constexpr int BoardWidth = 8;
    constexpr int BoardHeight = 8;

    // Colors
    static inline const std::string White = "White";
    static inline const std::string Black = "Black";
    static inline const std::string None = "None";

    // Graphics scene positioning and sizing
    constexpr int SceneXPos = 10;
    constexpr int SceneYPos = 10;
    constexpr int SceneWidth = 420;
    constexpr int SceneHeight = 420;

    // Chess tile sizing and styles
    constexpr int TileWidth = 50;
    constexpr int TileHeight = 50;
    constexpr int StrokeWidth = 2;

    /// Tile colors and styles
    const QColor Tile1Color = QColor::fromRgb(115, 149, 82);
    const QColor Tile2Color = QColor::fromRgb(235, 236, 208);
    const QPen Tile1Pen = QPen(Tile1Color, StrokeWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    const QPen Tile2Pen = QPen(Tile2Color, StrokeWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    // Selected square styling
    const QColor SelectedSquareColor = QColor::fromRgb(254, 253, 171);
    const QPen SelectedSquarePen = QPen(Qt::white, StrokeWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    // Legal move circle styling
    constexpr int CircleOffset = 13;
    constexpr int CircleSize = 26;
    const QColor LegalMovesCircleColor = QColor::fromRgb(0, 0, 0, 40);

    // Legal takes ring styling
    constexpr int RingOffset = 5;
    constexpr int RingSize = 40;
    constexpr int RingInnerWidth = 5;
    const QColor LegalTakesRingColor = QColor::fromRgb(0, 0, 0, 60);
    const QPen LegalTakesRingPen = QPen(LegalTakesRingColor, StrokeWidth * RingInnerWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
}

#endif

