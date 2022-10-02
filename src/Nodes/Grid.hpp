#pragma once
#include "Nodes/Node.hpp"

class Grid : public Node{
    public:
        struct Tile {
            Tile(unsigned int tile, engine::Vec2i pos) : tile(tile), pos(pos) {}
            unsigned int tile{};
            engine::Vec2i pos{};
        };
        Grid(engine::Vec2i size, const std::string& tilesetName, engine::Vec2i tileSize);

        void setTile(engine::Vec2i position, unsigned int tileID);

    private:
        engine::Vec2i size{};
        engine::Vec2i tileSize{};

        std::vector<Tile> tiles;

        sf::VertexArray vertices;

    protected:
        void onDraw(Renderer &renderer) const override;
        void onUpdate(const sf::Time& delta) override;

    friend class GridLoader;
};

