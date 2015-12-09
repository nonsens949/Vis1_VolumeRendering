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

//gradienten berechnung in x-richtung
std::vector<float> VolVis::centralDifferenceX()
{
	std::vector<float> x_value;
	for (int x = 0; x < act_width; x++)
	{
		for (int y = 0; y < act_height; y++)
		{
			for (int z = 0; x < act_depth; z++)
			{
				// das erste und das letzte pixel in x-richtung kann nicht berechnet werden mit x+1 und x-1
				if (x != 0 && x != act_width){
					float value = act_volume->voxel(x + 1, y, z).getValue() - act_volume->voxel(x - 1, y, z).getValue();
					x_value.push_back(value);
				}
				else {
					x_value.push_back(0.0);
				}
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
		for (int y = 0; y < act_height; y++)
		{
			for (int z = 0; x < act_depth; z++)
			{
				// das erste und das letzte pixel in y-richtung kann nicht berechnet werden mit y+1 und y-1
				if (y != 0 && y != act_height){
					float value = act_volume->voxel(x, y + 1, z).getValue() - act_volume->voxel(x, y - 1, z).getValue();
					y_value.push_back(value);
				}
				else {
					y_value.push_back(0.0);
				}

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
				// das erste und das letzte pixel in z-richtung kann nicht berechnet werden mit z+1 und z-1
				if (z != 0 && z != act_depth) {
					float value = act_volume->voxel(x, y, z + 1).getValue() - act_volume->voxel(x, y, z - 1).getValue();
					z_value.push_back(value);
				}
				else
				{
					z_value.push_back(0.0);
				}
			}
		}
	}
	return z_value;
}

// returns a normalized length vector [0.0, 1.0]
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
				counter++;
			}
		}
	}

	// normalisieren
	float max = 0;
	int arraysize = lengths.size();
	for (int j = 0; j < arraysize; j++){
		if (max < lengths[j]){
			max = lengths[j];
		}
	}
	for (int i = 0; i < arraysize; i++) {
		lengths[i] = lengths[i] / max;
	}
	return lengths;
}


//implemented Deconstructor
VolVis::~VolVis()
{
}
