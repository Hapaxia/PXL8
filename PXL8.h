/*

PXL8

by Hapax
github.com/hapaxia
July 2014

Creates a pixelated render target.

*/

#ifndef INC_PXL8_H
#define INC_PXL8_H

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>

class PXL8
{
public:
	sf::Sprite finalRender;

	PXL8();
	PXL8(sf::Vector2u size);

	void prepare();
	void setView(sf::View view);
	void setViewRect(sf::FloatRect viewRect);
	void clear();
	void clear(sf::Color colour);
	void draw(sf::Drawable& drawable);
	void apply();

	void setSize(sf::Vector2u size);
	void setPixelSize(sf::Vector2f size);
	void setPixelSize(float size);
	void setClearColor(sf::Color colour);
	sf::Vector2u getSize();
	sf::Vector2f getPixelSize();

private:
	sf::RenderTexture m_texture;
	sf::View m_view;
	sf::Vector2u m_size = { 800, 600 };
	sf::Vector2f m_pixelSize = { 1.f, 1.f };
	sf::Color m_clearColor = { 0, 0, 0 };
};

#endif // INC_PXL8_H