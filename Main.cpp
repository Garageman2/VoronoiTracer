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
	
	std::cout << "How many seeds?" << std::endl;
	std::cin >> SeedCount;
	SeedCount = Clamp(SeedCount, 2, 100);
	std::cout << "How big should the Seeds be drawn? Enter 0 to hide them" << std::endl;
	std::cin >> Radius;
	Radius = Clamp(Radius, 0, ImageHeight);
	ShadeDist = ImageWidth;
	std::vector<Seed> Seeds;
	Seeds.reserve(SeedCount);


	for (int i = 0; i < SeedCount; i++)
	{
		int X;
		int Y;
		std::cout << "Enter an X Location for Seed " << i << std::endl;
		std::cin >> X;
		std::cout << "Enter a Y Location for Seed " << i << std::endl;
		std::cin >> Y;
		Seeds.push_back(Seed(Vec3(Clamp(X,0,ImageWidth), Clamp(Y,0,ImageHeight), 1.0)));
	}

	
	//render
	Outfile << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";
	
	for (int j = ImageHeight; j>=0; j--)
	{
		//std::cerr << "\rScanlines Remaining: " << j << std::endl;
		for(int i = 0; i< ImageWidth; i++)
		{
			Vec3 PixLoc = Vec3(i, j, 0);
			Seed NearestSeed = Seeds[0];
			Color PixCol = NearestSeed.Color;
			double Dist = Distance(PixLoc, Seeds[0].Location);
			if(Seeds.size()>1)
			{
				for (int i = 1; i < Seeds.size()-1; i++)
				{
					Seed value = Seeds[i];
					double TDist = Distance(PixLoc, value.Location);
					if(TDist < Radius && Radius !=0)
					{
						std::cout << "Match" << std::endl;
						PixCol = Vec3(0, 0, 0);
						break;
					}
					if (TDist < Dist)
					{
						Dist = TDist;
						NearestSeed = value;
						PixCol = value.Color;
						//std::cerr << "Dist" << TDist << std::endl;
						PixCol = PixCol * Clamp(1-(TDist / ShadeDist), .1, 1.0);
						//std::cerr << "Color New" << PixCol << std::endl;
					}
				}
			}
			
			WriteColor(Outfile, PixCol);
		}
	}
	Outfile.close();
}


