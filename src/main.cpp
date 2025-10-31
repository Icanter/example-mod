#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PortalGameObject.hpp>

using namespace geode::prelude;

// Hook PlayerObject for orb clicks
class $modify(PlayerObject) {
    void activateOrb(EffectGameObject* orb, int player, bool idk) {
        // Call original function
        PlayerObject::activateOrb(orb, player, idk);
        // Disable the circle glow
        if (m_circleWave) {
            m_circleWave->setVisible(false);
        }
    }
};

// Hook PortalGameObject for portals
class $modify(PortalGameObject) {
    void activateObject(PlayerObject* player) {
        PortalGameObject::activateObject(player);
        if (player->m_circleWave) {
            player->m_circleWave->setVisible(false);
        }
    }
};