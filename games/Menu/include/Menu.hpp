/*
** EPITECH PROJECT, 2026
** Snake
** File description:
** Snake
*/

#include "IGame.hpp"
#include "gfx.hpp"
#include <functional>
#include <map>
#include <queue>

typedef struct area_s {
    point_t a;
    point_t b;
} area_t;

class MenuGame : public IGame {
    public:
        void init();
        void close();
        void update(std::queue<Event>);
        std::queue<AnyInstruction> getGfxInstructions();

    private:
        std::queue<AnyInstruction> _instructions;
        std::map<area_t, std::function<void()>> _interactiveAreas;
};
