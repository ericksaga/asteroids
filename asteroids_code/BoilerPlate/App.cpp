#include "App.hpp"
#include <iostream>
#include <algorithm>

#include "Palet.h"

// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

namespace Engine
{
	const float DESIRED_FRAME_RATE = 60.0f;
	const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;
	Palet change;
	Color stats(0.1f, 0.1f, 0.15f, 1.0f);

	App::App(const std::string& title, const int width, const int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_nUpdates(0)
		, m_timer(new TimeManager)
		, m_mainWindow(nullptr)
	{
		srand((int)time(0));
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
		LoadEntity();
	}

	App::~App()
	{
		CleanupSDL();
		EntityCleaner();
	}

	void App::Execute()
	{
		if (m_state != GameState::INIT_SUCCESSFUL)
		{
			std::cerr << "Game INIT was not successful." << std::endl;
			return;
		}

		m_state = GameState::RUNNING;

		SDL_Event event;
		while (m_state == GameState::RUNNING)
		{
			// Input polling
			//
			while (SDL_PollEvent(&event))
			{
				OnEvent(&event);
			}

			//
			Update();
			Render();
		}
	}

	bool App::Init()
	{
		// Init the external dependencies
		//
		bool success = SDLInit() && GlewInit();
		if (!success)
		{
			m_state = GameState::INIT_FAILED;
			return false;
		}

		// Setup the viewport
		//
		SetupViewport();

		// Change game state
		//
		m_state = GameState::INIT_SUCCESSFUL;

		return true;
	}

	void App::OnKeyDown(SDL_KeyboardEvent keyBoardEvent)
	{		
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_W:
			m_player->MoveForward();
			break;
		case SDL_SCANCODE_A:
			m_player->RotateLeft();
			break;
		case SDL_SCANCODE_D:
			m_player->RotateRight();
			break;
		default:			
			SDL_Log("%S was pressed.", keyBoardEvent.keysym.scancode);
			break;
		}
	}

	void App::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			OnExit();
			break;
		case SDL_SCANCODE_C:
			stats = change.BlueScreen();
			break;
		case SDL_SCANCODE_V:
			stats = change.GreenScreen();
			break;
		case SDL_SCANCODE_X:
			stats = change.RedScreen();
			break;
		case SDL_SCANCODE_Z:
			stats = change.DarkBlueScreen();
			break;
		case SDL_SCANCODE_S:
			if (debug)
			{
				for (int x = 0; x < m_asteroid.size(); x++)
				{
					m_asteroid[x]->ChangeSize();
				}
			}
			break;
		case SDL_SCANCODE_Q:
			GenerateAsteroid();
			break;
		case SDL_SCANCODE_E:
			if (m_asteroid.size() >= 1)
			{
				m_asteroid.pop_back();
			}
			break;
		case SDL_SCANCODE_R:
			if (debug)
			{
				debug = false;
			}
			else
			{
				debug = true;
				m_player->dead = false;
			}
			break;
		case SDL_SCANCODE_T:
			delete m_player;
			m_player = new Player();
			break;
		case SDL_SCANCODE_SPACE:
			if (!m_player->dead)
			{
				m_bullet.push_back(new Bullet(m_player->GetEntityAngle(), m_player));
			}
			break;
		case SDL_SCANCODE_F:
			if (frame)
			{
				frame = false;
			}
			else
			{
				frame = true;
			}
			SDL_Log("%f was pressed.", m_delta_time);
			break;
		default:
			//DO NOTHING
			break;
		}
	}

	void App::UpdateEntity()
	{
		m_player->Update(m_width, m_height, (float)m_delta_time);
		//update the player debugging state
		m_player->ChangeDebuggingState(debug);
		for (int x = 0; x < m_asteroid.size();x++)
		{
			m_asteroid[x]->Update(m_width, m_height, (float)m_delta_time);
			//update the asteroid debugging state
			m_asteroid[x]->ChangeDebuggingState(debug);
		}
		for (int x = 0; x < m_bullet.size(); x++)
		{
			m_bullet[x]->Update(m_width, m_height, (float)m_delta_time);
			//update the bullet debugging state
			m_bullet[x]->ChangeDebuggingState(debug);
		}
		//check collisions on normal gameplay
		if (!debug)
		{
			CheckCollision();
		}
		//check collision in debugging mode
		if (debug)
		{
			DebugCollision();
		}
		BulletCleanUp();
	}

	void App::UpdateFrame()
	{
		m_frames[m_frame_pos] = Vector2((float)m_frame_pos, (float)m_delta_time);
		m_frame_pos++;
		if (m_frame_pos >= FRAME_LIMIT)
		{
			m_frame_pos = 0;
		}
	}

	void App::Update()
	{
		double startTime = m_timer->GetElapsedTimeInSeconds();

		// Update code goes here
		//
		UpdateEntity();
		double endTime = m_timer->GetElapsedTimeInSeconds();
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;
		
		m_delta_time = DESIRED_FRAME_TIME - (endTime - startTime);
		UpdateFrame();
		while (endTime < nextTimeFrame)
		{
			// Spin lock
			endTime = m_timer->GetElapsedTimeInSeconds();
		}
		//double elapsedTime = endTime - startTime;        
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();

		m_nUpdates++;
	}
	
	void App::FrameRender()
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		glLoadIdentity();
		glTranslatef(200.0f, -200.0f, 0.0f);
		//space render
		glBegin(GL_LINE_STRIP);
		glVertex2f(0.0f, 200.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(200.0f, 0.0f);
		glEnd();
		//stadistic render
		glBegin(GL_LINE_STRIP);
		for (int x = 0; x < FRAME_LIMIT; x++)
		{
			glVertex2f(FRAME_SCALE_X*m_frames[x].x, FRAME_SCALE_Y*(DESIRED_FRAME_TIME - m_frames[x].y));
		}
		glEnd();
	}

	void App::RenderEntity()
	{
		m_player->Render();
		for (int x = 0; x < m_asteroid.size(); x++)
		{
			m_asteroid[x]->Render();
			if (m_asteroid[x]->CloseToShip())
			{
				//trace the line to the player
				m_asteroid[x]->DebugLine(m_player->GetOrigin());
			}
			if (m_asteroid[x]->CloseToBullet())
			{
				DebugBulletCollision(x);
			}
			//clear line and color marks
			m_asteroid[x]->CheckShipDistance(false);
			m_asteroid[x]->AssignColide(false);
			m_asteroid[x]->CheckBulletDistance(false);
		}
		for (int x = 0; x < m_bullet.size(); x++)
		{
			m_bullet[x]->Render();
		}
	}

	void App::Render()
	{
		glClearColor(stats.red, stats.green, stats.blue, stats.alpha);
		glClear(GL_COLOR_BUFFER_BIT);
		RenderEntity();
		if (frame)
		{
			FrameRender();
		}
		SDL_GL_SwapWindow(m_mainWindow);
	}

	bool App::SDLInit()
	{
		// Initialize SDL's Video subsystem
		//
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cerr << "Failed to init SDL" << std::endl;
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Uint32 flags =  SDL_WINDOW_OPENGL     | 
						SDL_WINDOW_SHOWN      | 
						SDL_WINDOW_RESIZABLE;

		m_mainWindow = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			flags
		);

		if (!m_mainWindow)
		{
			std::cerr << "Failed to create window!" << std::endl;
			SDL_Quit();
			return false;
		}

		m_context = SDL_GL_CreateContext(m_mainWindow);
		SDL_GL_MakeCurrent(m_mainWindow, m_context);

		// Make double buffer interval synced with vertical scanline refresh
		SDL_GL_SetSwapInterval(0);

		return true;
	}

	void App::SetupViewport()
	{
		// Defining ortho values
		//
		float halfWidth = m_width * 0.5f;
		float halfHeight = m_height * 0.5f;

		// Set viewport to match window
		//
		glViewport(0, 0, m_width, m_height);

		// Set Mode to GL_PROJECTION
		//
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set projection MATRIX to ORTHO
		//
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1);

		// Setting Mode to GL_MODELVIEW
		//
		glMatrixMode(GL_MODELVIEW);
	}

	bool App::GlewInit()
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return false;
		}

		return true;
	}

	void App::CleanupSDL()
	{
		// Cleanup
		//
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_mainWindow);

		SDL_Quit();
	}

	void App::EntityCleaner()
	{
		//delete all entity on App destroyer
		delete m_player;
		for (int x = 0; x < m_asteroid.size(); x++)
		{
			delete m_asteroid[x];
		}
		for (int x = 0; x < m_bullet.size(); x++)
		{
			delete m_bullet[x];
		}
		m_asteroid.clear();
		m_bullet.clear();
	}

	void App::OnResize(int width, int height)
	{
		// TODO: Add resize functionality
		//
		m_width = width;
		m_height = height;

		SetupViewport();
	}

	void App::OnExit()
	{
		// Exit main for loop
		//
		m_state = GameState::QUIT;

		// Cleanup SDL pointers
		//
		CleanupSDL();
	}
	
	void App::GenerateAsteroid()
	{
		//generate a random angle and postion for the asteroid
		m_asteroid.push_back(new Asteroid());
		m_asteroid[m_asteroid.size() - 1]->AssignOrientation(rand());
		m_asteroid[m_asteroid.size() - 1]->AssignPosition(rand(), rand());
	}

	void App::GenerateAsteroidWithPosition(Vector2 position, int state)
	{
		//generate a random angle for the asteroid
		m_asteroid.push_back(new Asteroid(state));
		m_asteroid[m_asteroid.size() - 1]->AssignOrientation(rand());
		m_asteroid[m_asteroid.size() - 1]->AssignPosition(position);
	}

	bool App::PlayerCollision(int asteroid_position)
	{
		//get the distance between the player and every asteroid on the screen
		float LC_distance = m_player->GetOrigin().VectorialDistance(m_asteroid[asteroid_position]->GetOrigin());
		if (LC_distance <= m_player->GetEntityRadius() + m_asteroid[asteroid_position]->GetEntityRadius())
		{
			m_player->dead = true;
			//check asteroid size is different from small
			if (m_asteroid[asteroid_position]->GetSize() != 2)
			{
				/*if it's different change the size and create a new asteroid in the same position with
				the same state*/
				m_asteroid[asteroid_position]->ChangeSize();
				int LC_state = m_asteroid[asteroid_position]->GetSize();
				GenerateAsteroidWithPosition(m_asteroid[asteroid_position]->GetOrigin(), 
					m_asteroid[asteroid_position]->GetSize());
			}
			else
			{
				//if it's small the asteroids is deleted and remove the asteroid from the vector
				delete m_asteroid[asteroid_position];
				m_asteroid.erase(m_asteroid.begin() + asteroid_position);
			}
			//only one collision is necesary in the player or bullet case
			return true;
		}
		return false;
	}

	bool App::BulletCollision(int asteroid_position)
	{
		for (int x = 0; x < m_bullet.size(); x++)
		{
			//get the distance between every bullet and every asteroid on the screen
			float LC_distance = m_bullet[x]->GetOrigin().VectorialDistance(m_asteroid[asteroid_position]->GetOrigin());
			if (LC_distance <= m_bullet[x]->GetEntityRadius() + m_asteroid[asteroid_position]->GetEntityRadius())
			{
				//erase the colliding bullet
				m_bullet.erase(m_bullet.begin() + x);
				//check asteroid size is different from small
				if (m_asteroid[asteroid_position]->GetSize() != 2)
				{
					/*if it's different change the size and create a new asteroid in the same position with
					the same state*/
					m_asteroid[asteroid_position]->ChangeSize();
					int LC_state = m_asteroid[asteroid_position]->GetSize();
					GenerateAsteroidWithPosition(m_asteroid[asteroid_position]->GetOrigin(),
						m_asteroid[asteroid_position]->GetSize());
				}
				else
				{
					//if it's small the asteroids is deleted and remove the asteroid from the vector
					delete m_asteroid[asteroid_position];
					m_asteroid.erase(m_asteroid.begin() + asteroid_position);
				}
				//only one collision is necesary in the player or bullet case
				return true;
			}
		}
		return false;
	}

	void App::CheckCollision()
	{
		//check the collisions with the asteroids for player and bullet
		for (int pos = 0; pos < m_asteroid.size(); pos++)
		{
			if (BulletCollision(pos))
			{
				break;
			}
			if (!m_player->dead && PlayerCollision(pos))
			{
				break;
			}
		}
	}

	void App::DebugPlayerCollision(int asteroid_position)
	{
		//get the distance between the player and every asteroid on the screen
		float LC_distance = m_player->GetOrigin().VectorialDistance(m_asteroid[asteroid_position]->GetOrigin());
		/*check in a 2 times radius of the player if it's on range the asteroid get marked and
		render a line between the ship and the asteroid*/
		if (LC_distance <= 2 * m_player->GetEntityRadius() + m_asteroid[asteroid_position]->GetEntityRadius())
		{
			//marked for render the line to player
			m_asteroid[asteroid_position]->CheckShipDistance(true);
		}
		//if the asteroid is on colision range it gets marked and render the asteroid red
		if (LC_distance <= m_player->GetEntityRadius() + m_asteroid[asteroid_position]->GetEntityRadius())
		{
			//marked for red color
			m_asteroid[asteroid_position]->AssignColide(true);
		}
	}

	void App::DebugBulletCollision(int asteroid_position)
	{
		for (int x = 0; x < m_bullet.size(); x++)
		{
			//get the distance between the bullets and every asteroid on the screen
			float LC_distance = m_bullet[x]->GetOrigin().VectorialDistance(m_asteroid[asteroid_position]->GetOrigin());
			/*check in a 2 times radius of the player if it's on range the asteroid get marked and
			render a line between the ship and the asteroid*/
			if (LC_distance <= 2 * m_bullet[x]->GetEntityRadius() + m_asteroid[asteroid_position]->GetEntityRadius())
			{
				//mark the bullet and render the line between the colliding bullet and the asteroid
				m_asteroid[asteroid_position]->CheckBulletDistance(true);
				//it doesnt render on update, only when called on render
				m_asteroid[asteroid_position]->DebugLine(m_bullet[x]->GetOrigin());
			}
			if (LC_distance <= m_bullet[x]->GetEntityRadius() + m_asteroid[asteroid_position]->GetEntityRadius())
			{
				//marked for red color
				m_asteroid[asteroid_position]->AssignColide(true);
			}
		}
	}

	void App::DebugCollision()
	{
		//check collision on debugging
		for (int pos = 0; pos < m_asteroid.size(); pos++)
		{
			DebugPlayerCollision(pos);
			DebugBulletCollision(pos);
		}
	}

	void App::BulletCleanUp()
	{
		//cleanup expired bullets
		for (int x = 0; x < m_bullet.size(); x++)
		{
			if (m_bullet[x]->GetScreenTime() >= MAX_SCREEN_TIME)
			{
				m_bullet.erase(m_bullet.begin() + x);
				break;
			}
		}
	}

	void App::LoadEntity()
	{
		//Load game initial state
		debug = false;
		frame = false;
		m_player = new Player();
		GenerateAsteroid();
		for (int x = 0; x < FRAME_LIMIT; x++)
		{
			m_frames[x] = Vector2((float)x, 0.0f);
		}
		m_frame_pos = 0;
		m_delta_time = DESIRED_FRAME_RATE;
	}
}