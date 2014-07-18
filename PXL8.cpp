#include "PXL8.h"


PXL8::PXL8()
{
}


PXL8::PXL8(sf::Vector2u size)
{
	setSize(size);
}


void PXL8::prepare()
{
	m_view.reset({ 0, 0, static_cast<float>(m_size.x), static_cast<float>(m_size.y) });
	m_texture.create((m_size.x / m_pixelSize.x) + 1, (m_size.y / m_pixelSize.y) + 1);
	m_texture.setView(m_view);
	m_texture.clear(m_clearColor);
}

void PXL8::setView(sf::View view)
{
	m_view.reset({ 0, 0, view.getSize().x, view.getSize().y });
	m_texture.setView(view);
}

void PXL8::setViewRect(sf::FloatRect viewRect)
{
	m_view.reset(viewRect);
	m_texture.setView(m_view);
}

void PXL8::clear(sf::Color colour)
{
	m_texture.clear(colour);
}

void PXL8::clear()
{
	clear(m_clearColor);
}

void PXL8::draw(sf::Drawable& drawable)
{
	m_texture.draw(drawable);
}

void PXL8::apply()
{
	m_texture.display();
	finalRender.setTexture(m_texture.getTexture());
	finalRender.setScale(m_pixelSize.x, m_pixelSize.y);
}

void PXL8::setSize(sf::Vector2u size)
{
	m_size = size;
}

void PXL8::setClearColor(sf::Color colour)
{
	m_clearColor = colour;
}

void PXL8::setPixelSize(sf::Vector2f ratio)
{
	m_pixelSize = ratio;
}

void PXL8::setPixelSize(float ratio)
{
	m_pixelSize = { ratio, ratio };
}

sf::Vector2u PXL8::getSize()
{
	return m_size;
}

sf::Vector2f PXL8::getPixelSize()
{
	return m_pixelSize;
}
