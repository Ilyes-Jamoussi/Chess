#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QImage>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QListWidget>

#include "ui_Display.h"
#include "Game.h"
#include "Square.h"
#include "Cercle.h"
#include "Ring.h"
#include "LegalMovesShapes.h"
#include "Image.h"

namespace interface {
    class Display : public QMainWindow {
        Q_OBJECT
    public:
        Display(QWidget* parent = nullptr);
      
        void startNewGame(const GameTag& gameTag);
        void removeCurrentGame();
        
        void setupGraphicsScene();
        void setupBoard();
        
        void resetBoardColors();

        QString currentPlayeQString() const;
        std::unique_ptr<LegalMovesShapes> createShape(const model::Position& position);
        void resetCurrentPlayerMessage();

        void establishConnections() const;
        void connectSquares() const;
        void connectValidMoves() const;
        void connectImages() const;
        void connectGameList() const;
        void connectGameStateMessages() const;
        void connectLeavingGame() const;

        ~Display();

    public slots:
        void updateSquareColor(const int rank, const int file);
        void resetSquareColor(const int rank, const int file);

        void refreshImages();
        void clearImages();

        void paintValidMoves(const int rank, const int file);
        void clearValidMoves();
        
        void changeGame();

        void playerStateMessage();
        void checkMessage();
        void checkMateMessage();
        void drawMessage();
        void resetMessage();
        void exitGame();
        
    private:
        Ui::DisplayClass ui;
        std::unique_ptr<QGraphicsScene> scene_ = nullptr;
        std::unique_ptr<model::Game> game_;
        std::unique_ptr<Square> square_[constants::BoardHeight][constants::BoardWidth];
        std::vector<std::unique_ptr<LegalMovesShapes>> legalMovesShapes_;
        std::vector<std::unique_ptr<Image>> images_;
    };
}

