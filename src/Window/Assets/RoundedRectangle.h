#pragma once
#include "SFML/Graphics.hpp"
#include <math.h>

class RoundedRectangle : public sf::Shape
{
public:
    virtual size_t getPointCount() const override
    {
        return m_cornerPointCount * 4; // Total points for 4 corners
    }

    virtual sf::Vector2f getPoint(size_t index) const override
    {
        if (m_cornerPointCount < 2 || m_radius <= 0.0f)
        {
            sf::RectangleShape rect(m_size);
            return rect.getPoint(index);
        }
        else
        {
            size_t corner = index / m_cornerPointCount;
            float angle = (index % m_cornerPointCount) * m_anglePerPoint;

            // Determine the center of the corner arc
            sf::Vector2f cornerCenter;
            switch (corner)
            {
            case 0: // Top-left corner
                cornerCenter = {m_radius, m_radius};
                angle += 180; // Rotate to face correct quadrant
                break;
            case 1: // Top-right corner
                cornerCenter = {m_size.x - m_radius, m_radius};
                angle += 270;
                break;
            case 2: // Bottom-right corner
                cornerCenter = {m_size.x - m_radius, m_size.y - m_radius};
                break;
            case 3: // Bottom-left corner
                cornerCenter = {m_radius, m_size.y - m_radius};
                angle += 90;
                break;
            }

            // Calculate the point on the arc
            sf::Vector2f point = cornerCenter +
                                 sf::Vector2f(cosf(angle * M_PI / 180) * m_radius,
                                              sinf(angle * M_PI / 180) * m_radius);

            return point;
        }
    }

    void setSize(sf::Vector2f size)
    {
        m_size = size;
        update();
    }

    sf::Vector2f getSize() const
    {
        return m_size;
    }

    void setRadius(float radius)
    {
        m_radius = radius;
        update();
    }

    float getRadius() const
    {
        return m_radius;
    }

    void setCornerPointCount(size_t points)
    {
        m_cornerPointCount = points;
        m_anglePerPoint = 90.0f / static_cast<float>(points);
        update();
    }

    size_t getCornerPointCount() const
    {
        return m_cornerPointCount;
    }

private:
    size_t m_cornerPointCount = 16; // Default for smooth corners
    float m_anglePerPoint = 90.0f / 16; // Angle step for each point
    float m_radius = 10.0f; // Default radius
    sf::Vector2f m_size = {100.0f, 50.0f}; // Default size
};
