#pragma once

#include "State.h"
#include "TileMap.h"
#include "GUI.h"

class State;
class StateData;
class Button;
class TileMap;


class EditorMode
{
private:

protected:
	StateData* stateData;
	TileMap* tileMap;

public:
	EditorMode(StateData* state_data, TileMap* tile_map);
	~EditorMode();

	virtual void updateInput(const float& dt) = 0;
	virtual void updateGui(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	virtual void renderGui(sf::RenderTarget& target) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

