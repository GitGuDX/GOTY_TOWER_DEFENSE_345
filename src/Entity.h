#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace sf;

class Entity : public Drawable
{
public:
    Entity();
    ~Entity();

	void SetTexture(const sf::Texture& texture)
	{
		m_Sprite.setTexture(texture);
	}

	void SetScale(const sf::Vector2f& scale)
	{
		m_Sprite.setScale(scale);
	}

	void SetOrigin(const sf::Vector2f& origin)
	{
		m_Sprite.setOrigin(origin);
	}

	void SetPosition(const sf::Vector2f& position)
	{
		m_Sprite.setPosition(position);
	}

	void SetColor(const sf::Color& color)
	{
		m_Sprite.setColor(color);
	}

	void SetSprite(const sf::Sprite& sprite)
	{
		m_Sprite = sprite;
	}

    void SetTextureRect(sf::IntRect intRectValue)
    {
        m_Sprite.setTextureRect(intRectValue);
    }

	sf::Vector2f GetPosition() const
	{
		return m_Sprite.getPosition();
	}

	sf::Vector2i GetClosestGridCoordinates() const
	{
		return sf::Vector2i(GetPosition().x / 160, GetPosition().y / 160);
	}

	const sf::Sprite& GetSprite() const
	{
		return m_Sprite;
	}

	sf::Sprite& GetSpriteNonConst()
	{
		return m_Sprite;
	}

	void Move(const sf::Vector2f& offset)
	{
		m_Sprite.move(offset);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(m_Sprite, states);
	}

    Vector2f GetOrigin()
    {
        return m_Sprite.getOrigin();
    }

    

public:
    Sprite m_Sprite;
	sf::Vector2f m_Direction;  // Store initial direction

  
   
};


#endif
