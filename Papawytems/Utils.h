#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

struct ObjectPosition
{
	float px;
	float py;
	float pz;

	float rx;
	float ry;
	float rz;
};

bool inRange(int value, int min, int max);

#endif // UTILS_H_INCLUDED