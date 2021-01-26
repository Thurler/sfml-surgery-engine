#include "operation.h"

void OperationState::update(const sf::Time &time) {
	toolSelect->update(time);
	vitals->update(time);
}

void OperationState::draw(sf::RenderWindow *window) {
	toolSelect->draw(window);
	vitals->draw(window);
}

OperationState::OperationState(GlobalValues *global) : CommonState(global) {
	vitals = new VitalsState(global, 70, 99, 400);
  toolSelect = new ToolSelectState(global, vitals);
}

OperationState::~OperationState() {
	if (toolSelect) {
		delete toolSelect;
		toolSelect = NULL;
	}
	if (vitals) {
		delete vitals;
		vitals = NULL;
	}
}
