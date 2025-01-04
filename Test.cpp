#include "Game.h"
using namespace model;
using namespace constants;

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Position, ConstructorAndAccessors) {
    Position pos;                      
    EXPECT_EQ(0, pos.getRank());
    EXPECT_EQ(0, pos.getFile());
    Position pos1(7, 3);                 
    EXPECT_EQ(7, pos1.getRank());
    EXPECT_EQ(3, pos1.getFile());
}

TEST(Position, Equality) {
    Position pos1(2, 3);
    Position pos2(2, 3);
    Position pos3(3, 2);
    EXPECT_TRUE(pos1 == pos2);         
    EXPECT_FALSE(pos1 == pos3);
    EXPECT_TRUE(pos1 != pos3);          
    EXPECT_FALSE(pos1 != pos2);
}

TEST(Position, Addition) {
    Position pos1(1, 1);
    Position pos2(2, 3);
    pos1 + pos2;
    EXPECT_EQ(3, pos1.getRank());
    EXPECT_EQ(4, pos1.getFile());
}

TEST(Position, AdditionAssignment) {
    Position pos1(1, 1);
    Position pos2(2, 3);
    pos1 += pos2;
    EXPECT_EQ(3, pos1.getRank());
    EXPECT_EQ(4, pos1.getFile());
}

TEST(Position, MultByScalar) {
    Position pos(1, 1);
    pos = pos * 3;
    EXPECT_EQ(3, pos.getRank());
    EXPECT_EQ(3, pos.getFile());
}

TEST(Position, ChangePosition) {
    Position pos1(2, 3);
    Position pos2(5, 6);
    pos1.changePosition(pos2);
    EXPECT_EQ(5, pos2.getRank());
    EXPECT_EQ(6, pos2.getFile());
}

TEST(Position, IsSumEven) {
    Position pos1(1, 1);
    Position pos2(2, 3);
    EXPECT_TRUE(pos1.isSumEven());
    EXPECT_FALSE(pos2.isSumEven());
}

TEST(Position, InsideBoard) {
    Position inside(5, 5);
    Position outside(8, 8);
    EXPECT_TRUE(inside.insideBoard());
    EXPECT_FALSE(outside.insideBoard());
}

TEST(Color, ConstructorAndToString) {
    Color white("White");
    EXPECT_EQ(white.toString(), White);

    Color noColor;                         
    EXPECT_EQ(noColor.toString(), None);
}

TEST(Color, Equality) {
    Color white1(White);
    Color white2(White);
    Color black(Black);
    EXPECT_TRUE(white1 == white2);          
    EXPECT_FALSE(white1 == black);

    EXPECT_TRUE(white1 != black);            
    EXPECT_FALSE(white1 != white2);
}

TEST(Rook, ConstructorAndAccessorsAndClone) {
    Position pos(1, 1);
    Color color(White);
    Rook rook(pos, color);
    EXPECT_EQ(rook.getPosition(), pos);
    EXPECT_EQ(rook.getColor(), color);
    EXPECT_EQ(rook.getType(), ROOK);

    std::shared_ptr<Piece> clonedRook = rook.clone();                        
    EXPECT_EQ(clonedRook->getPosition(), rook.getPosition());
    EXPECT_EQ(clonedRook->getColor(), rook.getColor());
    EXPECT_EQ(clonedRook->getType(), rook.getType());
}

TEST(Bishop, ConstructorAndAccessorsAndClone) {
    Position pos(1, 1);
    Color color(Black);
    Bishop bishop(pos, color);
    EXPECT_EQ(bishop.getPosition(), pos);
    EXPECT_EQ(bishop.getColor(), color);
    EXPECT_EQ(bishop.getType(), BISHOP);

    std::shared_ptr<Piece> clonedBishop = bishop.clone();                         
    EXPECT_EQ(clonedBishop->getPosition(), bishop.getPosition());
    EXPECT_EQ(clonedBishop->getColor(), bishop.getColor());
    EXPECT_EQ(clonedBishop->getType(), bishop.getType());                         
}

TEST(King, ConstructorAndAccessorsAndClone) {
    Position pos(1, 1);
    Color color(White);
    King king(pos, color);
    EXPECT_EQ(king.getPosition(), pos);
    EXPECT_EQ(king.getColor(), color);
    EXPECT_EQ(king.getType(), KING);

    std::shared_ptr<Piece> clonedKing = king.clone();                     
    EXPECT_EQ(clonedKing->getPosition(), king.getPosition());
    EXPECT_EQ(clonedKing->getColor(), king.getColor());
    EXPECT_EQ(clonedKing->getType(), king.getType());

}

TEST(King, PossibleMoves) {
    std::unique_ptr<Game> game = std::make_unique<Game>(constants::GameTag::EmptyGame);
    Position pos(0, 0);
    Color color(White);
    std::shared_ptr<King> king = std::make_shared<King>(pos, color);
    vector<Position> possibleMoves = king->possibleMoves(const_cast<const std::shared_ptr<Piece>**>(game->getBoard()->getPieces()));
    map<string, Position> positions = {
        {"a7", {1, 0}},
        {"b8", {0, 1}},
        {"b7", {1, 1}}
    };

    auto positionExistsInMoves = [&](Position& targetPosition) {
        for (Position& move : possibleMoves) {
            if (move == targetPosition) {
                return true;
            }
        }
        return false;
        };

    EXPECT_TRUE(positionExistsInMoves(positions["a7"]));
    EXPECT_TRUE(positionExistsInMoves(positions["b8"]));
    EXPECT_TRUE(positionExistsInMoves(positions["b7"]));
}

TEST(Rook, PossibleMoves) {
    std::unique_ptr<Game> game = std::make_unique<Game>(constants::GameTag::EmptyGame);
    Position pos(0, 0);
    Color color(White);
    std::shared_ptr<Rook> rook = std::make_shared<Rook>(pos, color);
    vector<Position> possibleMoves = rook->possibleMoves(const_cast<const std::shared_ptr<Piece>**>(game->getBoard()->getPieces()));

    map<string, Position> expectedPositions = {

        {"b8", {0, 1}},
        {"c8", {0, 2}},
        {"d8", {0, 3}},
        {"e8", {0, 4}},
        {"f8", {0, 5}},
        {"g8", {0, 6}},
        {"h8", {0, 7}},

        {"a7", {1, 0}},
        {"a6", {2, 0}},
        {"a5", {3, 0}},
        {"a4", {4, 0}},
        {"a3", {5, 0}},
        {"a2", {6, 0}},
        {"a1", {7, 0}}
    };
    auto positionExistsInMoves = [&](const Position& targetPosition) -> bool {
        for (const Position& move : possibleMoves) {
            if (move == targetPosition) {
                return true;
            }
        }
        return false;
        };

    for (const auto& [positionName, targetPosition] : expectedPositions) {
        EXPECT_TRUE(positionExistsInMoves(targetPosition));
    }
}

TEST(Bishop, PossibleMoves) {
    std::unique_ptr<Game> game = std::make_unique<Game>(constants::GameTag::EmptyGame);

    Position pos(0, 0);
    Color color(White);
    std::shared_ptr<Bishop> bishop = std::make_shared<Bishop>(pos, color);

    vector<Position> possibleMoves = bishop->possibleMoves(const_cast<const std::shared_ptr<Piece>**>(game->getBoard()->getPieces()));

    map<string, Position> expectedPositions = {
        {"b7", {1, 1}},
        {"c6", {2, 2}},
        {"d5", {3, 3}},
        {"e4", {4, 4}},
        {"f3", {5, 5}},
        {"g2", {6, 6}},
        {"h1", {7, 7}}
    };

    auto positionExistsInMoves = [&](const Position& targetPosition) -> bool {
        for (const Position& move : possibleMoves) {
            if (move == targetPosition) {
                return true;
            }
        }
        return false;
        };

    for (const auto& [positionName, targetPosition] : expectedPositions) {
        EXPECT_TRUE(positionExistsInMoves(targetPosition));
    }
}






#endif
