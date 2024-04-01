#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "boid.h"

class BSPNode {
   private:
    std::vector<Boid*> boids;
    sf::IntRect bounds;
    sf::RectangleShape bounds_draw;
    int size_limit;

    BSPNode* left = nullptr;
    BSPNode* right = nullptr;
    BSPNode* parent = nullptr;

    void Split(); // splits this node into 4 sub nodes
    void Join();  // merges (recursively) all sub nodes

   public:
    BSPNode(const sf::IntRect& bounds, int size_limit, BSPNode* parent = nullptr);
    ~BSPNode();

    // methods

    void Update(float delta_time, const sf::IntRect& full_rect);
    void Draw(sf::RenderWindow& window);
    void DrawBounds(sf::RenderWindow& window);
    void Add(Boid* boid);

    // getters & setters

    sf::IntRect get_bounds();
    void set_bounds(const sf::IntRect& bounds);
};

class BSPTree {
   private:
    BSPNode* root;

   public:
    BSPTree(const sf::IntRect& bounds, int size_limit);
    void Update(float delta_time);
    void Draw(sf::RenderWindow& window);
    void DrawBounds(sf::RenderWindow& window);
};
