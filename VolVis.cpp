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
				// momentan beginnt die intensitšt bei 100 % und je weiter man nach hinten geht desto weniger wird cer value miteinbezogen (man koennte auch das gegenteil machen und das 1.0- weggeben)
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

//gradienten berechnung in x-richtung
std::vector<float> VolVis::centralDifferenceX()
{
	std::vector<float> x_value;
	for (int x = 1; x < act_width - 1; x++)
	{
		for (int y = 0; y < act_height; y++)
		{
			for (int z = 0; x < act_depth; z++)
			{
				float value = act_volume->voxel(x + 1, y, z).getValue() - act_volume->voxel(x-1, y, z).getValue();
				x_value.push_back(value);
			}
		}
	}
	return x_value;
}

//gradienten berechnung in y-richtung
std::vector<float> VolVis::centralDifferenceY()
{
	std::vector<float> y_value;
	for (int x = 0; x < act_width; x++)
	{
		for (int y = 1; y < act_height-1; y++)
		{
			for (int z = 0; x < act_depth; z++)
			{
				float value = act_volume->voxel(x, y + 1, z).getValue() - act_volume->voxel(x, y - 1, z).getValue();
				y_value.push_back(value);
			}
		}
	}
	return y_value;
}

//gradienten berechnung in z-richtung
std::vector<float> VolVis::centralDifferenceZ()
{
	std::vector<float> z_value;
	for (int x = 0; x < act_width; x++)
	{
		for (int y = 0; y < act_height; y++)
		{
			for (int z = 1; x < act_depth-1; z++)
			{
				float value = act_volume->voxel(x, y, z + 1).getValue() - act_volume->voxel(x, y, z - 1).getValue();
				z_value.push_back(value);
			}
		}
	}
	return z_value;
}

std::vector<float> VolVis::calculateGradientLength()
{
	std::vector<float> lengths;

	int counter = 0;
	std::vector<float> x_value = centralDifferenceX();
	std::vector<float> y_value = centralDifferenceY();
	std::vector<float> z_value = centralDifferenceZ();

	for (int x = 0; x < act_width; x++)
	{
		for (int y = 0; y < act_height; y++)
		{
			for (int z = 0; x < act_depth; z++)
			{
				float val_x = x_value[counter];
				float val_y = y_value[counter];
				float val_z = z_value[counter];
				float length = sqrt(pow(val_x, 2) + pow(val_y, 2) + pow(val_z, 2));
				lengths.push_back(length);
			}
		}
	}
	return lengths;
}


//implemented Deconstructor
VolVis::~VolVis()
{
}
