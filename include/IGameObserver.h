#pragma once
class IGameObserver {
    public:
    virtual ~IGameObserver() {};
    virtual  void onScoreChanged(int newScore)=0;
    virtual void onLivesChanged(int newLives)=0;
};