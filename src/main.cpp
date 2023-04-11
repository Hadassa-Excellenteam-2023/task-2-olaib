#include "Controller.h"

int main()
{
	try
	{
		auto controller = Controller();
		controller.run();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}