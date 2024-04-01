#include <iostream>
#include "bsp.h"

using namespace sf;

//*
//* BSPNode class definitions
//*

#pragma region

void BSPNode::Split() {
    // exit early and prevent splitting if children
    //   already exist, to prevent memory leaks
    if (left != nullptr || right != nullptr) return;

    bool h_split = bounds.height > bounds.width;

    // if h_split == true, left node is on the top,
    //   else left node is to the left
    left = new BSPNode(
        IntRect(
            bounds.left,
            bounds.top,
            h_split ? bounds.width : bounds.width / 2,
            h_split ? bounds.height / 2 : bounds.height
        ),
        size_limit,
        this
    );

    // if h_split == true, right node is on the bottom,
    //   else right node is to the right
    right = new BSPNode(
        IntRect(
            h_split ? bounds.left : bounds.left + bounds.width / 2,
            h_split ? bounds.top + bounds.height / 2 : bounds.top,
            h_split ? bounds.width : bounds.width / 2,
            h_split ? bounds.height / 2 : bounds.height
        ),
        size_limit,
        this
    );

    // place containing boids into child nodes and mark them as "to remove"
    std::vector<Boid*> to_remove;
    for (Boid* boid : boids) {
        Vector2i boid_pos = (Vector2i)boid->get_position();
        if (left->get_bounds().contains(boid_pos)) {
            left->Add(boid);
            to_remove.push_back(boid);
        } else if (right->get_bounds().contains(boid_pos)) {
            left->Add(boid);
            to_remove.push_back(boid);
        }
    }

    // remove boids from original list that have been marked
    for (int i = to_remove.size() - 1; i >= 0; i--) {
        // iterate across original boids vector
        for (int j = 0; j < boids.size(); j++) {
            // if the one to remove is found, erase if from the original boids vector
            if (boids[j] == to_remove[i]) boids.erase(boids.begin() + j);
        }
    }

    // clear the to_remove vector
    to_remove.clear();
}

BSPNode::BSPNode(const IntRect& bounds, int size_limit, BSPNode* parent)
: bounds(bounds), parent(parent), size_limit(size_limit) {
    // initialize bounds rectangle values
    bounds_draw.setPosition((Vector2f)bounds.getPosition());
    bounds_draw.setSize((Vector2f)bounds.getSize());
    bounds_draw.setFillColor(Color::Transparent);
    bounds_draw.setOutlineColor(Color::Red);
    bounds_draw.setOutlineThickness(1.0f);
}

BSPNode::~BSPNode() {
    for (Boid* boid : boids) {
        delete boid;
    }
}

void BSPNode::Update(float delta_time, const IntRect& full_rect) {
    // recursively update children
    if (left != nullptr) left->Update(delta_time, full_rect);
    if (right != nullptr) right->Update(delta_time, full_rect);

    // update this node
    for (Boid* boid : boids) {
        boid->Update(delta_time, full_rect, boids);
    }
}

void BSPNode::Draw(RenderWindow& window) {
    if (left != nullptr) left->Draw(window);
    if (right != nullptr) right->Draw(window);

    for (Boid* boid : boids) {
        boid->Draw(window);
    }
}

void BSPNode::DrawBounds(sf::RenderWindow& window) {
    if (left != nullptr) left->DrawBounds(window);
    if (right != nullptr) right->DrawBounds(window);

    window.draw(bounds_draw);
}

void BSPNode::Add(Boid* boid) {
    boids.push_back(boid);

    if (boids.size() > size_limit) {
        // Split();
    }
}

IntRect BSPNode::get_bounds() { return bounds; }
void BSPNode::set_bounds(const IntRect& bounds) { this->bounds = bounds; }

#pragma endregion

//*
//* BSPTree class definitions
//*

#pragma region

BSPTree::BSPTree(const sf::IntRect& bounds, int size_limit) {
    root = new BSPNode(bounds, size_limit, nullptr);
}

#pragma endregion
