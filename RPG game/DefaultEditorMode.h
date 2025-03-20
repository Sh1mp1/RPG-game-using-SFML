#pragma once
#include "EditorMode.h"
class DefaultEditorMode :
    public EditorMode
{
private:
    gui::TextureSelector* textureSelector;	//GUI to select specific tile from tile sheet

    sf::Texture tileMapTexture;	//Stores the texture sheet/ tilesheet
    std::string tileMapTexturePath;	//The path of the tile sheet file

    bool collision;	//Stores if the tile to be added will have collision
    short type;	//Stores the type of the tile to be added
    std::string typeString;	//Stores the string for the type of the tile currently selected

public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map);
    ~DefaultEditorMode();
};

