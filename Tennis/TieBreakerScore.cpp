#include "TieBreakerScore.hpp"
#include <cmath>
#include <iostream>

TieBreakerScore::TieBreakerScore( Player *p1, Player *p2 ): Score(p1, p2) {}

bool TieBreakerScore::haveAWinner(){
	if((player1Score() >= 7 || player2Score() >= 7) && std::abs(player1Score() - player2Score()) >= 2){
		return true;
	}
	return false;
}

void TieBreakerScore::print(){
	std::cout << "Tie-Breaker Score is :" << std::endl;
    std::cout << "p1 score = " << player1Score() << "\np2 Score = " << player2Score() << std::endl;
}