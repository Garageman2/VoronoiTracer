#include "Main.h"
#include <vector>

int main()
{
	//setup
	const int ImageWidth = 1024;
	const int ImageHeight = 1024;

	std::ofstream Outfile;
	Outfile.open("Image.ppm", std::ios::out);

	//take in points 
	int SeedCount;
	int Radius;
	int ShadeDist;


	//include guards so that seeds cannot be the same or out of bounds and there must be at least 1. Darken based on distance.
	

	ValidInput("How Many Seeds?", SeedCount);
	SeedCount = Clamp(SeedCount, 2, 100);
	
	ValidInput("How big should the Seeds be drawn? Enter 0 to hide them", Radius);
	Radius = Clamp(Radius, 0, ImageHeight);
	
	ShadeDist = ImageWidth * 1.25;
	std::vector<Seed> Seeds;
	Seeds.reserve(SeedCount);

	bool DistType;
	ValidInput("Enter 0 for Euclidian and 1 for Manhattan", DistType);
	double(*DistFormula)(Vec3, Vec3){ (DistType) ? &ManDistance : &EucDistance };

	for (int i = 0; i < SeedCount; i++)
	{
		int X;
		int Y;
		ValidInput(std::string("Enter an X Location for Seed ").append(std::to_string(i).c_str()), X);
		ValidInput(std::string("Enter a Y Location for Seed ").append(std::to_string(i).c_str()), Y);
		Seeds.push_back(Seed(Vec3(Clamp(X,0,ImageWidth), Clamp(Y,0,ImageHeight), 1.0)));
	}

	
	//render
	Outfile << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";
	
	for (int j = ImageHeight; j>=0; j--)
	{
		
		for(int i = 0; i< ImageWidth; i++)
		{
			Vec3 PixLoc = Vec3(i, j, 0);
			Seed NearestSeed = Seeds[0];
			Color PixCol = NearestSeed.Color;
			double Dist = (*DistFormula)(PixLoc, Seeds[0].Location);
			if(Seeds.size()>1)
			{
				for (int i = 1; i < Seeds.size()-1; i++)
				{
					Seed value = Seeds[i];
					double TDist = (*DistFormula)(PixLoc, value.Location);
					if(TDist < Radius && Radius !=0)
					{
						PixCol = Vec3(0, 0, 0);
						break;
					}
					if (TDist < Dist)
					{
						Dist = TDist;
						NearestSeed = value;
						PixCol = value.Color;
						PixCol = PixCol * Clamp(1-(TDist / ShadeDist), .1, 1.0);
					}
				}
			}
			
			WriteColor(Outfile, PixCol);
		}
	}
	Outfile.close();
}


