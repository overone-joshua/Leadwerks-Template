
#pragma once
#include "GameplayManager.hpp"

GameplayManager::GameplayManager(void) 
    : m_winConditions(std::list<Condition>())
    , m_loseConditions(std::list<Condition>()) { }

GameplayManager::~GameplayManager(void) { Dispose(); }

void GameplayManager::Dispose(void) 
{
    m_winConditions.clear();
    m_loseConditions.clear();
}

std::list<GameplayManager::Condition>::iterator GameplayManager::AddWinCondition(GameplayManager::Condition _condition)
{
    return m_winConditions.insert(m_winConditions.end(), _condition);
}

std::list<GameplayManager::Condition>::iterator GameplayManager::AddLooseCondition(GameplayManager::Condition _condition)
{
    return m_loseConditions.insert(m_loseConditions.end(), _condition);
}

bool GameplayManager::Won(std::function<bool(std::list<Condition>)> _func)
{
    return _func(m_winConditions);
}

bool GameplayManager::Lost(std::function<bool(std::list<Condition>)> _func)
{
    return _func(m_loseConditions);
}