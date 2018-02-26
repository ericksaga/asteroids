#pragma once
#ifndef APP_HPP
#define APP_HPP

// C++ STL
#include <string>
#include <list>
#include <stdlib.h>
#include <time.h>
// Asteroids
#include "SDLEvent.hpp"
#include "TimeManager.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"

const int FRAME_LIMIT = 10;
const float FRAME_SCALE_Y = 10000.0f;
const float FRAME_SCALE_X = 20.0f;


namespace Engine
{
	class App : public SDLEvent
	{
	public:
		/* =============================================================
		* ENUMERATORS
		* ============================================================= */
		struct GameState
		{
			enum State
			{
				UNINITIALIZED = 0,
				INIT_FAILED = 1,
				INIT_SUCCESSFUL = 2,
				RUNNING = 4,
				PAUSED = 8,
				QUIT = 16
			};
		};

		/* =============================================================
		 * PUBLIC FUNCTIONS
		 * ============================================================= */
		App( const std::string& title, const int width, const int height );
		~App( );
		void Execute						( );
		bool Init							( );
		void Update							( );
		void Render							( );
	private:
		/* =============================================================
		 * PRIVATE FUNCTIONS
		 * ============================================================= */
		bool SDLInit						( );
		bool GlewInit						( );
		void SetupViewport					( );
		void CleanupSDL						( );
		void OnResize						( int width, int height ) override;
		void OnExit							( ) override;
		void OnKeyDown						( SDL_KeyboardEvent keyBoardEvent ) override;
		void OnKeyUp						( SDL_KeyboardEvent keyBoardEvent ) override;
		void GenerateAsteroid				();
		void GenerateAsteroidWithPosition	(Vector2, int);
		void LoadEntity						();
		void CheckCollision					();
		void DebugCollision					();
		void UpdateEntity					();
		void UpdateFrame					();
		void RenderEntity					();
		void FrameRender					();
		void EntityCleaner					();
		void BulletCleanUp					();
		void DebugPlayerCollision			(int);
		void DebugBulletCollision			(int);
		bool PlayerCollision				(int);
		bool BulletCollision				(int);
		/* =============================================================
		 * MEMBERS
		 * ============================================================= */
		int									m_width;
		int									m_height;
		int									m_nUpdates;
		double								m_lastFrameTime;
		bool								debug;
		bool								frame;
		std::string							m_title;
		SDL_Window*							m_mainWindow;
		SDL_GLContext						m_context;
		GameState::State					m_state;
		Engine::TimeManager*				m_timer;
		Player*								m_player;
		std::vector<Asteroid*>				m_asteroid;
		std::vector<Bullet*>				m_bullet;
		Vector2								m_frames[10];
		int									m_frame_pos;
		double								m_delta_time;
	};
}
#endif /* GAME_HPP */
