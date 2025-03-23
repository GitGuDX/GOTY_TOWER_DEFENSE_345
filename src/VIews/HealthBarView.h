#ifndef HEALTH_BAR_VIEW_H
#define HEALTH_BAR_VIEW_H

#include "../Platform.h"
#include "../GameEvents.h"
#include "../Entities/MonsterEntity.h"
#include <iostream>
#include <unordered_map>

using namespace sf;

class HealthBarView : public IGameObserver
{
public:
    struct HealthBarData
    {
        RectangleShape shape;
        float health;
        float maxHealth;
    };

    HealthBarView(RenderWindow& window);
    ~HealthBarView() = default;

    void Update(const IGameSubject& subject);

    void Draw();

    void InitializeShape(HealthBarData &data);

    void UpdateShape(HealthBarData& data);

    void RemoveMonster(const MonsterEntity* monsterPtr);

    void ClearSubjects() { m_MonsterEntitySubjects.clear(); }

    HealthBarView::HealthBarData* GetMonsterEntityData(const MonsterEntity* monster);

private:
    std::unordered_map<const MonsterEntity*, HealthBarData> m_MonsterEntitySubjects;

    RenderWindow& m_Window;

    int m_HealthBarPositionOffSet;
};

#endif