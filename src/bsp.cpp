#include <iostream>
#include "bsp.h"

using namespace sf;

//*
//* BSPNode class definitions
//*

#pragma region

BSPTree::BSPNode::BSPNode(const IntRect& bounds, int size_limit, BSPNode* parent)
: bounds(bounds), parent(parent), size_limit(size_limit) {
    // initialize bounds rectangle values
    bounds_draw.setPosition((Vector2f)bounds.getPosition());
    bounds_draw.setSize((Vector2f)bounds.getSize());
    bounds_draw.setFillColor(Color::Transparent);
    bounds_draw.setOutlineColor(Color::Red);
    bounds_draw.setOutlineThickness(1.0f);
}

BSPTree::BSPNode::BSPNode(int size_limit, BSPNode* parent)
: BSPNode(IntRect(), size_limit, parent) { }

BSPTree::BSPNode::~BSPNode() {
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;

    for (Boid* boid : boids) {
        delete boid;
    }
}

void BSPTree::BSPNode::Update(float delta_time, const IntRect& full_rect) {
    // resizing of root node (when parent == nullptr)
    if (parent == nullptr) set_bounds(full_rect);

    // update both child nodes
    if (left != nullptr && right != nullptr) {
        // resizing all child nodes
        ResizeChildBounds();

        left->Update(delta_time, full_rect);
        right->Update(delta_time, full_rect);

        bool children_can_delete =
            left->boids.size() == 0 &&
            left->left == nullptr &&
            right->boids.size() == 0 &&
            right->left == nullptr;

        if (children_can_delete) {
            delete left;
            delete right;
            left = nullptr;
            right = nullptr;
        }
    }

    // update this node
    for (Boid* boid : boids) {
        boid->Update(delta_time, full_rect, boids);

        // move boid to parent if it's no longer in the bounds
        //   of this node (and parent actually exists)
        if (!bounds.contains((Vector2i)boid->get_position())) {
            if (parent != nullptr) {
                MoveBoidToNode(boid, parent);
            }
        }
    }
}

void BSPTree::BSPNode::Draw(RenderWindow& window) {
    if (left != nullptr) left->Draw(window);
    if (right != nullptr) right->Draw(window);

    for (Boid* boid : boids) {
        boid->Draw(window);
    }
}

void BSPTree::BSPNode::DrawBounds(sf::RenderWindow& window) {
    if (left != nullptr) left->DrawBounds(window);
    if (right != nullptr) right->DrawBounds(window);

    window.draw(bounds_draw);
}

void BSPTree::BSPNode::Add(Boid* boid) {
    boids.push_back(boid);

    if (boids.size() >= size_limit) {
        // create nodes if they don't exist
        if (left == nullptr || right == nullptr) {
            left = new BSPNode(size_limit, this);
            right = new BSPNode(size_limit, this);
            ResizeChildBounds();
        }

        // move all boids to children nodes
        for (int i = boids.size() - 1; i >= 0; i--) {
            Boid* boid = boids[i];
            if (left->bounds.contains((Vector2i)boid->get_position())) {
                left->Add(boid);
                boids.erase(boids.begin() + i);
            } else if (right->bounds.contains((Vector2i)boid->get_position())) {
                right->Add(boid);
                boids.erase(boids.begin() + i);
            }
        }
    }
}

IntRect BSPTree::BSPNode::get_bounds() { return bounds; }
void BSPTree::BSPNode::set_bounds(const IntRect& bounds) {
    this->bounds = bounds;
    bounds_draw.setPosition((Vector2f)bounds.getPosition());
    bounds_draw.setSize((Vector2f)bounds.getSize());
}

/*
void BSPNode::Split() {
    // exit early and prevent splitting if children
    //   already exist, to prevent memory leaks
    if (left != nullptr || right != nullptr) return;

    // create new node objects
    left = new BSPNode(size_limit, size_min, this);
    right = new BSPNode(size_limit, size_min, this);
    ResizeChildBounds();

    // place containing boids into child nodes and mark them as "to remove"
    for (int i = boids.size() - 1; i >= 0; i--) {
        Boid* boid = boids[i];
        Vector2i boid_pos = (Vector2i)boid->get_position();

        if (left->get_bounds().contains(boid_pos)) {
            MoveBoidToNode(boid, left);
        } else if (right->get_bounds().contains(boid_pos)) {
            MoveBoidToNode(boid, right);
        }
    }
}

void BSPNode::Join() {
    // only do joining if children exist
    if (left != nullptr && right != nullptr) {
        // recursively join children
        left->Join();
        right->Join();

        // do joining process on this node
        left->MoveAllBoids(this);
        right->MoveAllBoids(this);

        // delete children
        delete left;
        delete right;
    }
}
*/

void BSPTree::BSPNode::MoveAllBoids(BSPNode* node) {
    if (parent == nullptr) return;

    for (int i = boids.size() - 1; i >= 0; i--) {
        Boid* boid = boids[i];
        boids.pop_back();
        parent->Add(boid);
    }
}

void BSPTree::BSPNode::MoveBoidToNode(Boid* boid, BSPNode* node) {
    // iterate to find index of inputted boid
    int index = 0;
    for (; index < boids.size(); index++) {
        if (boids[index] == boid) break;
    }

    // exit if not found (index is equal to size of array)
    if (index == boids.size()) return;

    // remove boid from this node and add to target node
    boids.erase(boids.begin() + index);
    node->Add(boid);
}

void BSPTree::BSPNode::ResizeChildBounds() {
    bool h_split = bounds.height > bounds.width;

    // if h_split == true, left node is on the top,
    //   else left node is to the left
    if (left != nullptr) {
        left->set_bounds(IntRect(
            bounds.left,
            bounds.top,
            h_split ? bounds.width : bounds.width / 2,
            h_split ? bounds.height / 2 : bounds.height
        ));
    }

    // if h_split == true, right node is on the bottom,
    //   else right node is to the right
    if (right != nullptr) {
        right->set_bounds(IntRect(
            h_split ? bounds.left : bounds.left + bounds.width / 2,
            h_split ? bounds.top + bounds.height / 2 : bounds.top,
            h_split ? bounds.width : bounds.width / 2,
            h_split ? bounds.height / 2 : bounds.height
        ));
    }
}

#pragma endregion

//*
//* BSPTree class definitions
//*

#pragma region

BSPTree::BSPTree(const sf::IntRect& bounds, int size_limit) {
    root = new BSPNode(bounds, size_limit);
}

BSPTree::~BSPTree() {
    delete root;
}

void BSPTree::Update(float delta_time, const IntRect& full_view) {
    root->Update(delta_time, full_view);
}

void BSPTree::Draw(RenderWindow& window) {
    root->Draw(window);
    if (draw_bounds) {
        root->DrawBounds(window);
    }
}

void BSPTree::Add(Boid* boid) {
    root->Add(boid);
}

#pragma endregion
