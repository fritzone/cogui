#ifndef RECT_H
#define RECT_H

namespace cogui {

struct rect
{
    int x = 0;
    int y = 0;
    int width = -1;
    int height = -1;

    bool inside(int px, int py)
    {
        return x <= px && px <= x + width && y <= py && py <= y + height;
    }

	bool inside_excluding_borders(int px, int py)
	{
		return x <= px && px < x + width && y <= py && py < y + height;
	}
};

}

#endif // RECT_H
