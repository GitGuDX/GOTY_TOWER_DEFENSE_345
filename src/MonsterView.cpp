// #include "MonsterView.h"
// #include <iostream>

// void MonsterView::Draw(sf::RenderWindow &window, std::vector<Monster> m_aMonstersQueue, int m_aPathSize)
// {
//     for (Monster& monster : m_aMonstersQueue) {
//         if (monster.GetCurrentPathIndex() < static_cast<size_t>(m_aPathSize) - 1){
//             window.draw(monster);
//         }
//     }
//     /*
//     // Iterate through the unordered_map using an iterator
//     std::vector<std::pair<const Monster*, MonsterStats>> reversedMonsters(m_monsterStats.begin(), m_monsterStats.end());

//     for (auto it = reversedMonsters.rbegin(); it != reversedMonsters.rend(); ++it) {
//         const Monster* monster = it->first;
//         if (monster == nullptr) continue;  // Avoid accessing invalid memory

//         // Check if the monster is still alive and in the path
//         if (monster->GetCurrentPathIndex() < m_aPathSize - 1 && monster->GetHealth() > 0) {
//             window.draw(*monster);
//         }
//     }
//     */
// }

// void MonsterView::RemoveMonster(const Monster &monster)
// {
//     // Debug print before removal
//     std::cout << "Monsters before removal: " << m_monsterStats.size() << std::endl;

//     auto it = m_monsterStats.find(&monster);
//     if (it != m_monsterStats.end()) {
//         m_monsterStats.erase(it);
//     } else {
//         std::cout << "Monster not found!" << std::endl;  // Debugging help
//     }

//     // Debug print after removal
//     std::cout << "Monsters after removal: " << m_monsterStats.size() << std::endl;
// }

// void MonsterView::Update(const IGameSubject &subject)
// {
//     const Monster *monster = dynamic_cast<const Monster *>(&subject);
//     if (monster) {
//         auto& stats = m_monsterStats[monster];
//         stats.speed = monster->GetSpeed();
//         stats.health = monster->GetHealth();
//         stats.strength = monster->GetStrength();
//         stats.reward = monster->GetReward();
//         stats.level = monster->GetLevel();
//         stats.maxHealth = monster->GetMaxHealth();
//     }
// }

// const MonsterView::MonsterStats *MonsterView::GetMonsterStats(const Monster *monster) const
// {
//     auto it = m_monsterStats.find(monster);
//     if (it != m_monsterStats.end()) {
//         return &it->second;
//     }
//     return nullptr;
// }

