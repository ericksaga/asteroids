#include "App.hpp"
#include <iostream>
#include <algorithm>

#include "Palet.h"

#include "GLIncludes.hpp"

irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();

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
		Missile LC_get_points;
		srand((int)time(0));
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
		LoadEntity();
		SoundEngine->setSoundVolume(0.5f);
		m_live_points = m_player->GetShipPoints();
		m_missile_points = LC_get_points.GetMissilePoints();
	}

	App::~App()
	{
		CleanupSDL();
		EntityCleaner();
		SoundEngine->removeAllSoundSources();
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
		bool success = SDLInit() && GlewInit() && TTFInit();
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
			m_manager.SetW(true);
			break;
		case SDL_SCANCODE_A:
			m_manager.SetA(true);
			break;
		case SDL_SCANCODE_D:
			m_manager.SetD(true);
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
			if (m_debug)
			{
				for (int x = 0; x < m_asteroid.size(); x++)
				{
					m_asteroid[x]->ChangeSize();
				}
			}
			break;
		case SDL_SCANCODE_Q:
			if (m_debug)
			{
				GenerateAsteroid();
			}
			break;
		case SDL_SCANCODE_E:
			if (m_asteroid.size() >= 1 && m_debug)
			{
				m_asteroid.pop_back();
			}
			break;
		case SDL_SCANCODE_R:
			if (m_debug)
			{
				m_debug = false;
			}
			else
			{
				m_debug = true;
				m_player->dead = false;
			}
			break;
		case SDL_SCANCODE_SPACE:
			if (!m_respawn_player && !m_pause)
			{
				m_bullet.push_back(new Bullet(m_player->GetEntityAngle(), m_player));
				SoundEngine->play2D("sounds/fire.wav");
			}
			break;
		case SDL_SCANCODE_F:
			if (m_frame)
			{
				m_frame = false;
			}
			else
			{
				m_frame = true;
			}
			SDL_Log("%f was pressed.", m_delta_time);
			break;
		case SDL_SCANCODE_H:
			EntityCleaner();
			LoadEntity();
			SoundEngine->stopAllSounds();
			SoundEngine->removeAllSoundSources();
			break;
		case SDL_SCANCODE_M:
			if (!m_respawn_player && m_missile_counter > 0)
			{
				SoundEngine->play2D("sounds/Torpedosound.mp3");
				m_missile.push_back(new Missile(m_player->GetEntityAngle(), m_player));
				m_missile_counter--;
			}
			break;
		case SDL_SCANCODE_P:
			if (!m_pause)
			{
				m_pause = true;
			}
			else
			{
				m_pause = false;
			}
			break;
		case SDL_SCANCODE_W:
			m_manager.SetW(false);
			break;
		case SDL_SCANCODE_A:
			m_manager.SetA(false);
			break;
		case SDL_SCANCODE_D:
			m_manager.SetD(false);
			break;
		default:
			//DO NOTHING
			break;
		}
	}

	void App::ManageInput()
	{
		if (m_manager.GetW())
		{
			m_player->MoveForward();
			SoundEngine->play2D("sounds/thrust.wav");
		}
		if (m_manager.GetA())
		{
			m_player->RotateLeft();
		}
		if (m_manager.GetD())
		{
			m_player->RotateRight();
		}
	}

	void App::UpdateWarp()
	{
		m_player->UpdateWarp(m_width, m_height);
		for (int x = 0; x < m_asteroid.size(); x++)
		{
			m_asteroid[x]->UpdateWarp(m_width, m_height);
		}
		for (int x = 0; x < m_bullet.size(); x++)
		{
			m_bullet[x]->UpdateWarp(m_width, m_height);
		}
		for (int x = 0; x < m_missile.size(); x++)
		{
			m_missile[x]->UpdateWarp(m_width, m_height);
		}
	}

	void App::UpdateEntity()
	{
		if (!m_player->GetInmortal())
		{
			m_respawn_player = false;
		}
		UpdateWarp();
		m_player->Update((float)m_delta_time);
		//update the player debugging state
		m_player->ChangeDebuggingState(m_debug);
		for (int x = 0; x < m_asteroid.size();x++)
		{
			m_asteroid[x]->Update((float)m_delta_time);
			//update the asteroid debugging state
			m_asteroid[x]->ChangeDebuggingState(m_debug);
		}
		for (int x = 0; x < m_bullet.size(); x++)
		{
			m_bullet[x]->Update((float)m_delta_time);
			//update the bullet debugging state
			m_bullet[x]->ChangeDebuggingState(m_debug);
		}
		for (int x = 0; x < m_missile.size(); x++)
		{
			m_missile[x]->Update((float)m_delta_time);
			//update the missile debugging state
			m_missile[x]->ChangeDebuggingState(m_debug);
		}
		//check collisions on normal gameplay
		if (!m_debug && !m_out_of_live)
		{
			CheckCollision();
		}
		//check collision in debugging mode
		if (m_debug)
		{
			DebugCollision();
		}
		BulletCleanUp();
		if (m_clear_screen)
		{
			m_clear_screen = false;
			m_asteroids_count++;
			m_missile_counter++;
			for (int x = 0; x < m_asteroids_count; x++)
			{
				GenerateAsteroid();
			}
		}
		if (m_live <= 0 && !m_out_of_live)
		{
			m_out_of_live = true;
			SoundEngine->play2D("sounds/quacksoundeffect.mp3",GL_TRUE);

		}
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
		if (!m_pause)
		{
			ManageInput();
			UpdateEntity();
			if (m_player->dead)
			{
				delete m_player;
				m_player = new Player();
				m_player->ActivateInmortal((float)startTime);
			}
			if (m_respawn_player)
			{
				m_player->CheckInmortal((float)startTime);
			}
		}
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
				DebugMissileCollision(x);
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
		for (int x = 0; x < m_missile.size(); x++)
		{	
			m_missile[x]->Render();
		}
	}

	void App::RenderLive()
	{
		float LC_size_factor = 0.4f;
		float LC_half_width = (float)m_width / 2.0f;
		float LC_half_height = (float)m_height / 2.0f;
		glLoadIdentity();
		glTranslatef(LC_half_width, LC_half_height, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int y = 0; y < m_live; y++)
		{
			glBegin(GL_LINE_LOOP);
			for (int x = 0; x < m_live_points.size(); x++)
			{
				glVertex2f(LC_size_factor*m_live_points[x].x - 30 * (y + 1),
					LC_size_factor*m_live_points[x].y - 20);
			}
			glEnd();
		}
	}

	void App::RenderMissile()
	{
		float LC_size_factor = 1.3f;
		float LC_half_width = (float)m_width / 2.0f;
		float LC_half_height = (float)m_height / 2.0f;
		glLoadIdentity();
		glTranslatef(-LC_half_width, -LC_half_height, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int y = 0; y < m_missile_counter; y++)
		{
			glBegin(GL_LINE_LOOP);
			for (int x = 0; x < m_missile_points.size(); x++)
			{
				glVertex2f(LC_size_factor*m_missile_points[x].x + 15 * (y + 1),
					LC_size_factor*m_missile_points[x].y + 10);
			}
			glEnd();
		}
	}

	void App::Render()
	{
		glClearColor(stats.red, stats.green, stats.blue, stats.alpha);
		glClear(GL_COLOR_BUFFER_BIT);
		RenderEntity();
		RenderLive();
		RenderMissile();
		if (m_frame)
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

	bool App::TTFInit()
	{
		if (TTF_Init() == -1) {
			SDL_Log("TTF_Init: %s\n", TTF_GetError());
			return false;
		}
		
		SDL_version compile_version;
		const SDL_version *link_version = TTF_Linked_Version();
		SDL_TTF_VERSION(&compile_version);

		SDL_Log("compiled with SDL_ttf version: %d.%d.%d\n",
			compile_version.major,
			compile_version.minor,
			compile_version.patch);

		SDL_Log("running with SDL_ttf version: %d.%d.%d\n",
			link_version->major,
			link_version->minor,
			link_version->patch);
		return true;
	}

	void App::CleanupSDL()
	{
		// Cleanup
		//
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_mainWindow);

		SDL_Quit();

		TTF_Quit();
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
		for (int x = 0; x < m_missile.size(); x++)
		{
			delete m_missile[x];
		}
		m_asteroid.clear();
		m_bullet.clear();
		m_missile.clear();
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
		m_asteroid[m_asteroid.size() - 1]->AssignPosition(rand(), rand(), m_width, m_height);
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
			m_live--;
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
					if (m_asteroid[asteroid_position]->GetSize() == 4)
					{
						SoundEngine->play2D("sounds/bangLarge.wav");
					}
					else
					{
						SoundEngine->play2D("sounds/bangMedium.wav");
					}
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
					SoundEngine->play2D("sounds/bangSmall.wav");
				}
				//only one collision is necesary in the player or bullet case
				return true;
			}
		}
		return false;
	}

	bool App::MissileCollision(int asteroid_position)
	{
		for (int x = 0; x < m_missile.size(); x++)
		{
			//get the distance between every bullet and every asteroid on the screen
			float LC_distance = m_missile[x]->GetOrigin().VectorialDistance(m_asteroid[asteroid_position]->GetOrigin());
			if (LC_distance <= m_missile[x]->GetEntityRadius() + m_asteroid[asteroid_position]->GetEntityRadius())
			{
				//erase the colliding bullet
				m_missile.erase(m_missile.begin() + x);
				if (m_asteroid[asteroid_position]->GetSize() == 4)
				{
					SoundEngine->play2D("sounds/bangLarge.wav");
				}
				else if(m_asteroid[asteroid_position]->GetSize() == 3)
				{
					SoundEngine->play2D("sounds/bangMedium.wav");
				}
				else
				{
					SoundEngine->play2D("sounds/bangSmall.wav");
				}
				delete m_asteroid[asteroid_position];
				m_asteroid.erase(m_asteroid.begin() + asteroid_position);
				
			
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
			if (BulletCollision(pos) || MissileCollision(pos))
			{
				//SoundEngine->play2D("sounds/explosion.wav");
				break;
			}
			if (!m_respawn_player && PlayerCollision(pos))
			{
				m_respawn_player = true;
				SoundEngine->play2D("sounds/megamandeathsound.mp3");
				break;
			}
		}
		if (m_asteroid.size() <= 0)
		{
			m_clear_screen = true;
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

	void App::DebugMissileCollision(int asteroid_position)
	{
		for (int x = 0; x < m_missile.size(); x++)
		{
			//get the distance between the bullets and every asteroid on the screen
			float LC_distance = m_missile[x]->GetOrigin().VectorialDistance(m_asteroid[asteroid_position]->GetOrigin());
			/*check in a 2 times radius of the player if it's on range the asteroid get marked and
			render a line between the ship and the asteroid*/
			if (LC_distance <= 2 * m_missile[x]->GetEntityRadius() + m_asteroid[asteroid_position]->GetEntityRadius())
			{
				//mark the bullet and render the line between the colliding bullet and the asteroid
				m_asteroid[asteroid_position]->CheckBulletDistance(true);
				//it doesnt render on update, only when called on render
				m_asteroid[asteroid_position]->DebugLine(m_missile[x]->GetOrigin());
			}
			if (LC_distance <= m_missile[x]->GetEntityRadius() + m_asteroid[asteroid_position]->GetEntityRadius())
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
			DebugMissileCollision(pos);
		}
	}

	void App::BulletCleanUp()
	{
		//cleanup expired bullets
		for (int x = 0; x < m_bullet.size(); x++)
		{
			if (m_bullet[x]->GetScreenTime() >= MAX_SCREEN_TIME_BULLETS)
			{
				delete m_bullet[x];
				m_bullet.erase(m_bullet.begin() + x);
				break;
			}
		}
		//cleanup expired missiles
		for (int x = 0; x < m_missile.size();x++)
		{
			if (m_missile[x]->GetScreenTime() >= MAX_SCREEN_TIME_MISSILES)
			{
				delete m_missile[x];
				m_missile.erase(m_missile.begin() + x);
				break;
			}
		}
	}

	void App::LoadEntity()
	{
		//Load game initial state
		m_debug = false;
		m_frame = false;
		m_clear_screen = false;
		m_out_of_live = false;
		m_pause = false;
		m_respawn_player = false;
		m_player = new Player();
		m_asteroids_count = 0;
		m_live = 3;
		m_missile_counter = 2;
		for (int x = 0; x < FRAME_LIMIT; x++)
		{
			m_frames[x] = Vector2((float)x, 0.0f);
		}
		m_frame_pos = 0;
		m_delta_time = DESIRED_FRAME_RATE;
	}
}