#include "Main.h"
#include <vector>


int main()
{
	//setup
	const int ImageWidth = 256;
	const int ImageHeight = 256;

	std::ofstream Outfile;
	Outfile.open("Image.ppm", std::ios::out);

	//take in points 
	int SeedCount;


	//include guards so that seeds cannot be the same or out of bounds and there must be at least 1
	
	std::cout << "how many seeds?" << std::endl;
	std::cin >> SeedCount;
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
		Seeds.push_back(Seed(Vec3(X, Y, 1.0)));
	}

	
	//render
	Outfile << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";
	
	for (int j = ImageHeight; j>=0; j--)
	{
		std::cerr << "\rScanlines Remaining: " << j << std::endl;
		for(int i = 0; i< ImageWidth; i++)
		{
			Vec3 PixLoc = Vec3(i, j, 0);
			Seed NearestSeed = Seeds[0];
			double Dist = Distance(PixLoc, Seeds[0].Location);
			if(Seeds.size()>1)
			{
				for (auto value : Seeds)
				{
					double TDist = Distance(PixLoc, value.Location);
					if (TDist < Dist)
					{
						Dist = TDist;
						NearestSeed = value;
					}
				}
			}
			WriteColor(Outfile, NearestSeed.Color);
		}
	}
	Outfile.close();
}


