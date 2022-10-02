#include "Nodes/Grid.hpp"
#include "Standard/Math/util.hpp"
#include <iostream>

struct GridLoader{
    GridLoader(Grid *grid) : grid(grid){}

    void set_textures() const
    {
        for(int i = 0; i < grid->size.y; i++)
        {
            for(int j = 0; j < grid->size.x; j++)
            {
                grid->setTile({i,j},i % 64);
            }
        }
    }

    void load_texture(const std::string& tileSetPath) const
    {
        sf::Texture texture;
        if (!texture.loadFromFile(tileSetPath))
        {
            std::cerr << "Failed to load texture [[" << tileSetPath << "]]!" << std::endl;
            return;
        }
        grid->tileSet = std::make_shared<sf::Texture>(texture);
    }

    void load_vertices() const
    {
        grid->vertices.setPrimitiveType(sf::Quads);
        grid->vertices.resize(grid->size.x * grid->size.y * 4);

        for (unsigned int i = 0; i < grid->size.x; ++i)
            for (unsigned int j = 0; j < grid->size.y; ++j)
            {
                sf::Vertex *quad = &grid->vertices[(i + j * grid->size.x) * 4];

                quad[0].position = sf::Vector2f(i * grid->tileSize.x, j * grid->tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * grid->tileSize.x, j * grid->tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * grid->tileSize.x, (j + 1) * grid->tileSize.y);
                quad[3].position = sf::Vector2f(i * grid->tileSize.x, (j + 1) * grid->tileSize.y);

                // ustaw puste tekstury
                quad[0].texCoords = sf::Vector2f(); // left top
                quad[1].texCoords = sf::Vector2f(); // right top
                quad[2].texCoords = sf::Vector2f(); // right bottom
                quad[3].texCoords = sf::Vector2f(); // left bottom
            }
    }

    void load_grid(const std::string& tileSetPath) const
    {
        load_vertices();
        load_texture(tileSetPath);
        set_textures();
    }

    Grid* grid;
};


Grid::Grid(engine::Vec2i size, const std::string& tileSetPath, engine::Vec2i tileSize) :
            size(size), tileSize(tileSize)
{
    tiles.reserve(size.x * size.y);
    GridLoader loader(this);
    loader.load_grid(tileSetPath);
}

void Grid::setTile(engine::Vec2i position, unsigned int tileID)
{
    tiles[to1d(size.x, position.x, position.y)].tile = tileID;
    int tu = tileID % (tileSet->getSize().x / tileSize.x);
    int tv = tileID / (tileSet->getSize().x / tileSize.x);

    sf::Vertex *quad = &vertices[(position.x + position.y * size.x) * 4];

    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y); // left top
    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y); // right top
    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y); // right bottom
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y); // left bottom
}

void Grid::onDraw(Renderer &renderer) const 
{
    sf::RenderStates state;
    state.texture = tileSet.get();
    // state.transform = global_transform.getTransform();
    renderer.draw_object_on_layer(vertices, 1, state);
}
void Grid::onUpdate(const sf::Time& delta) 
{

}

