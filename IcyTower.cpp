#include "IcyTower.h"
void IcyTower::set_window()
{
	this->window = nullptr;
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Astronaut game", sf::Style::Default);
	this->window->setFramerateLimit(60);
}

void IcyTower::events()
{
	while (this->window->pollEvent(this->e))
	{
		if (this->e.type == sf::Event::Closed)
			this->window->close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->window->close();
	}
}

void IcyTower::set_points_text()
{
	this->font.loadFromFile("arial.ttf");
	this->pointsText.setFont(this->font);
	this->pointsText.setString("Sample points text");
	this->pointsText.setCharacterSize(15.f);
	this->pointsText.setPosition(5.f, 20.f);
}

void IcyTower::load_textures()
{
	this->playerTex.loadFromFile("astronaut.png");
	this->platformTex.loadFromFile("laser.png");
	this->backgroundTex.loadFromFile("space.jpg");
}

void IcyTower::set_player()
{
	this->points = 0;
	this->lvl = 0;
	this->deathCounter = 0;
	this->floor_hitbox = false;
	this->jumpDelay = 0;
	this->verticalV = 0;
	this->is_space = false;
	this->player.setTexture(this->playerTex);
	this->player.setPosition(this->window->getSize().x / 2, this->window->getSize().y - this->player.getGlobalBounds().height);
}

void IcyTower::player_movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->player.getPosition().x >= 0.f)
		this->player.move(-8.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->player.getPosition().x + this->player.getGlobalBounds().width <= this->window->getSize().x)
		this->player.move(8.f, 0.f);
}

bool IcyTower::p_hitbox()
{
	if (this->player.getPosition().y + this->player.getGlobalBounds().height >= this->window->getSize().y)
	{
		if (!this->floor_hitbox)
			return true;
		if (this->floor_hitbox)
			this->window->close();
	}

	for (size_t i = 0; i < this->platforms.size(); i++)
		if (this->player.getGlobalBounds().intersects(this->platforms[i].getGlobalBounds()))
			return true;

	return false;
}

void IcyTower::up()
{
	if (this->jumpDelay < 20)
		this->jumpDelay++;
	if (this->jumpDelay >= 20 && this->p_hitbox())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			this->verticalV = -25.f;
			this->jumpDelay = 0;
		}
	}
}

void IcyTower::jump()
{
	this->player.move(0.f, this->verticalV);
	if (this->verticalV < 0.f)
		this->verticalV += 0.6f;
	this->verticalV++;
	if (this->player.getPosition().y + this->player.getGlobalBounds().height >= this->window->getSize().y)
	{
		this->player.setPosition(this->player.getPosition().x, this->window->getSize().y - this->player.getGlobalBounds().height);
	}
}

void IcyTower::set_platform()
{
	this->p_Delay = 0;
	this->platform.setTexture(this->platformTex);
	this->platform.setPosition(this->window->getSize().x / 2, this->window->getSize().y - 200.f);
}

void IcyTower::add_platform()
{
	this->platform.setPosition(rand() % int(this->window->getSize().x - this->platform.getGlobalBounds().width), 0.f);
	this->platforms.push_back(this->platform);
}

void IcyTower::move_platforms()
{
	for (size_t i = 0; i < this->platforms.size(); i++)
	{
		this->platforms[i].move(0.f, 4.f + this->lvl * 0.1);
		if (this->platforms[i].getPosition().y > this->window->getSize().y)
		{
			this->platforms.erase(this->platforms.begin() + i);
			this->points++;
			this->p_counter++;
			if (this->p_counter >= 10)
				this->lvl_up();
		}
	}
}

void IcyTower::respawn_platforms()
{
	if (this->p_Delay < 60 - this->lvl * 0.5)
		this->p_Delay++;
	if (this->p_Delay >= 60 - this->lvl * 0.5)
	{
		this->add_platform();
		this->p_Delay = 0;
	}
}

void IcyTower::hitbox()
{
	for (size_t i = 0; i < this->platforms.size(); i++)
	{
		if (this->player.getGlobalBounds().intersects(this->platforms[i].getGlobalBounds()) && this->verticalV > 0)
		{
			this->player.setPosition(this->player.getPosition().x, this->platforms[i].getPosition().y - this->player.getGlobalBounds().height * 0.8);
			this->verticalV = 0.f;
		}
	}
}

IcyTower::IcyTower()
{
	this->set_points_text();
	this->set_window();
	this->load_textures();
	this->set_background();
	this->set_platform();
	this->set_player();
	this->add_platform();
}

void IcyTower::draw()
{
	this->window->clear();
	this->window->draw(this->background);
	this->draw_platforms(*this->window);
	this->window->draw(this->player);
	this->window->draw(this->pointsText);
	this->window->display();
}

void IcyTower::update()
{
	this->update_text();
	this->hitbox();
	this->respawn_platforms();
	this->events();
	this->move_platforms();
	this->player_movement();
	this->up();
	this->jump();
	if (this->deathCounter < 250)
		this->deathCounter++;
	if (this->deathCounter >= 150)
		this->floor_hitbox = true;
}

