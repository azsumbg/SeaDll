#include "pch.h"
#include "SeaDll.h"

// RANDIt ***********************

dll::RANDIt::RANDIt()
{
	std::random_device rd{};
	std::seed_seq sq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

	twister = new std::mt19937(sq);
}
dll::RANDIt::~RANDIt()
{
	if (twister)delete twister;
}

int dll::RANDIt::operator()(int min, int max)
{
	std::uniform_int_distribution distrib(min, max);

	return distrib(*twister);
}

/////////////////////////////////

// PPROTON ****************************************

dll::PROTON::PROTON(float _sx, float _sy, float _width, float _height)
{
	start.x = _sx;
	start.y = _sy;

	width = _width;
	height = _height;

	end.x = start.x + width;
	end.y = start.y + height;

	x_radius = width / 2;
	y_radius = height / 2;

	center.x = start.x + x_radius;
	center.y = start.y + y_radius;
}
dll::PROTON::PROTON(FPOINT _start_pos, float _width, float _height)
{
	start = _start_pos;
	
	width = _width;
	height = _height;

	end.x = start.x + width;
	end.y = start.y + height;

	x_radius = width / 2;
	y_radius = height / 2;

	center.x = start.x + x_radius;
	center.y = start.y + y_radius;
}
float dll::PROTON::GetWidth()const
{
	return width;
}
float dll::PROTON::GetHeight()const
{
	return height;
}
float dll::PROTON::XRadius()const
{
	return x_radius;
}
float dll::PROTON::YRadius()const
{
	return y_radius;
}
void dll::PROTON::SetEdges()
{
	end.x = start.x + width;
	end.y = start.y + height;

	center.x = start.x + x_radius;
	center.y = start.y + y_radius;
}
void dll::PROTON::NewDims(float _new_width, float _new_height)
{
	width = _new_width;
	height = _new_height;

	end.x = start.x + width;
	end.y = start.y + height;

	x_radius = width / 2;
	y_radius = height / 2;

	center.x = start.x + x_radius;
	center.y = start.y + y_radius;
}
void dll::PROTON::NewWidth(float _new_width)
{
	width = _new_width;
	
	end.x = start.x + width;
	
	x_radius = width / 2;
	
	center.x = start.x + x_radius;
}
void dll::PROTON::NewHeight(float _new_height)
{
	height = _new_height;

	end.y = start.y + height;

	y_radius = height / 2;

	center.y = start.y + y_radius;
}

///////////////////////////////////////////////////

// OBJECT CLASS ***********************************

dll::OBJECT::OBJECT(types _what, float _to_x, float _to_y) :PROTON(_to_x, _to_y, 1.0f, 1.0f)
{
	type = _what;

	switch (type)
	{
	case types::field:
		NewDims(1000.0f, 750.0f);
		max_frames = 75;
		frame_delay = 0;
		break;

	case types::evil1:
		NewDims(120.0f, 69.0f);
		max_frames = 49;
		frame_delay = 1;
		break;

	case types::evil2:
		NewDims(130.0f, 85.0f);
		max_frames = 12;
		frame_delay = 6;
		break;

	case types::evil3:
		NewDims(174.0f, 100.0f);
		max_frames = 6;
		frame_delay = 10;
		break;

	case types::evil4:
		NewDims(80.0f, 60.0f);
		max_frames = 20;
		frame_delay = 3;
		break;

	case types::evil5:
		NewDims(65.0f, 70.0f);
		max_frames = 8;
		frame_delay = 9;
		break;

	case types::evil6:
		NewDims(59.0f, 50.0f);
		max_frames = 40;
		frame_delay = 1;
		break;

	case types::evil7:
		NewDims(68.0f, 40.0f);
		max_frames = 12;
		frame_delay = 6;
		break;

	case types::evil8:
		NewDims(75.0f, 76.0f);
		max_frames = 16;
		frame_delay = 6;
		break;

	case types::jelly:
		NewDims(66.0f, 80.0f);
		max_frames = 4;
		frame_delay = 16;
		break;

	case types::hero:
		NewDims(120.0f, 100.0f);
		max_frames = 2;
		frame_delay = 35;
		break;


	}
}
types dll::OBJECT::GetType() const
{
	return type;
}
int dll::OBJECT::GetFrame()
{
	frame_delay--;
	if (frame_delay <= 0)
	{
		switch (type)
		{
		case types::field:
			frame_delay = 0;
			break;

		case types::evil1:
			frame_delay = 1;
			break;

		case types::evil2:
			frame_delay = 6;
			break;

		case types::evil3:
			frame_delay = 10;
			break;

		case types::evil4:
			frame_delay = 3;
			break;

		case types::evil5:
			frame_delay = 9;
			break;

		case types::evil6:
			frame_delay = 1;
			break;

		case types::evil7:
			frame_delay = 6;
			break;

		case types::evil8:
			frame_delay = 6;
			break;

		case types::jelly:
			frame_delay = 16;
			break;

		case types::hero:
			frame_delay = 35;
			break;
		}

		++current_frame;
		if (current_frame >= max_frames)current_frame = 0;
	}

	return current_frame;
}
void dll::OBJECT::SetType(types what)
{
	type = what;
	current_frame = 0;

	switch (type)
	{
	case types::field:
		NewDims(1000.0f, 750.0f);
		max_frames = 75;
		frame_delay = 0;
		break;

	case types::evil1:
		NewDims(120.0f, 69.0f);
		max_frames = 49;
		frame_delay = 1;
		break;

	case types::evil2:
		NewDims(130.0f, 85.0f);
		max_frames = 12;
		frame_delay = 6;
		break;

	case types::evil3:
		NewDims(174.0f, 100.0f);
		max_frames = 6;
		frame_delay = 10;
		break;

	case types::evil4:
		NewDims(80.0f, 60.0f);
		max_frames = 20;
		frame_delay = 3;
		break;

	case types::evil5:
		NewDims(65.0f, 70.0f);
		max_frames = 8;
		frame_delay = 9;
		break;

	case types::evil6:
		NewDims(59.0f, 50.0f);
		max_frames = 40;
		frame_delay = 1;
		break;

	case types::evil7:
		NewDims(68.0f, 40.0f);
		max_frames = 12;
		frame_delay = 6;
		break;

	case types::evil8:
		NewDims(75.0f, 76.0f);
		max_frames = 16;
		frame_delay = 6;
		break;

	case types::jelly:
		NewDims(66.0f, 80.0f);
		max_frames = 4;
		frame_delay = 16;
		break;

	case types::hero:
		NewDims(120.0f, 100.0f);
		max_frames = 2;
		frame_delay = 35;
		break;
	}
}
void dll::OBJECT::ObjRelease()
{
	delete this;
}

///////////////////////////////////////////////////

// CREATURES **************************************

dll::CREATURES::CREATURES(types __what, float __start_x, float __start_y, float __to_x, float __to_y)
	:OBJECT(__what, __start_x, __start_y)
{
	if (type != types::hero)SetPathInfo(__to_x, __to_y);

	switch (type)
	{
	case types::evil1:
		speed = 0.7f;
		sight_scope = 100.0f;
		break;

	case types::evil2:
		speed = 0.6f;
		sight_scope = 110.0f;
		break;

	case types::evil3:
		speed = 0.5f;
		sight_scope = 130.0f;
		break;

	case types::evil4:
		speed = 0.8f;
		sight_scope = 90.0f;
		break;

	case types::evil5:
		speed = 0.9f;
		sight_scope = 90.0f;
		break;

	case types::evil6:
		speed = 1.0f;
		sight_scope = 70.0f;
		break;

	case types::evil7:
		speed = 1.2f;
		sight_scope = 50.0f;
		break;

	case types::evil8:
		speed = 0.9f;
		sight_scope = 80.0f;
		break;

	case types::jelly:
		speed = 0.6f;
		break;

	case types::hero:
		speed = 5.0f;
		break;
	}
}
void dll::CREATURES::SetPathInfo(float _to_where_x, float _to_where_y)
{
	move_sx = start.x;
	move_sy = start.y;
	move_ex = _to_where_x;
	move_ey = _to_where_y;

	hor_dir = false;
	ver_dir = false;

	if (move_sx == move_ex || (move_ex > start.x && move_ex <= end.x))
	{
		ver_dir = true;
		return;
	}
	if (move_sy == move_ey || (move_ey > start.y && move_ey <= end.y))
	{
		hor_dir = true;
		return;
	}

	slope = (move_ey - move_sy) / (move_ex - move_sx);
	intercept = move_sy - move_sx * slope;
}
bool dll::CREATURES::Move(float gear)
{
	float my_speed = speed + gear / 10.0f;

	if (type != types::hero)return false;

	switch (dir)
	{
	case dirs::right: 
		if (end.x + my_speed <= scr_width)
		{
			start.x += my_speed;
			SetEdges();
			return true;
		}
		break;

	case dirs::left:
		if (start.x - my_speed >= 0)
		{
			start.x -= my_speed;
			SetEdges();
			return true;
		}
		break;

	case dirs::down:
		if (end.y + my_speed <= scr_height)
		{
			start.y += my_speed;
			SetEdges();
			return true;
		}
		break;

	case dirs::up:
		if (start.y - my_speed >= 50.0f)
		{
			start.y -= my_speed;
			SetEdges();
			return true;
		}
		break;
	}

	return false;
}
bool dll::CREATURES::Move(float gear, float dest_x, float dest_y)
{
	float my_speed = speed + gear / 10.0f;

	SetPathInfo(dest_x, dest_y);

	if (ver_dir)
	{
		if (end.y + my_speed <= scr_height)
		{
			start.y += my_speed;
			SetEdges();
			if (move_ey <= center.y)return false;
			return true;
		}
		if (start.y - my_speed >= 50.0f)
		{
			start.y -= my_speed;
			SetEdges();
			if (move_ey >= center.y)return false;
			return true;
		}
	}
	else if (hor_dir)
	{
		if (end.x + my_speed <= scr_width)
		{
			start.x= my_speed;
			SetEdges();
			if (move_ex <= center.x)return false;
			return true;
		}
		if (start.x - my_speed >= 0)
		{
			start.x -= my_speed;
			SetEdges();
			if (move_ex >= center.x)return false;
			return true;
		}
	}
	else
	{
		if (move_ex > move_sx)
		{
			if (end.x + my_speed <= scr_width)
			{
				start.x = my_speed;
				start.y = start.x * slope + intercept;
				SetEdges();
				if (move_ex <= center.x)return false;
				return true;
			}
		}
		else if (move_ex < move_sx)
		{
			if (start.x - my_speed >= 0)
			{
				start.x -= my_speed;
				start.y = start.x * slope + intercept;
				SetEdges();
				if (move_ex >= center.x)return false;
				return true;
			}
		}
	}

	return false;
}
void dll::CREATURES::EvilAI(PACK<FPOINT>& pack, float gear)
{
	state = states::stop;
	Sort(pack, center);

	FPOINT target = pack.front();

	if (Distance(center, target) <= sight_scope)
	{
		state = states::move;
		if (center.x < target.x)dir = dirs::right;
		else dir = dirs::left;

		if (!Move(gear, target.x, target.y))state = states::patrol;
	}
	else
	{
		if (center.x <= scr_width / 2)dir = dirs::right;
		else dir = dirs::left;
		--patrol_move_points;
		if (dir == dirs::right)
		{
			if (patrol_move_points <= 0)
			{
				patrol_move_points = 200;
				dir = dirs::left;
				return;
			}
			if (!Move(gear))
			{
				dir = dirs::left;
				return;
			}
		}
	}
}
void dll::CREATURES::Release()
{
	delete this;
}

///////////////////////////////////////////////////

// FUNCTIONS ************************************

float dll::Distance(FPOINT my_point, FPOINT target_point)
{
	float a = (float)(pow(abs(target_point.x - my_point.x), 2));
	float b = (float)(pow(abs(target_point.y - my_point.y), 2));

	return (float)(sqrt(a + b));
}

SEADLL_API dll::OBJECT* dll::CreateObject(types what, float to_x, float to_y)
{
	OBJECT* ret{ nullptr };
	
	ret = new OBJECT(what, to_x, to_y);

	return ret;
}

SEADLL_API dll::CREATURES* dll::CreateCreature(types what, float start_x, float start_y, float to_x, float to_y)
{
	CREATURES* ret{ nullptr };

	ret = new CREATURES(what, start_x, start_y, to_x, to_y);

	return ret;
}

////////////////////////////////////////////////