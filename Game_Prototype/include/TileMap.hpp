//
//  TileMap.hpp
//  AssetManagerv1
//
//  Created by Denis Flynn on 19/09/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef TileMap_hpp
#define TileMap_hpp
#include <string>
#include "Window.h"
#include "enums.h"
#include <iostream>

// The level tile type.
struct Tile {
    TILE type;                            // The type of tile this is.
    int columnIndex;                    // The column index of the tile.
    int rowIndex;                        // The row index of the tile.
    sf::Sprite sprite;                    // The tile sprite.
    int H;                                // Heuristic / movement cost to goal.
    int G;                                // Movement cost. (Total of entire path)
    int F;                                // Estimated cost for full path. (G + H)
    Tile* parentNode;                    // Node to reach this node.
};

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    
//    // Gets the tile that the position lies on.
//    TileMap* GetTile(sf::Vector2f position)
//    {
//        // Convert the position to relative to the level grid.
//        position.x -= m_origin.x;
//        position.y -= m_origin.y;
//
//        // Convert to a tile position.
//        int tileColumn, tileRow;
//
//        tileColumn = static_cast<int>(position.x) / m_tileSize.x;
//        tileRow = static_cast<int>(position.y) / m_tileSize.y;
//
//        return &m_grid[tileColumn][tileRow];
//    }
//
//    // Returns a pointer to the tile at the given index.
//    Tile* GetTile(int columnIndex, int rowIndex)
//    {
//        if (TileIsValid(columnIndex, rowIndex))
//        {
//            return &m_grid[columnIndex][rowIndex];
//        }
//        else
//        {
//            return nullptr;
//        }
//    }
    
    // Gets the actual location of a tile in the level.
    sf::Vector2f GetActualTileLocation(int columnIndex, int rowIndex)
    {
        sf::Vector2f location;
        
        location.x = static_cast<float>(m_origin.x + (columnIndex * m_tileSize.x) + (m_tileSize.x / 2));
        location.y = static_cast<float>(m_origin.y + (rowIndex * m_tileSize.y) + (m_tileSize.y / 2));
        
        return location;
    }
    sf::Vector2i GetActualTileLocation(float x, float y)
    {
        sf::Vector2i location;
        location.x = static_cast<int>((x-m_tileSize.x / 2-m_origin.x)/(m_tileSize.x ));
        location.y = static_cast<int>((y-m_tileSize.y / 2-m_origin.y)/(m_tileSize.y ));
        
        return location;
    }
    sf::Vector2i GetActualTileLocation(sf::Vector2f location)
    {
        sf::Vector2i locationInt;
        locationInt.x = static_cast<int>((location.x-m_tileSize.x / 2-m_origin.x)/(m_tileSize.x ));
        locationInt.y = static_cast<int>((location.y-m_tileSize.y / 2-m_origin.y)/(m_tileSize.y ));
        
        return locationInt;
    }
    void printOnTile(std::string text,int row, int col){
        
        m_text.setString(text);
        m_text.setFont(m_font);
        m_text.setCharacterSize(m_tileSize.x/2);
        m_text.setFillColor(sf::Color::Red);
        sf::Vector2f text_pos;
        text_pos= GetActualTileLocation(row,col);
        m_text.setPosition(text_pos);
        
    }
    void rectangeOnTile(sf::Vector2i pos, sf::Color colour){
    //store old tile colour getFillColour()
        sf::Vector2f(pos.x * m_tileSize.x, pos.y * m_tileSize.y);
        
        //m_rectangleArr[pos.x + pos.y * m_tileArrSize.y].getOutlineColor();
        m_rectangleArr[pos.x + pos.y * m_tileArrSize.y].setFillColor(colour);
        //if warm colour, ,
        //set tile colour red sf::Color::r=256
        //if cool colour, set tile colour red sf::Color::b=256
        //use alpha sf::Color::a=amount

//        m_rectangle.setSize(sf::Vector2f(m_tileSize.x, m_tileSize.y));
//        m_rectangle.setOutlineColor(sf::Color::Yellow);
//        m_rectangle.setOutlineThickness(5);
//
//        m_rectangle.setOutlineColor(sf::Color::Red);
//        m_rectangle.setOutlineThickness(5);
//        m_rectangle.setPosition(10, 20);
    }
    void printOnTile(std::string text,sf::Vector2i pos){
        
        m_text.setString(text);
        m_text.setFont(m_font);
        m_text.setCharacterSize(m_tileSize.x/2);
        m_text.setFillColor(sf::Color::Red);
        sf::Vector2f text_pos;
        text_pos= GetActualTileLocation(pos.x,pos.y);
        m_text.setPosition(text_pos);
        
    }
    void printOnTileArr(std::vector<sf::Text> textArr){

        m_GridText=textArr;
        
    }
    
    bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height)
    {
        if (!m_font.loadFromFile("resource/arial.ttf"))
        {
            // Error...
            std::cout <<"Error!!"<<std::endl;
            
        }
        m_tileSize=tileSize;
        m_tileArrSize=sf::Vector2u(width,height);
        
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;
        
        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);
        
        
        m_rectangle.setSize(sf::Vector2f(tileSize.x, tileSize.y));
        m_rectangle.setOutlineColor(sf::Color::Yellow);
        m_rectangle.setOutlineThickness(5);
        
        
        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];
                
                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().y / tileSize.y);
                
                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
                
                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                
                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                
                m_rectangle.setPosition(quad[0].position);
                m_rectangleArr.push_back(m_rectangle);
            }
        
        return true;
    }
    
    
    
private:
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();
        
        // apply the tileset texture
        //states.texture = &m_tileset;
        
        // draw the vertex array
        target.draw(m_vertices, states);
        for (auto const& i:m_rectangleArr){
            target.draw(i);
        }
        
        for (auto const& i:m_GridText){
            target.draw(i);
        }
        
        
        
    }
    
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;
    sf::Vector2u m_tileArrSize;
    sf::RectangleShape m_rectangle;
    std::vector<sf::RectangleShape> m_rectangleArr;
    
    sf::Vector2i m_origin;
    std::vector<int> m_grid;
    sf::Font m_font;
    sf::Text m_text;
    std::vector<sf::Text> m_GridText;
    
    // Load from a font file on disk
    

};
#endif /* TileMap_hpp */
