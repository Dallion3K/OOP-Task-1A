#include "raylib.h"
#include "Game.h"
using namespace std;
int main()
{
	InitWindow(900, 600, "OOP Assignment 1");
	SetTargetFPS(144);
	SetExitKey('N');

	//I'm taking names
	string name;
	cout << "Please enter your name: ";
	cin >> name;

	//And giving them to games.

	Game game(name);
	//game.set_up();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		if (game.is_running())
		{
			if (IsKeyPressed(KEY_RIGHT))	game.process_input(KEY_RIGHT);
			if (IsKeyPressed(KEY_LEFT))		game.process_input(KEY_LEFT); 
			if (IsKeyPressed(KEY_UP))		game.process_input(KEY_UP);
			if (IsKeyPressed(KEY_DOWN))		game.process_input(KEY_DOWN);
			if (IsKeyPressed(CHEAT))		game.cheat();
			if (IsKeyPressed(UNDO)) 
			{ 
				if (!game.get_last_input_undone())
				{ 
					game.undo_input();
				} 
				else
				{
					cout << "No more undo's this turn!\n";
				}
			};
		}
		else
		{
			DrawText(game.get_end_reason().c_str(), 610, 10, 20, LIGHTGRAY);
			DrawText("Play again, y or n?", 610, 90, 20, LIGHTGRAY);
			
			if (IsKeyPressed('Y'))
			{
				game.set_up();
			}

		}

		const int cellSize = (int)((float)GetScreenHeight() / (float)(SIZE));

		const auto grid = game.prepare_grid();

		for (int x = 0; x < SIZE; x++)
		{
			for (int y = 0; y < SIZE; y++)
			{
				int xPosition = x * cellSize;
				int yPosition = y * cellSize;

				switch (grid[y][x])
				{
					case HOLE:       DrawRectangle(xPosition, yPosition, cellSize, cellSize, BLACK);     break;
					case MOUSE:      DrawRectangle(xPosition, yPosition, cellSize, cellSize, GREEN);     break;
					case FREECELL:   DrawRectangle(xPosition, yPosition, cellSize, cellSize, DARKGREEN); break;
					case NUT:		 DrawRectangle(xPosition, yPosition, cellSize, cellSize, BROWN);	 break;
					case SNAKETAIL:	 DrawRectangle(xPosition, yPosition, cellSize, cellSize, PURPLE);	 break;
					case SNAKEHEAD:  DrawRectangle(xPosition, yPosition, cellSize, cellSize, RED);       break;
					default:         assert(false); // if this assert triggers there's an unrecognised tile on the grid!
				}

				// draw lines around each tile, remove this if you don't like it!
				DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, DARKGRAY);
			}
		}

		//Draw texts (score, name, etc...)
		string title_1 = "Name: " + name;
		string title_2 = "Score: " + to_string(game.get_player().get_score());
		DrawText(title_1.c_str() , 610, 35, 20, LIGHTGRAY);
		DrawText(title_2.c_str(), 610, 60, 20, LIGHTGRAY);
		
		EndDrawing();


	}

	CloseWindow();
	return 0;
}