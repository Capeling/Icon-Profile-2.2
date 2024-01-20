#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

int getFrameIcon(int type) {
    auto gManager = GameManager::sharedState();
    switch(type) {
        default: return gManager->getPlayerFrame();
        case 1 return gManager->getPlayerShip();
        case 2 return gManager->getPlayerBall();
        case 3 return gManager->getPlayerBird();
        case 4 return gManager->getPlayerDart();
        case 5 return gManager->getPlayerRobot();
        case 6 return gManager->getPlayerSpider();
	case 7 return gManager->getPlayerSwing(); 
	case 8 return gManager->getPlayerJetpack();
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
