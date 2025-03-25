#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const sf::Texture& texture, sf::Vector2f position)
    {
        m_sprite.setTexture(texture);
        m_sprite.setPosition(position);
    }

    bool IsMouseOver(sf::Vector2f mousePos) const
    {
        return m_sprite.getGlobalBounds().contains(mousePos);
    }

    void SetTexture(const sf::Texture& texture)
    {
        m_sprite.setTexture(texture);
    }

    void SetScale(const sf::Vector2f scale)
    {
        m_sprite.setScale(scale);
    }

    void SetOrigin(const sf::Vector2f origin)
    {
        m_sprite.setOrigin(origin);
    }

    void SetOriginToCenter()
    {
        sf::Vector2u spriteSize = m_sprite.getTexture()->getSize();
        m_sprite.setOrigin(spriteSize.x/2, spriteSize.y/2);
    }

    const sf::Sprite& GetSprite() const
    {
        return m_sprite;
    }

private:
    sf::Sprite m_sprite;
};

#endif
