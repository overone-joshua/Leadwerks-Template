#ifndef _GAMEPLAY_MANAGER_HPP_
    #define _GAMEPLAY_MANAGER_HPP_

#pragma once
#include "../Utilities/Macros.hpp"
#include "../Utilities/Manager.hpp"

#include <functional>
#include <list>

class GameplayManager
{
    typedef std::function<bool(void)> Condition;

    CLASS_TYPE(GameplayManager);

public:

    GameplayManager(void);
    ~GameplayManager(void);

    void Dispose(void);

    std::list<Condition>::iterator AddWinCondition(Condition _condition);

    std::list<Condition>::iterator AddLooseCondition(Condition _condition);

    bool Won(std::function<bool(std::list<Condition>)> _function);

    bool Lost(std::function<bool(std::list<Condition>)> _function);

private:

    std::list<Condition> m_winConditions;

    std::list<Condition> m_loseConditions;

}; // < end class.

#endif _GAMEPLAY_MANAGER_HPP_