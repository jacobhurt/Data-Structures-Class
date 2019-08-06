#include "TieBreaker.hpp"
#include "TieBreakerScore.hpp"
#include "PointScore.hpp"

TieBreaker::TieBreaker( Player *p1, Player *p2 ): Competition( p1, p2 ) {}

Score *TieBreaker::play( Player *p ) {
    TieBreakerScore* score = new TieBreakerScore( player1(), player2() );

    PointScore *pointScore = reinterpret_cast<PointScore *>( p->serveAPoint() );
	score->addScore( pointScore->getWinner() );
  	delete pointScore;

  	int switchServe = 0;

    do{
    	if(switchServe++ % 2 == 0){
    		p = Player::otherPlayer(p);
    	}
    	PointScore *pointScore = reinterpret_cast<PointScore *>( p->serveAPoint() );
		score->addScore( pointScore->getWinner() );
		delete pointScore;
    } while(!score->haveAWinner());

    return score;
}
