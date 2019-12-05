#include "Game.h"
#include "Sprite.h"

#define fullscreen 0




void ToggleFullscreen(SDL_Window* Window) {
	
}

Game::Game()
{
	window.Init("test", Game::width, Game::height);
	
	first_state = new State();//add a new state
	second_state = new State();

	set_state(first_state);
	first_state->get_camera()->set_dimensions(960, 800);
	set_state(second_state);
	SDL_RenderSetLogicalSize(Game::window.renderer, Game::cur_state->get_camera().get()->rect.w, Game::cur_state->get_camera().get()->rect.h);
}

void Game::Init()
{
	SDL_Color color = { 255,0 ,255 ,255 };
	second_state->norge = new Text_Sprite({0,0,200,200}, "assets/font.ttf", 32, "Aldo adsadshbadsh gbaytu gvasty dvastyadsvtyvdasty ilea   ",color );
	first_state->norge = new Text_Sprite({ 0,0,200,200 }, "assets/font.ttf", 32, "Primul morge", color);
	
}

void Game::create_window(const std::string& name, const int& width, const int& height)
{

	//also creates the renderer, because why not?
	/*
	if (s_window != nullptr)//delete currewnt windows if there is one
	{
		SDL_DestroyRenderer(Game::renderer);
		SDL_DestroyWindow(Game::s_window);

	}
	s_window = SDL_CreateWindow(name.c_str(),
	 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(s_window, -1, 0);
	
	*/
}

void Game::set_state(State* new_state)
{
	cur_state = new_state;
	SDL_RenderSetLogicalSize(Game::window.renderer, new_state->get_camera().get()->rect.w, new_state->get_camera().get()->rect.h); // set the render size to the new state's camera

}

void Game::Update(const unsigned int& dt )
{
	//move camera

	unsigned char const* keys = SDL_GetKeyboardState(nullptr);
	if (keys[SDL_SCANCODE_UP])
	{
		Game::cur_state->get_camera().get()->set_dimensions(Game::cur_state->get_camera().get()->rect.w + 12, Game::cur_state->get_camera().get()->rect.h + 10);
	}
	else if (keys[SDL_SCANCODE_DOWN])
	{
		Game::cur_state->get_camera().get()->set_dimensions(Game::cur_state->get_camera().get()->rect.w - 12, Game::cur_state->get_camera().get()->rect.h - 10);
	}
	else if (keys[SDL_SCANCODE_W])
	{
		Game::cur_state->get_camera().get()->set_position(Game::cur_state->get_camera().get()->rect.x, Game::cur_state->get_camera().get()->rect.y - 10);
	}
	else if (keys[SDL_SCANCODE_S])
	{
		Game::cur_state->get_camera().get()->set_position(Game::cur_state->get_camera().get()->rect.x , Game::cur_state->get_camera().get()->rect.y + 10);
	}
	else if (keys[SDL_SCANCODE_A])
	{
		Game::cur_state->get_camera().get()->set_position(Game::cur_state->get_camera().get()->rect.x - 10, Game::cur_state->get_camera().get()->rect.y);
	}
	else if (keys[SDL_SCANCODE_D])
	{
		Game::cur_state->get_camera().get()->set_position(Game::cur_state->get_camera().get()->rect.x + 10, Game::cur_state->get_camera().get()->rect.y);
	}
	else if (keys[SDL_SCANCODE_RIGHT])
	{
		set_state(second_state);
	}
	else if (keys[SDL_SCANCODE_LEFT])
	{
		set_state(first_state);
	}




	cur_state->Update(Game::dt);


}

void Game::handlevents()
{


}

void Game::render()
{
	
	//SDL_RenderClear(Game::renderer);

	cur_state->Render();

	//SDL_RenderPresent(Game::renderer);

}

