#include <Empaerior.h>
#include <main.h>
#include <SDL_vulkan.h>
#include "Tools/Imgui/Emp_Imgui.h"
#include <random>

//#include "tools/emptmxlite/emptmxlite.h"
#include <thread>         


#include <SDL.h>
#include <SDL_render.h>
#include "../include/core/mat.h"

//An example of what a application might look like
#include "rendering/vulkan_rendering/renderer.h"
#include <vulkan/vulkan.h>
#include "input/input.h"
#include <stb_image.h>
#include <rendering/vulkan_rendering/sprite.h>
#include "Minesweeper.h"
//
//a user defined state


inline Empaerior::Font idk{};
inline bool touched_mine = false;
class APP_State1 : public Empaerior::State
{

public:

	APP_State1(VK_Renderer* renderer)
	{



		Empaerior::Window_Functions::change_window_name(Empaerior::Application::window, "Minesweeper");

		//INITIALIZE THE ECS
		ecs.Init();

		//set the camera
		//camera = { 0,0,480,400 };

		//REGISTER SOME COMPONENTS
		ecs.register_component<Empaerior::singleSprite_Component>();
		ecs.register_component<Empaerior::Event_Listener_Component>();

		//CREATE SOME SYSTEMS TO USE THE COMPONENTS
		spr_system = ecs.register_system <Empaerior::singleSpriteSystem>();
		spr_system->Init(renderer);
		event_system = ecs.register_system<Empaerior::Event_System>();
		mine_system = ecs.register_system<Mine_sweep_system>();
		//SPECIFIY WHAT TYPES OF COMPONENT EACH SYSTEM NEEDS
		ecs.add_criteria_for_iteration<Empaerior::singleSpriteSystem, Empaerior::singleSprite_Component>();
		//ecs.add_component_to_system<Empaerior::Sprite_Component, Empaerior::Sprite_System>();
		//ecs.add_component_to_system<Empaerior::Event_Listener_Component, Empaerior::Event_System>();
		ecs.add_criteria_for_iteration<Empaerior::Event_System, Empaerior::Event_Listener_Component>();




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
		std::uniform_int_distribution<int> xDist(0, board_size - 1);
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
		Background background;
		background.back = { ecs.create_entity_ID() };
		ecs.add_component<Empaerior::singleSprite_Component>(background.back.id, {});

		//spr_system->emplace_sprite(ecs, background.id, { 0,0,480,400 }, { 0,0,1,1 }, "assets/background.png");
	   spr_system->createSprite(ecs, background.back.id, { 0,0,480,400 }, { 0,0,1,1 },
			renderer->texture_atlas.create_texture_from_file("assets/background.png"));
		Empaerior::setSpriteDepth(ecs.get_component<Empaerior::singleSprite_Component>(background.back.id).sprites, 0.8);
		ecs.add_component<Mine_field>(background.back.id, { {0} });


		//spr_system->emplace_textsprite(ecs, background.id, { 258,5,1000,100 }, "assets/font.ttf", 32, "Mines: " + std::to_string(nr_mines), { 0,0,0,255 });
		ecs.add_component<Empaerior::singleSprite_Component>(background.minetext.id, {});
		Empaerior::createTextSprite(renderer->geometrybuffer, renderer->texture_atlas,
			ecs.get_component<Empaerior::singleSprite_Component>(background.minetext.id).sprites,
			{ 258,5,1000,100 }, { 32,32 }, idk,std::string("Mines : " + std::to_string(nr_mines)).c_str() , {0,0,0}
			);


		//Add faceboi
		Empaerior::Entity face_boi = { ecs.create_entity_ID() };
		Empaerior::Entity flagspr = { ecs.create_entity_ID() };

		//ecs.add_component<Empaerior::Sprite_Component>(face_boi.id, {});
		ecs.add_component<Empaerior::singleSprite_Component>(face_boi.id, {});
		//spr_system->emplace_sprite(ecs, face_boi.id, { 220,0,36,36 }, { 0,0,26,26 }, "assets/tex_face.png");
		spr_system->createSprite(ecs, face_boi.id, { 220,0,36,36 }, { 0,0,26,26 },
			renderer->texture_atlas.create_texture_from_file("assets/tex_face.png"));
		ecs.add_component<Empaerior::Event_Listener_Component>(face_boi.id, {});


		//ecs.add_component<Empaerior::Sprite_Component>(flagspr.id, {});
		ecs.add_component<Empaerior::singleSprite_Component>(flagspr.id, {});

		//spr_system->emplace_textsprite(ecs, flagspr.id, { 44,5,220,100 }, "assets/font.ttf", 32, "Flags : 0 ", { 0,0,0,255 });
		Empaerior::createTextSprite(renderer->geometrybuffer, renderer->texture_atlas,
			ecs.get_component<Empaerior::singleSprite_Component>(flagspr.id).sprites,
			{ 44,5,220,100 }, { 32,32 }, idk, "Flags : 0", { 0,0,0 }
		);

		ecs.get_component<Mine_field>(background.back.id).all_spaces = board_size * board_size - nr_mines;



#pragma region face_boi_release


		event_system->add_event_to_entity(ecs, face_boi.id, SDL_MOUSEBUTTONUP,
			[&Ecs = ecs, &Spr_system = spr_system, &rendersetts = renderer->GraphicsSettings, &kamera= renderer->ubo, face_boi_id = face_boi.id](Empaerior::Event& event)
		{

			//mouse coordinates

			auto f_m = Empaerior::Input::Mouse::get_world_mouse_coords(rendersetts,kamera);
			//if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(face_boi_id).all_sprite_index[0]).get_rect(), f_m.x, f_m.y))
			if (Empaerior::Utilities::rect_contains_point(Ecs.get_component<Empaerior::singleSprite_Component>(face_boi_id).sprites.rect, f_m[0], f_m[1]))
			{
				//RESTART GAME
				touched_mine = true;
				//Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(face_boi_id).all_sprite_index[0]).set_texture("assets/tex_face.png");
				Empaerior::setSpriteTexture(Ecs.get_component<Empaerior::singleSprite_Component>(face_boi_id).sprites, Ecs.get_component<Empaerior::singleSprite_Component>(face_boi_id).sprites.parent_atlas->create_texture_from_file("assets/tex_face.png"));
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
			[&Ecs = ecs, &Spr_system = spr_system, &rendersetts = renderer->GraphicsSettings, &kamera = renderer->ubo, face_boi_id = face_boi.id](Empaerior::Event& event)
		{

			//mouse coordinates

			auto f_m = Empaerior::Input::Mouse::get_world_mouse_coords(rendersetts,kamera);

			//if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(face_boi_id).all_sprite_index[0]).get_rect(), f_m.x, f_m.y))
			if (Empaerior::Utilities::rect_contains_point(Ecs.get_component<Empaerior::singleSprite_Component>(face_boi_id).sprites.rect, f_m[0], f_m[1]))
			{
				//Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(face_boi_id).all_sprite_index[0]).set_texture("assets/face_boi_click.png");
				Empaerior::setSpriteTexture(Ecs.get_component<Empaerior::singleSprite_Component>(face_boi_id).sprites, Ecs.get_component<Empaerior::singleSprite_Component>(face_boi_id).sprites.parent_atlas->create_texture_from_file("assets/tex_face.png"));

			}

			Empaerior::event_handled(event);
		}

		);
#pragma endregion

#pragma region margins

		
		for (auto i = 0; i < 4; i++)
		{
			background.margins[i].id = ecs.create_entity_ID();
			ecs.add_component<Empaerior::singleSprite_Component>(background.margins[i].id, {});
			spr_system->createSprite(ecs, background.margins[i].id, background.marginRects[i], { 0,0,1,1 },
				renderer->texture_atlas.create_texture_from_file("assets/margin.png"));
		}
		
	
			/*spr_system->emplace_sprite(ecs, background.id, { 432,40,4,320 }, { 0,0,1,1 }, "assets/margin.png");
		spr_system->emplace_sprite(ecs, background.id, { 44,40,4,320 }, { 0,0,1,1 }, "assets/margin.png");
		spr_system->emplace_sprite(ecs, background.id, { 44,36,392,4 }, { 0,0,1,1 }, "assets/margin.png");
		spr_system->emplace_sprite(ecs, background.id, { 44,360,392,4 }, { 0,0,1,1 }, "assets/margin.png");*/


#pragma endregion

#pragma endregion



#pragma region PlayArea
	
#define tile ecs.get_component<Mine_field>(background.back.id).field[i][j]
		for (int i = 0; i < board_size; i++)
		{
			for (int j = 0; j < board_size; j++)
			{
				tile.lower.id = ecs.create_entity_ID();
				tile.upper.id = ecs.create_entity_ID();
			
			
				//add the random generation here
			//	ecs.add_component<Empaerior::Sprite_Component>(tile, {});

				ecs.add_component<Empaerior::singleSprite_Component>(tile.lower.id, {});
				ecs.add_component<field_component>(tile.lower.id, { field_matrix[i][j] });

				ecs.add_component<cell_component>(tile.upper.id, { 0,false });
				ecs.add_component<Empaerior::singleSprite_Component>(tile.upper.id, {});
				
			
				//std::cout << ecs.has_components<Empaerior::singleSprite_Component>(tile.upper.id);
				ecs.add_component<Empaerior::Event_Listener_Component>(tile.upper.id, { {} });

				//adds what at the bottom


				//spr_system->emplace_sprite(ecs, tile, { Empaerior::fl_point(24 * j + 48) ,Empaerior::fl_point(20 * i + 40),24,20 }, { 0,0,64,64 }, id_to_field_type[field_matrix[i][j]]);
				spr_system->createSprite(ecs,tile.lower.id, { Empaerior::fl_point(24 * j + 48) ,Empaerior::fl_point(20 * i + 40),24,20 }, { 0,0,16,16 }, 
					renderer->texture_atlas.create_texture_from_file(id_to_field_type[field_matrix[i][j]]));
				//Empaerior::setSpriteDepth(ecs.get_component<Empaerior::singleSprite_Component>(tile.lower.id).sprites, 0.99);
				//

				//adds what's in the front

				//spr_system->emplace_sprite(ecs, tile, { Empaerior::fl_point(24 * j + 48) ,Empaerior::fl_point(20 * i + 40) ,24,20 }, { 0, 0, 64, 64 }, id_to_cell_type[0]);
				spr_system->createSprite(ecs, tile.upper.id, { Empaerior::fl_point(24 * j + 48) ,Empaerior::fl_point(20 * i + 40),24,20 }, { 0,0,16,16 },
					renderer->texture_atlas.create_texture_from_file(id_to_cell_type[0]));



				//event handling

				event_system->add_event_to_entity(ecs, tile.upper.id, SDL_MOUSEBUTTONUP, [&Ecs = ecs, &Spr_system = spr_system, &mine = mine_system, map = background, i, j,rendr = renderer, &id_to_cell_type_map = id_to_cell_type, Face_boi = face_boi, FlagSpr = flagspr, &Nr_mines = nr_mines](Empaerior::Event& event) {
				
#define l_tile Ecs.get_component<Mine_field>(map.back.id).field[i][j]
					if (Empaerior::is_event_handled(event)) return;
					//mouse coordinates

					auto f_m = Empaerior::Input::Mouse::get_world_mouse_coords(rendr->GraphicsSettings,rendr->ubo);

					//Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(Face_boi.id).all_sprite_index[0]).set_texture("assets/tex_face.png");
					
					//reveal
					if (event.event.button.button == SDL_BUTTON_LEFT)
					{
						Empaerior::setSpriteTexture(Ecs.get_component<Empaerior::singleSprite_Component>(Face_boi.id).sprites,
							rendr->texture_atlas.create_texture_from_file("assets/tex_face.png"));
						if (!Ecs.get_component<cell_component>(l_tile.upper.id).is_revealed && Ecs.get_component<cell_component>(l_tile.upper.id).is_clicked == 1)
						{
							//if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[0]).get_rect(), f_m.x, f_m.y))
							if (Empaerior::Utilities::rect_contains_point(Ecs.get_component<Empaerior::singleSprite_Component>(l_tile.lower.id).sprites.rect, f_m[0], f_m[1]))
							{
								ENGINE_INFO(std::string("Mouse up on cell ") + std::to_string(i) + ' ' + std::to_string(j) + '\n');
								mine->Reveal(Ecs, Spr_system, map.back.id, i, j);

								Empaerior::event_handled(event);
								if (Ecs.get_component<Mine_field>(map.back.id).mine_encountered == 1)
								{
									APP_WARN("Mine encountered\n");
									//Change face_boi to dead_boi

									//Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(Face_boi.id).all_sprite_index[0]).set_texture("assets/dead_boi.png");
									Empaerior::setSpriteTexture(Ecs.get_component<Empaerior::singleSprite_Component>(Face_boi.id).sprites,
										rendr->texture_atlas.create_texture_from_file("assets/dead_boi.png")
									);

								}
								else if (mine->get_nr_cell(Ecs, map.back.id) + Nr_mines == board_size * board_size)
								{
									APP_INFO("GAME WON\n");
									//Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(Face_boi.id).all_sprite_index[0]).set_texture("assets/happy_boi.png");
									Empaerior::setSpriteTexture(Ecs.get_component<Empaerior::singleSprite_Component>(Face_boi.id).sprites,
										rendr->texture_atlas.create_texture_from_file("assets/happy_boi.png")
									);
								}
							}

						}
					}
					//change cell type
					if (event.event.button.button == SDL_BUTTON_RIGHT)
					{
						if (!Ecs.get_component<cell_component>(l_tile.upper.id).is_revealed)
						{
							//if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[0]).get_rect(), f_m.x, f_m.y))
							if (Empaerior::Utilities::rect_contains_point(Ecs.get_component<Empaerior::singleSprite_Component>(l_tile.lower.id).sprites.rect, f_m[0], f_m[1]))
							{
#define CELL_TYPE Ecs.get_component<cell_component>(l_tile.upper.id).cell_type

								if (CELL_TYPE == 1) Ecs.get_component<Mine_field>(map.back.id).flags--;//remove flag
								CELL_TYPE++;
								if (CELL_TYPE == 3) CELL_TYPE = 0;
								if (CELL_TYPE == 1) Ecs.get_component<Mine_field>(map.back.id).flags++;//if lfag
								//Empaerior::SpriteFunctions::set_message(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(FlagSpr.id).all_sprite_index[0]), "Flags : " + std::to_string(Ecs.get_component<Mine_field>(map).flags), 32);
								Empaerior::setTextSpriteMessage(
									Ecs.get_component<Empaerior::singleSprite_Component>(FlagSpr.id).sprites,
									{ 44,5,220,100 },
									{32,32},
									idk,
									std::string("Flags : " + std::to_string(Ecs.get_component<Mine_field>(map.back.id).flags)).c_str(),
									{0,0,0}
								);
								//Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[1]).set_texture(id_to_cell_type_map[CELL_TYPE]);
								Empaerior::setSpriteTexture(Ecs.get_component<Empaerior::singleSprite_Component>(l_tile.upper.id).sprites,
									rendr->texture_atlas.create_texture_from_file(id_to_cell_type_map[CELL_TYPE]));
#undef CELL_TYPE
							}
						}


					}



					if (!Ecs.get_component<cell_component>(l_tile.upper.id).is_revealed && Ecs.get_component<cell_component>(l_tile.upper.id).is_clicked)
					{

						//Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[1]).set_texture("assets/tex_cell.png");
						Empaerior::setSpriteTexture(Ecs.get_component<Empaerior::singleSprite_Component>(l_tile.upper.id).sprites,
							rendr->texture_atlas.create_texture_from_file("assets/tex_cell.png"));
						Ecs.get_component<cell_component>(l_tile.upper.id).is_clicked = 0;

					}




#undef l_tile
				});

				//WHEN A CELL A CLICKED
				event_system->add_event_to_entity(ecs, tile.upper.id, SDL_MOUSEBUTTONDOWN, [&Ecs = ecs, &Spr_system = spr_system, &mine = mine_system, map = background, i, j, Face_boi = face_boi, rendr = renderer, &id_to_cell_type_map = id_to_cell_type](Empaerior::Event const& event) {
			
#define l_tile Ecs.get_component<Mine_field>(map.back.id).field[i][j]
					//mouse coordinates
					auto f_m = Empaerior::Input::Mouse::get_world_mouse_coords(rendr->GraphicsSettings,rendr->ubo);
					if (!Ecs.get_component<cell_component>(l_tile.upper.id).is_revealed && event.event.button.button == SDL_BUTTON_LEFT)
					{
						//if (Empaerior::Utilities::rect_contains_point(Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[0]).get_rect(), f_m.x, f_m.y) && Ecs.get_component<cell_component>(l_tile).cell_type == 0)
						if (Empaerior::Utilities::rect_contains_point(Ecs.get_component<Empaerior::singleSprite_Component>(l_tile.lower.id).sprites.rect, f_m[0], f_m[1]))
						{
							if (Ecs.has_components<Empaerior::singleSprite_Component>(l_tile.upper.id)) {
								//Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(l_tile).all_sprite_index[1]).set_texture("assets/tex_empty.png");
						    	Empaerior::setSpriteTexture(Ecs.get_component<Empaerior::singleSprite_Component>(l_tile.upper.id).sprites,
									rendr->texture_atlas.create_texture_from_file("assets/tex_empty.png"));
							
							}
							Ecs.get_component<cell_component>(l_tile.upper.id).is_clicked = 1;
							//Spr_system->get_sprite(Ecs.get_component<Empaerior::Sprite_Component>(Face_boi.id).all_sprite_index[0]).set_texture("assets/shock_boi.png");
							Empaerior::setSpriteTexture(Ecs.get_component<Empaerior::singleSprite_Component>(Face_boi.id).sprites,
								rendr->texture_atlas.create_texture_from_file("assets/shock_boi.png"));
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
		//spr_system->update(ecs, dt);
	
	}

	virtual void Render() override//renders the state
	{

		//SDL_RenderSetLogicalSize(Empaerior::Application::window.renderer, camera.rect.w, camera.rect.h);
		//RENDER
		//spr_system->render(ecs, camera);


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

	std::shared_ptr<Empaerior::singleSpriteSystem> spr_system;
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
		window.Init("Empaerior  3.0B8 -Vulkan Renderer", 480, 400);


		//CREATE A NEW STATE
		
		
		
	
	
		//make the state active

		//Empaerior::Sprite testtette;

		vk.InitialGraphicsSettings.Depth = VK_FALSE;
		vk.Init(window.window);
		ENGINE_INFO(std::string("INITIAL VERTEX BUFFER SIZE " + std::to_string(vk.geometrybuffer.initialVertexSize)));
		ENGINE_INFO(std::string("INITIAL INDEX BUFFER SIZE " + std::to_string(vk.geometrybuffer.initialIndexSize)));
		ImGui_Emp::Init(window, vk);

		//setup font
		Empaerior::FontLoading::initFontEngine();
		vk.texture_atlas.create_texture_from_fontPath(idk, "assets/fonts/idk.ttf", 32);
	
		main_state = push_state(new APP_State1(&vk));
		activate_state(main_state);
		
		
	
	//	Empaerior::createTextSprite(vk.geometrybuffer, vk.texture_atlas, testtette, { 0,0,1000,1000 }, { 32,32 }, idk, "_THIS IS MESSAGE DUUUDE", { 255,255,255 });
	

	}
	
	~Test_Aplication()
	{

	}

	//the main loop


	void run() override
	{


		//GAME LOOP

	//	destroySprite(greenboi);

		while (Empaerior::Application::is_running)
		{

			Empaerior::Timer timy;


			Empaerior::u_int framestart = 0;
			Empaerior::u_int frametime = 0;
			Empaerior::u_int currentime = 0;
			Empaerior::u_int acumulator = 0;

			//poll what event is registered
			while (Empaerior::Application::PollEvent()) {

				//make it not handled yet
				Empaerior::Application::event.is_handled = false;
				//handle it
				handlevents(Empaerior::Application::event);


				if (Empaerior::Application::event.event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					vk.framebufferNeedsReconstruction = true;

				}

				ImGuiEmpImpl::ProcessEvent(Empaerior::Application::event);

			}
			if (!Empaerior::Application::is_paused)
			{


			
				
				if (vk.framebufferNeedsReconstruction)
				{
					vk.checkFrameBufferResize();
					ImGui_Emp::refreshImgui(window, vk);
					vk.framebufferNeedsReconstruction = false;
				}

				framestart = SDL_GetTicks();
				frametime = framestart - currentime;

				if (frametime > 25) frametime = 25; //if too many frames are skipped

				currentime = framestart;
				acumulator += frametime;



				while (acumulator >= Empaerior::Application::dt)
				{
					Update(Empaerior::Application::dt);
					acumulator -= Empaerior::Application::dt;


				}

				auto position = Empaerior::Input::Mouse::get_world_mouse_coords(vk.GraphicsSettings, vk.ubo);
				//std::cout << position[0]	 << ' ' << position[1] << '\n';
				
				
				vk.ubo.position_mat = glm::translate(glm::mat4(1.0f), glm::vec3(vk.ubo.position.x * -1, vk.ubo.position.y * -1 , 1.0f));
				



			


				




				timy.start();

				if (Empaerior::Input::Keyboard::is_key_pressed(SDL_SCANCODE_P))
				{
					dump_data(vk.geometrybuffer);
				}
				

				ImGui_Emp::NewFrame(window, vk);
				ShowImGuiWindows();
		
			
				vk.newFrame();
				
	
				//dump_data(vk.geometrybuffer);

				ImGui_Emp::Render(window, vk);
				//	vk.framebufferResized = true;

				vk.drawFrame();
				

				//std::cout <<"Frame time: " << timy.getTicks()<< ' '  << "FPS: " << 1000/ ( timy.getTicks<double,std::chrono::nanoseconds>()/ 1000000.0f) << '\n';
				timy.stop();
				vk.present();
	
				
				
				//

			}






		}

		vkDeviceWaitIdle(vk.device);
		ImGui_Emp::Quit(vk);
		vk.cleanup();
	
	}


	void handlevents(Empaerior::Event& event) override
	{
		Empaerior::Application::window.window_listener.handleEvents(event);
			if (active_states.size() == 0) return;
			for (Empaerior::u_inter i = active_states.size() - 1; active_states.size() > i; --i)
			{
				states[active_states[i]]->handleevents(event);
			}
	}
	void Update(const Empaerior::u_int dt)override
	{

		for (auto& index : active_states) states[index]->Update(dt);
		On_mine_touched();

	}


	void render() override
	{
		for (auto& index : active_states) states[index]->Render();

	}

	void ShowImGuiWindows()
	{
		ImGui::Begin("Graphics");
		if (ImGui::CollapsingHeader("Rasterization"))
		{
			ImGui::Checkbox("rasterizerDiscardEnable", &vk.GraphicsSettings.rasterizerDiscardEnable);
			ImGui::Checkbox("DepthClamp", &vk.GraphicsSettings.DepthClamp);
		}
		if (ImGui::CollapsingHeader("Depth Settings"))
		{
			ImGui::Checkbox("Depth", &vk.GraphicsSettings.Depth);
			ImGui::Checkbox("Stenciltest", &vk.GraphicsSettings.StencilTest);
			ImGui::Checkbox("DepthBoundtest", &vk.GraphicsSettings.DepthBoundTest);
			ImGui::InputFloat("MinDepth", &vk.GraphicsSettings.minDepth);
			ImGui::InputFloat("MaxDepth", &vk.GraphicsSettings.maxDepth);
		}
		if (ImGui::CollapsingHeader("Viewport"))
		{
			ImGui::InputFloat("ViewportX", &vk.GraphicsSettings.viewportX, 10, 100, 2);
			ImGui::InputFloat("ViewportY", &vk.GraphicsSettings.viewportY, 10, 100, 2);
			ImGui::InputFloat("ViewportW", &vk.GraphicsSettings.viewportW, 10, 100, 2);
			ImGui::InputFloat("ViewportH", &vk.GraphicsSettings.viewportH ,10, 100, 2);


		}
		
		ImGui::Checkbox("Blending", &vk.GraphicsSettings.Blending);
		

		ImGui::Button("Apply", { 50, 25 });
		if (ImGui::IsItemClicked()) vk.framebufferNeedsReconstruction = true;
	

		ImGui::Button("Reset", { 50,25 });
		if (ImGui::IsItemClicked()) { vk.GraphicsSettings = vk.InitialGraphicsSettings;  vk.framebufferNeedsReconstruction = true; }
		ImGui::End();

		ImGui::Begin("Camera Settings");
		ImGui::InputFloat("Camera X", &vk.ubo.position.x, 10, 100, 2);
		ImGui::InputFloat("Camera Y", &vk.ubo.position.y, 10, 100, 2);
		ImGui::InputFloat("ScaleX", &vk.ubo.scaleX, 0.1f, 100, 2);
		ImGui::InputFloat("ScaleY", &vk.ubo.scaleY, 0.1f, 100, 2);


		ImGui::End();

		ImGui::Begin("Geometry Buffer Data");

		if (ImGui::CollapsingHeader("Vertex Buffer")) {
			std::string bufferIndex("Current Buffer Index : " + std::to_string(vk.geometrybuffer.vertexBuffer.inUseBufferIndex));
			ImGui::Text(bufferIndex.c_str());

			std::string bufferAllocationSize("Buffer Allocation Size : " + std::to_string(vk.geometrybuffer.vertexBuffer.BufferSize[vk.geometrybuffer.vertexBuffer.inUseBufferIndex]));
			ImGui::Text(bufferAllocationSize.c_str());

			std::string bufferSize("Current Buffer Size : " + std::to_string(vk.geometrybuffer.vertexBuffer.used_size[vk.geometrybuffer.vertexBuffer.inUseBufferIndex]));
			ImGui::Text(bufferSize.c_str());

			std::string vertices("Current Vertice count : " + std::to_string(vk.geometrybuffer.vertexBuffer.used_size[vk.geometrybuffer.vertexBuffer.inUseBufferIndex] / sizeof(Vertex)));
			ImGui::Text(vertices.c_str());
		}
		if (ImGui::CollapsingHeader("Index Buffer")) {
			std::string bufferIndex("Current Buffer Index : " + std::to_string(vk.geometrybuffer.indexBuffer.inUseBufferIndex));
			ImGui::Text(bufferIndex.c_str());

			std::string bufferAllocation("Current Buffer Allocation : " + std::to_string(vk.geometrybuffer.indexBuffer.BufferSize[vk.geometrybuffer.indexBuffer.inUseBufferIndex]));
			ImGui::Text(bufferAllocation.c_str());

			std::string bufferSize("Current Buffer Size : " + std::to_string(vk.geometrybuffer.indexBuffer.used_size[vk.geometrybuffer.indexBuffer.inUseBufferIndex]));
			ImGui::Text(bufferSize.c_str());

			std::string vertices("Current Index count : " + std::to_string(vk.geometrybuffer.indexBuffer.used_size[vk.geometrybuffer.indexBuffer.inUseBufferIndex] / sizeof(uint32_t)));
			ImGui::Text(vertices.c_str());


		}
		ImGui::End();
		
		ImGui::ShowMetricsWindow();
	}

	void On_mine_touched()
	{
		if (touched_mine)
		{
			ENGINE_INFO("RESTARTING THE GAME");


			vk.geometrybuffer.reset();
			delete_state(main_state);
		

			main_state = push_state(new APP_State1(&vk));
			activate_state(main_state);
			touched_mine = false;
			
			ENGINE_INFO("RESTARTED THE GAME");
		}

	}

	std::vector<Empaerior::Sprite> sprites;
	Empaerior::u_inter main_state;
	Empaerior::Sprite greenboi;
	Empaerior::Sprite greenerboi;
	Empaerior::Sprite textboiii;

	VK_Renderer vk;
	float forTest = 0;
	float i  = 0, j = 0;
	
	std::string str = "1111111";
};

//CREATE A NEW APPLICATION
Empaerior::Application* Empaerior::Create_Application()
{
	return new Test_Aplication();
}