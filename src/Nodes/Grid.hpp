#pragma once
#include "Nodes/Node.hpp"
#include "Standard/Math/util.hpp"

class Grid : public Node{
    public:
        struct Tile {
            int original_tile{};
            int current_tile{};
            int basic_tile{};
            int phase{};
            engine::Vec2i pos{};
        };
        Grid(engine::Vec2i size, const std::string& tilesetName, engine::Vec2i tileSize);

        void setTile(engine::Vec2i position, unsigned int tileID);
        void setTile(unsigned int position, unsigned int tileID);


    private:
        engine::Vec2i size{};
        engine::Vec2i tileSize{};

        std::vector<Tile> tiles;
        AtlasManager* atlasManager;
        AtlasManager* atlasManagerColl;


        const Layers* layers = Layers::get_instance();

    protected:
        void onDraw() const override;
        void onUpdate(const sf::Time& delta) override;
};

