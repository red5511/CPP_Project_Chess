#include "ChessGame.h"

int main()
{
	sf::Sprite onlineSprite, computerSprite, exitSprite;
	int width = 840;


	int height = 840;


	sf::RenderWindow window(sf::VideoMode(width, height), "Chess Online");


	onlineSprite.setTextureRect(sf::IntRect(0, 0, 182, 49));
	exitSprite.setTextureRect(sf::IntRect(0, 0, 98, 49));
	computerSprite.setTextureRect(sf::IntRect(0, 0, 242, 49));


	computerSprite.setPosition(width / 2 - 100 - 30, height / 2 - 80);
	onlineSprite.setPosition(width / 2 - 100, height / 2 - 80 + 80);
	exitSprite.setPosition(width/2-100+40, height/2-80+160);

	sf::Event event;

	sf::Texture onlineTexture, computerTexture, exitTexture, background;
	onlineTexture.loadFromFile("online.png");
	computerTexture.loadFromFile("computer.png");
	exitTexture.loadFromFile("exit.png");
	background.loadFromFile("rsz_background.png");

	onlineSprite.setTexture(onlineTexture);
	computerSprite.setTexture(computerTexture);
	exitSprite.setTexture(exitTexture);

	sf::Sprite bck(background);


	

	while (window.isOpen()) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left)
					if(onlineSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						game(true);
					}
					else if (computerSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						game(false);
					}
					else if (exitSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						window.close();
					}

			if (onlineSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
			{
				onlineSprite.setColor(sf::Color(255, 0, 0, 125));
			}
			else
			{
				onlineSprite.setColor(sf::Color(255, 255, 255, 255));
			}

			if (exitSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
			{
				exitSprite.setColor(sf::Color(255, 0, 0, 125));
			}
			else
			{
				exitSprite.setColor(sf::Color(255, 255, 255, 255));
			}

			if (computerSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
			{
				computerSprite.setColor(sf::Color(255, 0, 0, 125));
			}
			else
			{
				computerSprite.setColor(sf::Color(255, 255, 255, 255));
			}
		}
		window.clear();
		window.draw(bck);
		window.draw(onlineSprite);
		window.draw(computerSprite);
		window.draw(exitSprite);
		window.display();
	}


	return 0;
}