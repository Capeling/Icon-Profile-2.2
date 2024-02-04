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
	case IconType::Swing: return gManager->getPlayerSwing(); 
	case IconType::Jetpack: return gManager->getPlayerJetpack();
    }
}

void helpGeodeUpdate() {
    auto* mod = Loader::get()->getLoadedMod("geode.loader");
    auto value = mod->getSavedValue<std::string>("last-modified-auto-update-check");
    if (value.ends_with('\r')) {
        mod->setSavedValue("last-modified-auto-update-check", value.substr(0, value.size() - 1));
    }
}

class $modify(MenuLayer) {
	bool init() {
		if(!MenuLayer::init())
			return false;
		
		auto gm = GameManager::sharedState();

		helpGeodeUpdate();
		auto profileMenu = this->getChildByID("profile-menu");
		profileMenu->setLayout(AxisLayout::create());
		profileMenu->setPositionX(this->getChildByID("player-username")->getPositionX());

		SimplePlayer* playerIcon = SimplePlayer::create(0);
		playerIcon->updatePlayerFrame(static_cast<int>(getFrameIcon(gm->m_playerIconType)), static_cast<IconType>(gm->m_playerIconType));
		playerIcon->setColor(gm->colorForIdx(gm->getPlayerColor()));
		playerIcon->setSecondColor(gm->colorForIdx(gm->getPlayerColor2()));
		playerIcon->setGlowOutline(gm->colorForIdx(gm->getPlayerGlowColor()));
		playerIcon->enableCustomGlowColor(gm->colorForIdx(gm->getPlayerGlowColor()));
		if(!gm->getPlayerGlow()) playerIcon->disableGlowOutline();
		playerIcon->setScale(1.15);
		CCSprite* playerSprite = as<CCSprite*>(as<CCMenuItemSpriteExtra*>(profileMenu->getChildByID("profile-button"))->getChildren()->objectAtIndex(0));
		if(gm->m_playerIconType == IconType::Robot) playerIcon->m_robotSprite->runAnimation("idle01");
		if(gm->m_playerIconType == IconType::Spider) playerIcon->m_spiderSprite->runAnimation("idle01");
		playerSprite->addChild(playerIcon);
		playerSprite->setDisplayFrame(playerIcon->displayFrame());
		
		return true;
	}
};
