#include <SFML/Graphics.hpp>

#include <vector> // for circle shapes
#include <string> // for displaying values as text

#include "PXL8.h"

int main()
{
	// initial sizes
	const sf::Vector2u initWindowSize({ 800, 600 });
	const sf::Vector2f initViewSize({ 400, 300 });

	// window
	sf::RenderWindow window(sf::VideoMode(initWindowSize.x, initWindowSize.y), "PXL8 Example", sf::Style::Default);

	// current pixelation
	sf::Vector2f currentPixelSize({ 1.f, 1.f });

	// display switch
	bool displayImageInsteadOfCircles = false;

	// feedback text
	sf::Font font;
	if (!font.loadFromFile("font.ttf"))
		return EXIT_FAILURE;
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(20, 20);
	text.setColor(sf::Color::White);

	// image sprite
	sf::Texture texture;
	if (!texture.loadFromFile("image.jpg"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	sprite.setScale(initViewSize.x / texture.getSize().x, initViewSize.y / texture.getSize().y); // scale image to match view

	// circles
	srand(static_cast<unsigned int>(time(NULL)));
	const sf::Vector2f sixteenth(initViewSize.x / 4, initViewSize.y / 4); // size of a sixteeth of the view (4x4)
	std::vector<sf::CircleShape> circles, smallCircles;
	for (unsigned int cy = 0; cy < 4; cy++)
	{
		for (unsigned int cx = 0; cx < 4; cx++)
		{
			// main circles
			const float radius = (sixteenth.x < sixteenth.y) ? sixteenth.x / 2 : sixteenth.y / 2; // make sure circle's size stays within "sixteenth" regardless of aspect ratio
			sf::CircleShape newCircle(radius);
			newCircle.setOrigin(radius, radius);
			newCircle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
			newCircle.setPosition((cx * sixteenth.x) + sixteenth.x / 2, (cy * sixteenth.y) + sixteenth.y / 2);
			newCircle.setOutlineColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
			newCircle.setOutlineThickness(-4);
			circles.push_back(newCircle);

			// small circles
			if ((cy > 0) && (cx > 0))
			{
				const float smallRadius = radius * 0.7f;
				newCircle.setRadius(smallRadius);
				newCircle.setOrigin(smallRadius, smallRadius);
				newCircle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
				newCircle.setPosition(cx * sixteenth.x, cy * sixteenth.y);
				newCircle.setOutlineThickness(2);
				smallCircles.push_back(newCircle);
			}
		}
	}

	// main loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				window.close();
			else if (event.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height)))); // resize window view to match window size
			else if (event.type == sf::Event::KeyPressed)
			{
				// BACKSPACE = reset pixelation (reset pixel size to 1x1)
				if (event.key.code == sf::Keyboard::BackSpace)
					currentPixelSize = { 1.f, 1.f };
				// 1 2 = adjust pixelation (pixel size)
				else if (event.key.code == sf::Keyboard::Num1)
					currentPixelSize /= 1.1f;
				else if (event.key.code == sf::Keyboard::Num2)
					currentPixelSize *= 1.1f;
				// 3 4 = adjust pixelation (pixel size) (width only)
				else if (event.key.code == sf::Keyboard::Num3)
					currentPixelSize.x /= 1.1f;
				else if (event.key.code == sf::Keyboard::Num4)
					currentPixelSize.x *= 1.1f;
				// 5 6 = adjust pixelation (pixel size) (height only)
				else if (event.key.code == sf::Keyboard::Num5)
					currentPixelSize.y /= 1.1f;
				else if (event.key.code == sf::Keyboard::Num6)
					currentPixelSize.y *= 1.1f;
				// SPACE = switch between image and circles displayed
				else if (event.key.code == sf::Keyboard::Space)
					displayImageInsteadOfCircles = !displayImageInsteadOfCircles;
				// ENTER = new random circle colours
				else if (event.key.code == sf::Keyboard::Return)
				{
					for (auto& circle : circles)
						circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
					for (auto& smallCircle : smallCircles)
						smallCircle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
				}
			}
		}

		/*
		PXL8 required code block:

		PXL8 pxl8({ window.getSize().x, window.getSize().y }); // size should always be specified but defaults to (800, 600)
		pxl8.setPixelSize(2.f); // defaults to 1.f (no pixelation). can specify single or dual dimensions. single as a float, dual in a sf::vector2f i.e. setPixelSize({ 3.f, 2.f });
		pxl8.prepare();
		pxl8.draw(stuff); // draw stuff
		pxl8.apply();
		*/

		// PXL8 setup
		PXL8 pxl8({ window.getSize().x, window.getSize().y });
		pxl8.setPixelSize(currentPixelSize);
		pxl8.prepare();
		pxl8.setViewRect(sf::FloatRect(0, 0, initViewSize.x, initViewSize.y)); // setView/setViewRect is not necessary. if not specified, uses size given via setSize()
		pxl8.clear(sf::Color::Blue); // clear is not necessary. automatically clears with black. the clear colour can be changed with setClearColor() before prepare()

		// PXL8 draw
		if (displayImageInsteadOfCircles)
			pxl8.draw(sprite);
		else
		{
			for (auto& smallCircle : smallCircles)
				pxl8.draw(smallCircle);
			for (auto& circle : circles)
				pxl8.draw(circle);
		}

		// PXL8 finalise
		pxl8.apply();

		// update text string
		text.setString("Pixel width: " + std::to_string(pxl8.getPixelSize().x) + "\nPixel height: " + std::to_string(pxl8.getPixelSize().y));

		// window update
		window.clear();
		window.draw(pxl8.finalRender); // draw PXL8's render
		text.setColor(sf::Color::Black); // text outline
		const unsigned int outlineAngleSteps = 8;
		for (unsigned int a = 0; a < outlineAngleSteps; ++a)
		{
			const float currentAngle = 3.141592653589793238462643383279502f * a * 2 / outlineAngleSteps;
			text.move(round(sin(currentAngle)), round(cos(currentAngle)));
			window.draw(text);
			text.move(-round(sin(currentAngle)), -round(cos(currentAngle)));
		}
		text.setColor(sf::Color::White); // actual text
		window.draw(text); // draw text over PXL8's render using window's own view
		window.display();
	}

	return EXIT_SUCCESS;
}