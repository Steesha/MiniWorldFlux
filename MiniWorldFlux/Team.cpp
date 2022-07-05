#include "Team.h"

Team::Team() : AbstractModule("Team", Category::World) {

}

Team* Team::getInstance() {
	static Team* inst = new Team();
	return inst;
}

bool Team::isSameTeam(SDK::ClientPlayer* target) {
	IngameCheck false;

	for (auto& pair : Game::playerInfo) {

		if (pair.first == target->uid)
			if (pair.second->team == Game::thePlayer->getTeam())
				return true;
	}

	return false;
}

void Team::onEnabled() {

}

void Team::onDisabled() {

}

