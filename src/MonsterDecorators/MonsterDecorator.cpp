#include "MonsterDecorator.h"
#include "SpeedDebuffDecorator.h"

MonsterEntityDecorator::MonsterEntityDecorator(std::unique_ptr<MonsterEntity> monsterPtr)
    : MonsterEntity(monsterPtr->GetType(), monsterPtr->GetLevel())
    , m_decoratedMonster(std::move(monsterPtr))
{}


// void MonsterEntityDecorator::RemoveExpiredDecorators()
// {
//     if (!m_decoratedMonster) return;

//     // Check the next decorator in the chain
//     auto* decorator = dynamic_cast<MonsterEntityDecorator*>(m_decoratedMonster.get());
//     auto* speedDebuffDecorator = dynamic_cast<SpeedDebuffDecorator*>(m_decoratedMonster.get());
//     if (speedDebuffDecorator)
//     {
//         std::cout << "Decorator type: " << typeid(*speedDebuffDecorator).name() << std::endl;
//     }
//     if (decorator) {
//         // Recursively call RemoveExpiredDecorators to check deeper layers
//         decorator->RemoveExpiredDecorators();

//         // Now check if the current decorator is a SpeedDebuffDecorator
//         if (auto* debuff = dynamic_cast<SpeedDebuffDecorator*>(decorator)) {
//             std::cout << "Decorator type: " << typeid(*debuff).name() << std::endl;

//             if (debuff) {
//                 std::cout << "is it marked removal?: " << debuff->IsMarkedForRemoval() << std::endl;
//                 if (debuff->IsMarkedForRemoval()) {
//                     std::cout << "Removing speed buff" << std::endl;
//                     // Remove this decorator by skipping it in the chain
//                     m_decoratedMonster = debuff->ExtractBaseMonsterUniquePointer();
//                 }
//             }
//         }
//     }
// }
