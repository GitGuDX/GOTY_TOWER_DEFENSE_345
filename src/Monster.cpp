/**

@file Monster.cpp

@brief Implements the Monster class behavior and attributes.
*/

#include "Monster.h"
//#include "Tower.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

bool Monster::CanAttack()
{
    return m_fTimeSinceLastAttack >= m_fAttackCooldown;
}

// void Monster::Attack(Tower& tower)
// {
//     if (CanAttack())
//     {
//         tower.TakeDamage(m_fAttackDamage);  // Tower loses health
//         m_fTimeSinceLastAttack = 0.0f;  // Reset attack cooldown
//     }
// }

void Monster::UpdateAttackCooldown(float deltaTime)
{
    m_fTimeSinceLastAttack += deltaTime;
}
