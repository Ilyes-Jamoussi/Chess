/*
* This program simulates a chess game with interface
* \file   main.cpp
* \author Ahmed Sami Benabbou : 2122457 et Ilyes Jamoussi : 205854
* \date   27 avril 2024
* Créé le 3 mai 2024
*/

#include "Display.h"
#include "Game.h"
#pragma warning(push, 0)
#include <QtWidgets/QApplication>
#include "gtest/gtest.h"
#pragma pop()

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi(); 
	bibliotheque_cours::executerGoogleTest(argc, argv); 
#endif
}

int main(int argc, char *argv[]) {
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
    QApplication a(argc, argv);
    initialiserBibliothequeCours(argc, argv);
    interface::Display w;
    w.show();
    return a.exec();
}
