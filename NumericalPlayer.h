#include "BoardGame_Classes.h"
#include <vector>
#include <utility>

class NumericalPlayer : public Player<int> {
public:
    NumericalPlayer(string n, int s, PlayerType t);


    Move<int>* get_random_move();
};

#endif
