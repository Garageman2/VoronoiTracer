#include "Main.h"

#include <fstream>
#include <iostream>

int main()
{
	//setup
	const int ImageWidth = 256;
	const int ImageHeight = 256;

	std::ofstream Outfile;
	Outfile.open("Image.ppm", std::ios::out);
	
	//render
	Outfile << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";
	
	for (int j = ImageHeight; j>=0; j--)
	{
		for(int i = 0; i< ImageWidth; i++)
		{
			auto R = double(i) / (ImageWidth - 1);
			auto G = double(j) / (ImageHeight - 1);
			auto B = .25;

			int IR = static_cast<int>(255.999 * R);
			int IG = static_cast<int>(255.999 * G);
			int IB = static_cast<int>(255.999 * B);

			Outfile << IR << ' ' << IG << ' ' << IB << '\n';
		}
	}
	Outfile.close();
}
