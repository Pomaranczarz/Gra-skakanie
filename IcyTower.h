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

		//================ Basics =================
		void set_window();

		void set_background() { this->background.setTexture(this->backgroundTex); }

		void events();

		void set_points_text();

		void load_textures();
		
		void lvl_up() { this->lvl++; this->p_counter = 0; }

		void update_text() { this->pointsText.setString("Points: " + std::to_string(this->points)); }

		//================ Player =================
		void set_player();

		//player's movement
		void player_movement();

		//player's hitboxes
		bool p_hitbox();

		//jump delay
		void up();

		//jumping
		void jump();

		//================ Platforms =================
		void set_platform();

		//adding single platform
		void add_platform();

		//moving platforms
		void move_platforms();

		//adding platforms
		void respawn_platforms();

		//platforms' hitboxes with player
		void hitbox();

		//drawing platforms
		void draw_platforms(sf::RenderTarget& window) { for (auto i : this->platforms) window.draw(i); }

	public:
		IcyTower();

		//================ Render =================
		void draw();

		//================ Update =================
		void update();

		const bool is_working() const { return this->window->isOpen(); }

		~IcyTower() { delete this->window; }
};

