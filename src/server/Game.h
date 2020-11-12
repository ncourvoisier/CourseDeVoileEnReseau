#ifndef SAILINSANE_GAME_H
#define SAILINSANE_GAME_H


#include <vector>

#include "Player.h"

namespace sail
{

    class Game
    {
    public:
        Game();

        void start();

       // gf::Id addPlayer(gf::TcpSocket socket);

        bool connectPlayer(Player& player, gf::Id id, std::string userName);

        std::vector<Player>& getPlayers();

        void playerAction(Player& player, PlayerAction action);

        GameState updateGame(int dt);

    private:
        static constexpr int NeededPlayers = 2;

        static constexpr float Speed = 25.0f;
        static constexpr float MaxSpeed = Speed * 4;

        std::vector<Player> m_players;

        int m_playersNb;

        bool m_started;
    };

}


#endif //SAILINSANE_GAME_H