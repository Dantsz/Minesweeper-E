#include <Empaerior.h>
#include <main.h>
#include <random>
#include "Minesweeper.h"
//An example of what a application might look like

//a user defined state
bool touched_mine = false;
class APP_State1 : public Empaerior::State
{

public:

	APP_State1()
	{



		Empaerior::Window_Functions::change_window_name(Empaerior::Application::window, "Minesweeper");

		//INITIALIZE THE ECS
		ecs.Init();

		//set the camera
		camera = { 0,0,480,400 };

		//REGISTER SOME COMPONENTS
		ecs.register_component<Empaerior::Sprite_Component>();
		ecs.register_component<Empaerior::Event_Listener_Component>();

		//CREATE SOME SYSTEMS TO USE THE COMPONENTS
		spr_system = ecs.register_system <Empaerior::Sprite_System>();
		event_system = ecs.register_system<Empaerior::Event_System>();
		mine_system = ecs.register_system<Mine_sweep_system>();
		//SPECIFIY WHAT TYPES OF COMPONENT EACH SYSTEM NEEDS
		ecs.add_component_to_system<Empaerior::Sprite_Component, Empaerior::Sprite_System>();
		ecs.add_component_to_system<Empaerior::Event_Listener_Component, Empaerior::Event_System>();




#pragma region Asset path loading

		//insert the path
		int id = 0;
		id_to_cell_type.insert({ id,"assets/tex_cell.png" });
		++id;
		id_to_cell_type.insert({ id,"assets/tex_flag.png" });
		++id;
		id_to_cell_type.insert({ id,"assets/tex_q.png" });


		//insert cell texturees
		id = -1;
		id_to_field_type.insert({ id,"assets/tex_mine.png" });
		id++;
		id_to_field_type.insert({ id,"assets/tex_empty.png" });
		id++;
		id_to_field_type.insert({ id,"assets/tex_one.png" });
		id++;
		id_to_field_type.insert({ id,"assets/tex_two.png" });
		id++;
		id_to_field_type.insert({ id,"assets/tex_three.png" });
		id++;
		id_to_field_type.insert({ id ,"assets/tex_four.png" });
		id++;
		id_to_field_type.insert({ id , "assets/tex_five.png" });
		id++;
		id_to_field_type.insert({ id,"assets/tex_six.png" });
		id++;
		id_to_field_type.insert({ id,"assets/tex_seven.png" });
		id++;
		id_to_field_type.insert({ id,"assets/tex_eight.png" });




#pragma endregion

#pragma region RNG GENERATION

		int lower_bound = 20;
		int upper_bound = 50;
		field_matrix[board_size][board_size];
		/*
				std::ifstream out("config.json");
				cereal::JSONInputArchive archive(out);

				archive(cereal::make_nvp("lower_bound", lower_bound));
				archive(cereal::make_nvp("upper_bound", upper_bound));

				*/

				//mine distributing
				//thanks Chilli Tomato Noodle

		for (int i = 0; i < board_size; i++)
		{
			for (int j = 0; j < board_size; j++)
			{
				field_matrix[i][j] = 0;
			}
		}

		//total mines
		
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> xDist(0, board_size  - 1);
		std::uniform_int_distribution<int> yDist(0, board_size - 1);
		std::uniform_int_distribution<int> mines_rng(lower_bound, upper_bound);
		int mines = mines_rng(rng);
	
	

		int x = 0; 
		int y = 0;
		while (mines != 0)
		{
			x = xDist(rng);
			y = yDist(rng);
			field_matrix[x][y] = -1;

			--mines; 
	
		}
	
	
		//make the number tiles
		for (int i = 0; i < board_size; i++)
		{
			for (int j = 0; j < board_size; j++)
			{
				int mines_around = 0;
				if (field_matrix[i][j] == -1) { continue; }
				if (j + 1 < board_size && field_matrix[i][j + 1] == -1) mines_around++;
				if (i + 1 < board_size && field_matrix[i + 1][j] == -1) mines_around++;
				if (j - 1 >= 0 && field_matrix[i][j - 1] == -1) mines_around++;
				if (i - 1 >= 0 && field_matrix[i - 1][j] == -1) mines_around++;
				if (i + 1 < board_size && j + 1 < board_size && field_matrix[i + 1][j + 1] == -1)  mines_around++;
				if (i + 1 < board_size && j - 1 >= 0 && field_matrix[i + 1][j - 1] == -1)  mines_around++;
				if (i - 1 >= 0 && j - 1 >= 0 && field_matrix[i - 1][j - 1] == -1) mines_around++;
				if (i - 1 >= 0 && j + 1 < board_size && field_matrix[i - 1][j + 1] == -1)  mines_around++;
				field_matrix[i][j] = mines_around;

			}

		}
		nr_mines = get_bombs();
#pragma endregion


#pragma region Background
		//Put the backgorund in
		Empaerior::Entity background = { ecs.create_entity_ID() };
		ecs.add_component<Empaerior::Sprite_Component>(background.id, {});
		spr_system->emplace_sprite(ecs, background.id, { 0,0,480,400 }, { 0,0,1,1 }, "assets/background.png");
		ecs.add_component<Mine_field>(background.id, { {0} });
		spr_system->emplace_textsprite(ecs, background.id, { 258,5,1000,100 }, "assets/font.ttf", 32, "Mines: " + std::to_string(nr_mines), { 0,0,0,255 });
		//Add faceboi
		Empaerior::Entity face_boi = { ecs.create_entity_ID() };
		Empaerior::Entity flagspr = { ecs.create_entity_ID() };

		ecs.add_component<Empaerior::Sprite_Component>(face_boi.id, {});
		spr_system->emplace_sprite(ecs, face_boi.id, { 220,0,36,36 }, { 0,0,26,26 }, "assets/tex_face.png");
		ecs.add_component<Empaerior::Event_Listener_Component>(face_boi.id, {});
		

		ecs.add_component<Empaerior::Sprite_Component>(flagspr.id, {});
		spr_system->emplace_textsprite(ecs, flagspr.id, { 44,5,220,100 }, "assets/font.ttf", 32, "Flags : 0 ", { 0,0,0,255 });


		ecs.get_component<Mine_field>(background.id).all_spaces = board_size * board_size - nr_mines;
	


#pragma region face_boi_release


		event_system->add_event_to_entity(ecs, face_boi.id, SDL_MOUSEBUTTONUP,
			[&Ecs = ecs,&Spr_system = spr_system, &kamera = camera, face_boi_id = face_boi.id](Empaerior::Event& event)
		{

			//mouse coordinates

			auto f_m = Empaerior::Input::Mouse::get_world_mouse_coords(kamera);
			if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(face_boi_id).all_sprite_index[0]).get_rect(), f_m.x, f_m.y))
			{
				//RESTART GAME
				touched_mine = true;
				Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(face_boi_id).all_sprite_index[0]).set_texture("assets/tex_face.png");
			}
			else
			{
				//Ecs.get_component<Empaerior::Sprite_Component>(face_boi_id).sprites[0].set_texture("assets/tex_face.png");
			}

			Empaerior::event_handled(event);
		}

		);

#pragma endregion



#pragma region face_boi_down

		event_system->add_event_to_entity(ecs, face_boi.id, SDL_MOUSEBUTTONDOWN,
			[&Ecs = ecs,&Spr_system = spr_system, &kamera = camera, face_boi_id = face_boi.id](Empaerior::Event& event)
		{

			//mouse coordinates

			auto f_m = Empaerior::Input::Mouse::get_world_mouse_coords(kamera);
			if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(face_boi_id).all_sprite_index[0]).get_rect(), f_m.x, f_m.y))
			{
				Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(face_boi_id).all_sprite_index[0]).set_texture("assets/face_boi_click.png");

			}

			Empaerior::event_handled(event);
		}

		);
#pragma endregion

#pragma region margins

		spr_system->emplace_sprite(ecs, background.id, { 432,40,4,320 }, { 0,0,1,1 }, "assets/margin.png");
		spr_system->emplace_sprite(ecs, background.id, { 44,40,4,320 }, { 0,0,1,1 }, "assets/margin.png");
		spr_system->emplace_sprite(ecs, background.id, { 44,36,392,4 }, { 0,0,1,1 }, "assets/margin.png");
		spr_system->emplace_sprite(ecs, background.id, { 44,360,392,4 }, { 0,0,1,1 }, "assets/margin.png");


#pragma endregion

#pragma endregion

#pragma region PlayArea

#define tile ecs.get_component<Mine_field>(background.id).field[i][j]
		for (int i = 0; i < board_size; i++)
		{
			for (int j = 0; j < board_size; j++)
			{

				tile = ecs.create_entity_ID();
				//add the random generation here
				ecs.add_component<Empaerior::Sprite_Component>(tile, {});
				ecs.add_component<field_component>(tile, { field_matrix[i][j] });
				ecs.add_component<cell_component>(tile, { 0,false });

				ecs.add_component<Empaerior::Event_Listener_Component>(tile, { {} });

				//adds what at the bottom


				spr_system->emplace_sprite(ecs, tile, { Empaerior::fl_point(24 * j + 48) ,Empaerior::fl_point(20 * i + 40),24,20 }, { 0,0,64,64 }, id_to_field_type[field_matrix[i][j]]);


				//

				//adds what's in the front

				spr_system->emplace_sprite(ecs, tile, { Empaerior::fl_point(24 * j + 48) ,Empaerior::fl_point(20 * i + 40) ,24,20 }, { 0, 0, 64, 64 }, id_to_cell_type[0]);


				//notice I didn't register this component as it is not necessary


				//event handling

				event_system->add_event_to_entity(ecs, tile, SDL_MOUSEBUTTONUP, [&Ecs = ecs, &Spr_system = spr_system, &mine = mine_system, map = background.id, i, j, &kamera = camera, &id_to_cell_type_map = id_to_cell_type, Face_boi = face_boi,FlagSpr = flagspr, &Nr_mines = nr_mines](Empaerior::Event& event) {

#define l_tile Ecs.get_component<Mine_field>(map).field[i][j]
					if (Empaerior::is_event_handled(event)) return; 
					//mouse coordinates
				
					auto f_m = Empaerior::Input::Mouse::get_world_mouse_coords(kamera);

					Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(Face_boi.id).all_sprite_index[0]).set_texture("assets/tex_face.png");
					//reveal
					if (event.event.button.button == SDL_BUTTON_LEFT)
					{
						if (!Ecs.get_component<cell_component>(l_tile).is_revealed&& Ecs.get_component<cell_component>(l_tile).is_clicked == 1)
						{
							if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[0]).get_rect(), f_m.x, f_m.y))
							{

								mine->Reveal(Ecs,Spr_system, map, i, j);
							
								Empaerior::event_handled(event);
								if (Ecs.get_component<Mine_field>(map).mine_encountered == 1)
								{
									//Change face_boi to dead_boi
							
									Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(Face_boi.id).all_sprite_index[0]).set_texture("assets/dead_boi.png");
									
								}
								else if (mine->get_nr_cell(Ecs, map) + Nr_mines == board_size  * board_size)
								{
									Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(Face_boi.id).all_sprite_index[0]).set_texture("assets/happy_boi.png");
								}
							}

						}
					}
					//change cell type
					if (event.event.button.button == SDL_BUTTON_RIGHT)
					{
						if (!Ecs.get_component<cell_component>(l_tile).is_revealed)
						{
							if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[0]).get_rect(), f_m.x, f_m.y))
							{
#define CELL_TYPE Ecs.get_component<cell_component>(l_tile).cell_type

								if (CELL_TYPE == 1) Ecs.get_component<Mine_field>(map).flags--;//remove flag
								CELL_TYPE++;
								if (CELL_TYPE == 3) CELL_TYPE = 0;
								if (CELL_TYPE == 1) Ecs.get_component<Mine_field>(map).flags++;//if lfag
								Empaerior::SpriteFunctions::set_message(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(FlagSpr.id).all_sprite_index[0]), "Flags : " + std::to_string(Ecs.get_component<Mine_field>(map).flags), 32);
								Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[1]).set_texture(id_to_cell_type_map[CELL_TYPE]);
#undef CELL_TYPE
							}
						}


					}



					if (!Ecs.get_component<cell_component>(l_tile).is_revealed&& Ecs.get_component<cell_component>(l_tile).is_clicked)
					{

						Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[1]).set_texture("assets/tex_cell.png");
						Ecs.get_component<cell_component>(l_tile).is_clicked = 0;

					}




#undef l_tile
				});

				//WHEN A CELL A CLICKED
				event_system->add_event_to_entity(ecs, tile, SDL_MOUSEBUTTONDOWN, [&Ecs = ecs,&Spr_system = spr_system, &mine = mine_system, map = background.id, i, j,Face_boi = face_boi ,  &kamera = camera, &id_to_cell_type_map = id_to_cell_type](Empaerior::Event const& event) {

#define l_tile Ecs.get_component<Mine_field>(map).field[i][j]
					//mouse coordinates
					auto f_m = Empaerior::Input::Mouse::get_world_mouse_coords(kamera);
					if (!Ecs.get_component<cell_component>(l_tile).is_revealed&& event.event.button.button == SDL_BUTTON_LEFT)
					{
						if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[0]).get_rect(), f_m.x, f_m.y) && Ecs.get_component<cell_component>(l_tile).cell_type == 0)
						{
							if(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index.size() > 1)	Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[1]).set_texture("assets/tex_empty.png");
							Ecs.get_component<cell_component>(l_tile).is_clicked = 1;
							Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(Face_boi.id).all_sprite_index[0]).set_texture("assets/shock_boi.png");
						}

					}



#undef l_tile
				});




			}

		}

#pragma endregion

		
	}


	~APP_State1()
	{
		ecs.Destroy();
	}

	void Update(const Empaerior::u_int dt)override
	{
		//DEBUG CODE, LETS YOU MOVE AROUND THE MAP


		//UPDATE
		spr_system->update(ecs, dt);
	}

	virtual void Render() override//renders the state
	{
		
		SDL_RenderSetLogicalSize(Empaerior::Application::window.renderer, camera.rect.w, camera.rect.h);
		//RENDER
		spr_system->render(ecs, camera);
		

	}
	virtual void handleevents(Empaerior::Event& event) override
	{
		//HANDLE EVENTS
		event_system->handle_events(ecs, event);
	}

	Empaerior::u_inter get_bombs()
	{
		Empaerior::u_inter z = 0;
		for (int i = 0; i < board_size; i++)
		{
			for (int j = 0; j < board_size; j++)
			{
				if (field_matrix[i][j] == -1) z++;
			}
		}
		return z;
	}
	
	std::shared_ptr<Empaerior::Sprite_System> spr_system;
	std::shared_ptr<Empaerior::Event_System> event_system;
	std::shared_ptr<Mine_sweep_system> mine_system;

	Empaerior::u_inter nr_mines = 0;

	Empaerior::u_inter field_matrix[board_size][board_size];
private:


	//id -> path to the png of the field (mine,1,2,3,0)
	std::unordered_map<Empaerior::u_inter, std::string> id_to_field_type;
	//id -> path to the png of the cell type (flag,normal,?)
	std::unordered_map<Empaerior::u_inter, std::string> id_to_cell_type;

};



//a user defined application
class Test_Aplication : public Empaerior::Application
{
public:
	Test_Aplication()
	{
		//CREATE A WINDOW
		window.Init("test", 960, 800);
		//CREATE A NEW STATE
		main_state = push_state(new APP_State1());



		//make the state active


		activate_state(main_state);







		//SET THE DIMENSIONS OF THE CAMERA
		SDL_RenderSetLogicalSize(Application::window.renderer, states[active_states[0]]->get_camera().rect.w, states[active_states[0]]->get_camera().rect.h);
		//ADD AN OVERLAY STATE

	//  pause_state(main_state);








	}

	~Test_Aplication()
	{

	}

	//the main loop

	void run() override
	{
		//GAME LOOP
		Empaerior::u_int framestart = 0;
		Empaerior::u_int frametime = 0;
		Empaerior::u_int currentime = 0;
		Empaerior::u_int acumulator = 0;

		while (Empaerior::Application::is_running)
		{


			//poll what event is registered
			while (SDL_PollEvent(&Empaerior::Application::event.event)) {
				//make it not handled yet
				Empaerior::Application::event.is_handled = false;
				//handle it
				handlevents(Empaerior::Application::event);

			}
			if (!Empaerior::Application::is_paused)
			{


				framestart = SDL_GetTicks();
				frametime = framestart - currentime;

				if (frametime > 25) frametime = 25; //if too many frames are skipped

				currentime = framestart;
				acumulator += frametime;



				while (acumulator >= Empaerior::Application::dt)
				{


					//update

					Update(Empaerior::Application::dt);

					acumulator -= Empaerior::Application::dt;



				}


				//Text_Sprite * norge = new Text_Sprite({ 0,0,200,200 }, "assets/font.ttf", 32 ,s, color);


				Empaerior::Application::window.clear();
				render();

				Empaerior::Application::window.render();


				//CReating and deleting a state every update to test for bugs


				//refresh the application
				refresh();


				

			}

			Empaerior::Asset_Loading::clean_textures();

		}
	}


	void handlevents(Empaerior::Event& event) override
	{

		Empaerior::Application::window.window_listener.handleEvents(event);

		for (Empaerior::u_inter i = active_states.size() - 1; active_states.size() > i; --i)
		{
			states[active_states[i]]->handleevents(event);
		}

	}
	void Update(const Empaerior::u_int dt)override
	{

		for (Empaerior::u_inter i = 0; i < active_states.size(); i++)
		{
			states[active_states[i]]->Update(dt);
		}
		On_mine_touched();
	}


	void render() override
	{

		for (Empaerior::u_inter i = 0; i < active_states.size(); i++)
		{
			states[active_states[i]]->Render();
		}
	}


	void On_mine_touched()
	{
		if (touched_mine)
		{
			ENGINE_INFO("RESTARTING THE GAME");



			delete_state(main_state);

			main_state = push_state(new APP_State1());
			activate_state(main_state);
			touched_mine = false;
			ENGINE_INFO("RESTARTED THE GAME");
		}

	}
	Empaerior::u_inter main_state;
};

//CREATE A NEW APPLICATION
Empaerior::Application* Empaerior::Create_Application()
{
	return new Test_Aplication();
}