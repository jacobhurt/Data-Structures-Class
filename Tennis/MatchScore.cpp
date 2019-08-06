#include "MatchScore.hpp"

MatchScore::MatchScore( Player *p1, Player *p2 ): Score( p1, p2 ), setNumber(0) {}

bool MatchScore::haveAWinner()  {
	return player1Score() == 3 || player2Score() == 3;
}

void MatchScore::addScore( Score *score ) {
	if(score->getWinner() == player1()){
		p1Score++;
	}
	else{
		p2Score++;
	}
	scores[setNumber++] = (SetScore*)score;
}

void MatchScore::print() {
    for( int i = 0; i < setNumber; i++ )
      scores[i]->print();
}
MatchScore::~MatchScore() {
    for( int i = 0; i < setNumber; i++ )
      delete scores[i];
}
