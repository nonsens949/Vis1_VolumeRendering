#include "VolVis.h"

//implemented constructor
VolVis::VolVis(Volume *volume)
{
	act_width = volume->width();
	act_height = volume->height();
	act_depth = volume->depth();
	act_volume = volume;
}


std::vector<float> VolVis::calculateRayCasting()
{
	std::vector<float> density;
	for (int x = 0; x < act_width; x++)
	{
		for (int y = 0; y < act_height; y++)
		{
			Voxel& maxIntesity = Voxel();
			for (int z = 0; z < act_depth; z++)
			{
				if (act_volume->voxel(x, y, z).operator>(maxIntesity))
				{
					maxIntesity = act_volume->voxel(x, y, z);
				}
			}
			density.push_back(maxIntesity.getValue());
		}
	}
	return density;
}

float VolVis::getIntensityForWorldCoordinates(int x, int y, int z)
{
	return act_volume->voxel(x, y, z).getValue();
}

//implemented Deconstructor
VolVis::~VolVis()
{
}
