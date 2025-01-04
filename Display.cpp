#include "Display.h"

namespace interface {

    Display::Display(QWidget* parent) : QMainWindow(parent) {
        game_ = std::make_unique<model::Game>(GameTag::EmptyGame );
        ui.setupUi(this);
        setupGraphicsScene();
        setupBoard();
        establishConnections();
        resetMessage();
        resetCurrentPlayerMessage();
    }
    
    void Display::startNewGame(const GameTag& gameTag) {
        this->game_ = std::make_unique<model::Game>( gameTag );
        refreshImages();
        establishConnections();
    }

    void Display::removeCurrentGame() {
        game_->resetBoard();
        clearImages();
        clearValidMoves();
        resetBoardColors();
        resetMessage();
        resetCurrentPlayerMessage();
    }

    void Display::changeGame() {      
        removeCurrentGame();
        startNewGame(game_->getGameMapping()[ui.myGameList->currentRow()]);
    }

    void Display::setupGraphicsScene() {
        this->scene_ = std::make_unique<QGraphicsScene>(constants::SceneXPos, constants::SceneYPos,
            constants::SceneWidth, constants::SceneHeight);
        ui.graphicsView->setScene(scene_.get());
    }

    void Display::setupBoard() {
        for (int rank : iter::range(constants::BoardWidth)) {
            for (int file : iter::range(constants::BoardHeight)) {
                model::Position position = { rank, file };
                this->square_[rank][file] = std::make_unique<Square>(position);
                scene_->addItem(this->square_[rank][file].get());
            }
        }
    }
    
    void Display::resetBoardColors() {
        for (int rank : iter::range(constants::BoardWidth)) {
            for (int file : iter::range(constants::BoardHeight))
                resetSquareColor(rank, file);
        }
    }
  
    void Display::paintValidMoves(const int rank, const int file) {
       std::shared_ptr<model::Piece> myPiece = game_->getBoard()->getPieceAt({ rank ,file });
       for (model::Position& position : this->game_->getBoard()->generateValidMoves(myPiece)){
           if (game_->getBoard()->getPieceAt(position)->getType() != KING) {
               std::unique_ptr<LegalMovesShapes> shape = createShape(position);
               scene_->addItem(dynamic_cast<QGraphicsItem*>(shape.get()));
               legalMovesShapes_.push_back(std::move(shape));             
           }
       }
    }

    void Display::clearValidMoves() {
       for (std::unique_ptr<LegalMovesShapes>& visualShape : this->legalMovesShapes_) {
           scene_->removeItem(dynamic_cast<QGraphicsItem*>(visualShape.get()));
       }
       this->legalMovesShapes_.clear();
    }

    std::unique_ptr<LegalMovesShapes> Display::createShape(const model::Position& position) {
        if (this->game_->getBoard()->containsPiece(position)) 
            return make_unique<Ring>(position);       
       return make_unique<Circle>(position);;
    }

    void Display::updateSquareColor(const int rank, const int file) {
        this->square_[rank][file]->changeColor(SelectedSquareColor, SelectedSquarePen);
        this->square_[rank][file]->setBrush(square_[rank][file]->getQColor());
    }

    void Display::resetSquareColor(const int rank, const int file) {
        this->square_[rank][file]->resetSquareColor();
        this->square_[rank][file]->setBrush(square_[rank][file]->getQColor());
    }

    void Display::refreshImages() {
        for (std::shared_ptr<model::Piece> piece : game_->getBoard()->getPieceVector()) {
            std::unique_ptr<Image> image = make_unique<Image>(piece);
            this->scene_->addItem(&image->getQtPixmap());
            this->images_.push_back(std::move(image));
            
        }
    }

    void Display::clearImages() {
        for (std::unique_ptr<Image>& image : this->images_) {
            this->scene_->removeItem(&image->getQtPixmap());
        }
        this->images_.clear();
    }
   
    void Display::establishConnections() const {
        connectSquares();
        connectImages();
        connectValidMoves();
        connectGameList();
        connectGameStateMessages();
        connectLeavingGame();
    }

    void Display::connectSquares() const {
        for (int rank : iter::range(constants::BoardWidth)) {
            for (int file : iter::range(constants::BoardWidth)) {
                QObject::connect(this->square_[rank][file].get(), &Square::SquareSelected, this->game_.get(), &model::Game::handlePieceSelection, Qt::UniqueConnection);
            }
        }
        QObject::connect(this->game_.get(), &model::Game::positionSelected, this, &Display::updateSquareColor, Qt::UniqueConnection);
        QObject::connect(this->game_.get(), &model::Game::positionDeselected, this, &Display::resetSquareColor, Qt::UniqueConnection);
    }

    void Display::connectImages() const {
        QObject::connect(this->game_.get(), &model::Game::refreshPieceImages, this, &Display::refreshImages, Qt::UniqueConnection);
        QObject::connect(this->game_.get(), &model::Game::clearPieceImages, this, &Display::clearImages, Qt::UniqueConnection);
    }

    void Display::connectValidMoves() const {
        QObject::connect(this->game_.get(), &model::Game::positionSelected, this, &Display::paintValidMoves, Qt::UniqueConnection);
        QObject::connect(this->game_.get(), &model::Game::positionDeselected, this, &Display::clearValidMoves, Qt::UniqueConnection);
    }

    void Display::connectGameList() const {
        QObject::connect(ui.myGameList, &QListWidget::itemClicked, this, &Display::changeGame, Qt::UniqueConnection);
    }
    
    void Display::connectGameStateMessages() const {
        QObject::connect(this->game_.get(), &model::Game::checkSignal, this, &Display::checkMessage, Qt::UniqueConnection);
        QObject::connect(this->game_.get(), &model::Game::checkMateSignal, this, &Display::checkMateMessage, Qt::UniqueConnection);
        QObject::connect(this->game_.get(), &model::Game::resetMessage, this, &Display::resetMessage, Qt::UniqueConnection);
        QObject::connect(this->game_.get(), &model::Game::drawSignal, this, &Display::drawMessage, Qt::UniqueConnection);
        QObject::connect(this->game_.get(), &model::Game::currentPlayerSignal, this, &Display::playerStateMessage, Qt::UniqueConnection);
        QObject::connect(this->game_.get(), &model::Game::resetCurrentPlayerMessage, this, &Display::resetCurrentPlayerMessage, Qt::UniqueConnection);
        QObject::connect(ui.myGameList, &QListWidget::itemClicked, this, &Display::playerStateMessage, Qt::UniqueConnection);
        
    }
    
    void Display::connectLeavingGame() const {
        QObject::connect(ui.actionExit, &QAction::triggered, this, &Display::exitGame, Qt::UniqueConnection);
    }

    void Display::exitGame() {
        this->close();
    }

    QString Display::currentPlayeQString() const {
        model::Color currentPlayerColor = this->game_->getPlayerState().getCurrentPlayer();
        return currentPlayerColor.toString().c_str();
    }

    void Display::playerStateMessage() {
        ui.currentPlayerLabel->setText(currentPlayeQString() + " turn");
    }
    void Display::checkMessage() {
        ui.feedBackLabel->setText(currentPlayeQString() + " is in check!");
    }
  
    void Display::checkMateMessage() {
        ui.feedBackLabel->setText("Player " + currentPlayeQString() + " lost!");
    }

    void Display::drawMessage() {    
        ui.feedBackLabel->setText("Draw!");
    }

    void Display::resetMessage() {
        ui.feedBackLabel->setText("");
    }

    void Display::resetCurrentPlayerMessage() {
        ui.currentPlayerLabel->setText("");
    }

    Display::~Display() {
    }
}






