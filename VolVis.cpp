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


std::vector<float> VolVis::calculateAlphaCompositing()
{
	std::vector<float> density;
	for (int x = 0; x < act_width; x++)
	{
		for (int y = 0; y < act_height; y++)
		{

			// composed value
			float alpha = 0.0;
			for (int z = 0; alpha < 1.0 && z < act_depth; z++)
			{
				// TODO von vorne nach hinten die daten durchgehen und akkumulieren

				// hier muss noch ein passender wert gefunden werden, mit dem die tansparenz angepasst werden kann 
				// (der value muss noch mit einem wert multipliziert werden, mit ausprobieren)
				// momentan beginnt die intensität bei 100 % und je weiter man nach hinten geht desto weniger wird cer value miteinbezogen (man koennte auch das gegenteil machen und das 1.0- weggeben)
				alpha += act_volume->voxel(x, y, z).getValue() * ((1.0 - z / act_depth)*0.1);
				if (alpha > 1.0) {
					alpha = 1.0;
				}

			}
			density.push_back(alpha);
		}
	}
	return density;
}


//implemented Deconstructor
VolVis::~VolVis()
{
}
