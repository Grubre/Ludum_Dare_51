#include "Nodes/Grid.hpp"
#include "Standard/Math/util.hpp"

struct GridLoader{
    GridLoader(Grid *grid) : grid(grid){}

    void load_textures() const
    {
        for(int i = 0; i < grid->size.y; i++)
        {
            for(int j = 0; j < grid->size.x; j++)
            {
                int tileID = 1;
                grid->tiles.emplace_back(tileID, engine::Vec2i(i,j));
            }
        }
    }

    void load_vertices() const
    {
        grid->vertices.setPrimitiveType(sf::Quads);
        grid->vertices.resize(grid->size.x * grid->size.y * 4);
        grid->tiles.resize(grid->size.x * grid->size.y);

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

    void load_grid() const
    {
        load_vertices();
        load_textures();
    }

    Grid* grid;
};


Grid::Grid(engine::Vec2i size, const std::string& tilesetName, engine::Vec2i tileSize) :
            size(size), tileSize(tileSize)
{
    tiles.reserve(size.x * size.y);
    GridLoader loader(this);
    loader.load_grid();
}

void Grid::setTile(engine::Vec2i position, unsigned int tileID)
{

}

void Grid::onDraw(Renderer &renderer) const 
{

}
void Grid::onUpdate(const sf::Time& delta) 
{

}

