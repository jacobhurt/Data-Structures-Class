#include "Set.hpp"
#include "SetScore.hpp"
#include "Game.hpp"
#include "TieBreaker.hpp"

Set::Set( Player *p1, Player *p2 ): Competition( p1, p2 ) {}

Score *Set::play( Player *p ) {
	SetScore *score = new SetScore( player1(), player2() );

	while( !score->haveAWinner() ) {
		Game *game = new Game( player1(), player2() );
		score->addScore( game->play(p)->getWinner() );
		p = Player::otherPlayer(p);
		delete game;
	}
	if(score->shouldPlayATieBreaker()){
		TieBreaker *tieBreaker = new TieBreaker( player1(), player2() );
		score->addTieScore( (TieBreakerScore*)tieBreaker->play(p) );
		delete tieBreaker;
	}
    return score;
}

