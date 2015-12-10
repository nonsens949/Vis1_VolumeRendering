#ifndef VOLVIS_H
#define VOLVIS_H

#include "Volume.h"

class VolVis
{
private:
	//Variables
	int act_width; //x
	int act_height; //y
	int act_depth; //z
	Volume *act_volume; //volume

public:
	VolVis(Volume *volume); //Constructor
	~VolVis(); //Deconstructor

	int getWidth(){ return act_width; }
	int getHeight(){ return act_height; }
	int getDepth(){ return act_depth; }
	Volume getVolume(){ return *act_volume; }

	std::vector<float> calculateRayCasting();
	float getIntensityForWorldCoordinates(int x, int y, int z);
	std::vector<float> calculateAlphaCompositing();
	std::vector<float> centralDifferenceX();
	std::vector<float> centralDifferenceY();
	std::vector<float> centralDifferenceZ();
	std::vector<float> calculateGradientLength();
};
#endif
