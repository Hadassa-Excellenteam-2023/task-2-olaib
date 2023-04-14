#include "Controller.h"

const auto UNKNOWN = "Unknown exception";

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
	catch (...)
	{
		std::cout << UNKNOWN << std::endl;
	}

	return EXIT_SUCCESS;
}