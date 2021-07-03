#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class IcyTower
{
	private:
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event e;

		sf::Sprite player;
		sf::Texture playerTex;
		int jumpDelay;
		float verticalV;
		bool is_space;
		int deathCounter;
		bool floor_hitbox;
		int lvl;
		int points;

		int p_Delay;
		sf::Sprite platform;
		sf::Texture platformTex;
		std::vector<sf::Sprite> platforms;
		int p_counter;

		sf::Sprite background;
		sf::Texture backgroundTex;

		sf::Text pointsText;
		sf::Font font;

		void set_window();
		void set_background() { this->background.setTexture(this->backgroundTex); }
		void events();
		void set_points_text();
		void load_textures();
		void lvl_up() { this->lvl++; this->p_counter = 0; }
		void update_text() { this->pointsText.setString("Points: " + std::to_string(this->points)); }
	
		void set_player();
		void player_movement();
		bool p_hitbox();
		void up();
		void jump();
	
		void set_platform();
		void add_platform();
		void move_platforms();
		void respawn_platforms();
		void hitbox();
		void draw_platforms(sf::RenderTarget& window) { for (auto i : this->platforms) window.draw(i); }

	public:
		IcyTower();
		void draw();
		void update();
		const bool is_working() const { return this->window->isOpen(); }
		~IcyTower() { delete this->window; }
};

