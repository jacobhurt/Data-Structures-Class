#include "Match.hpp"
#include "Score.hpp"
#include "MatchScore.hpp"
#include "Set.hpp"
#include "Player.hpp"

Match::Match( Player *p1, Player *p2 ): Competition( p1, p2 ) {}

Score *Match::play( Player *p ) {
    MatchScore *score = new MatchScore( player1(), player2() );

    while( !score->haveAWinner() ) {
		Set *set = new Set( player1(), player2() );
		score->addScore( set->play(p) );
		p = Player::otherPlayer(p);
		delete set;
    }
    return score;
}
