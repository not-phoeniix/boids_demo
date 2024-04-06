#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "boid.h"

class BSPTree {
   private:
    class BSPNode {
       private:
        std::vector<Boid*> boids;
        sf::IntRect bounds;
        sf::RectangleShape bounds_draw;
        int size_limit;

        BSPNode* left = nullptr;
        BSPNode* right = nullptr;
        BSPNode* parent = nullptr;

        void MoveBoidToNode(Boid* boid, BSPNode* node);
        void ResizeChildBounds();
        void MoveAllBoids(BSPNode* node);

       public:
        BSPNode(const sf::IntRect& bounds, int size_limit, BSPNode* parent = nullptr);
        BSPNode(int size_limit, BSPNode* parent = nullptr);
        ~BSPNode();

        void Update(float delta_time, const sf::IntRect& full_rect);
        void Draw(sf::RenderWindow& window);
        void DrawBounds(sf::RenderWindow& window);
        void Add(Boid* boid);

        sf::IntRect get_bounds();
        void set_bounds(const sf::IntRect& bounds);
    };

    BSPNode* root;

   public:
    bool draw_bounds = false;

    BSPTree(const sf::IntRect& bounds, int size_limit);
    ~BSPTree();

    void Update(float delta_time, const sf::IntRect& full_view);
    void Draw(sf::RenderWindow& window);
    void Add(Boid* boid);
};
