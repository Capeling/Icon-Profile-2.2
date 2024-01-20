#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

int getFrameIcon(IconType type) {
    auto gManager = GameManager::sharedState();
    switch(type) {
        default: return gManager->getPlayerFrame();
        case IconType::Ship: return gManager->getPlayerShip();
        case IconType::Ball: return gManager->getPlayerBall();
        case IconType::Ufo: return gManager->getPlayerBird();
        case IconType::Wave: return gManager->getPlayerDart();
        case IconType::Robot: return gManager->getPlayerRobot();
        case IconType::Spider: return gManager->getPlayerSpider();
    }
}

class $modify(MenuLayer) {
	bool init() {
		if(!MenuLayer::init())
			return false;
		
		auto gm = GameManager::sharedState();

		auto profileMenu = this->getChildByID("profile-menu");
		profileMenu->setLayout(AxisLayout::create());
		profileMenu->setPositionX(this->getChildByID("player-username")->getPositionX());

		SimplePlayer* playerIcon = SimplePlayer::create(0);
		playerIcon->setColor(gm->colorForIdx(gm->getPlayerColor()));
		playerIcon->setSecondColor(gm->colorForIdx(gm->getPlayerColor2()));
		playerIcon->setGlowOutline(gm->colorForIdx(gm->getPlayerGlowColor()));
		playerIcon->enableCustomGlowColor(gm->colorForIdx(gm->getPlayerGlowColor()));
		if(!gm->getPlayerGlow()) playerIcon->disableGlowOutline();
		playerIcon->updatePlayerFrame(static_cast<int>(getFrameIcon(gm->m_playerIconType)), static_cast<IconType>(gm->m_playerIconType));
		playerIcon->setScale(1.15);
		CCSprite* playerSprite = as<CCSprite*>(as<CCMenuItemSpriteExtra*>(profileMenu->getChildByID("profile-button"))->getChildren()->objectAtIndex(0));
		playerSprite->addChild(playerIcon);
		playerSprite->setDisplayFrame(playerIcon->displayFrame());
		
		return true;
	}
};
