#pragma once
#include "object.hpp"

class Rectangle : public Object {
    public:
        Point Intersect(Ray ray) override;

        Rectangle(float l, float w, float h) : length(l), width(w), height(h) {}

    private:
        float length;
        float width;
        float height;

};