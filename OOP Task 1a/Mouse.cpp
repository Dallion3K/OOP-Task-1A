#include "Mouse.h"


Mouse::Mouse(): MoveableGridItem(rng.get_random_value(SIZE), rng.get_random_value(SIZE), MOUSE),alive(true),escaped(false),mouse_dx(0),mouse_dy(0)
{

}

bool Mouse::is_alive() const
{
   return alive;
}

bool Mouse::has_escaped() const
{
   return escaped;
}

bool Mouse::has_reached_a_hole(const Underground ug) const
{
	return ug.is_at_hole(x,y);
}

void Mouse::die()
{
   alive = false;
}

void Mouse::escape_into_hole()
{
   escaped = true;
}

void Mouse::scamper(int key)
{
	//set prev co-ordinates
	set_px_set_py(x, y);

	//set next location
   switch (key)
   {
   case KEY_LEFT:
	   mouse_dx = -1;
	   mouse_dy = 0;
	   break;
   case KEY_RIGHT:
	   mouse_dx = +1;
	   mouse_dy = 0;
	   break;
   case KEY_UP:
	   mouse_dx = 0;
	   mouse_dy = -1;
	   break;
   case KEY_DOWN:
	   mouse_dx = 0;
	   mouse_dy = +1;
	   break;
   default:
	   // not a key we care about, so do nothing
	   break;
   }
   // update mouse coordinates if move is possible

	if (((x + mouse_dx) >= 1) && ((x + mouse_dx) <= SIZE) && ((y + mouse_dy) >= 1) && ((y + mouse_dy) <= SIZE))
	{
	   update_position(mouse_dx, mouse_dy);	 

	}
}



//void Mouse::position_in_middle_of_grid()
//{
//   x = SIZE / 2;
//   y = SIZE / 2;
//}

bool Mouse::can_collect_nut(Nut nut)const 
{
    return !nut.has_been_collected();
}

void Mouse::reset()
{
	alive = true;
	escaped = false;
	reset_position();
}