#include "Main.h"


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
		std::cerr << "\rScanlines Remaining: " << j << std::endl;
		for(int i = 0; i< ImageWidth; i++)
		{
			Color PixelColor((double(i) / (ImageWidth - 1)), (double(j) / (ImageHeight - 1)), .95);
			WriteColor(Outfile, PixelColor);
		}
	}
	Outfile.close();
}
