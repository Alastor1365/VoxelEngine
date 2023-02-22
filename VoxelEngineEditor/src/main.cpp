#include<iostream>
#include<memory>
#include "VoxelEngineCore/Application.hpp"

class MyApp : public VoxelEngine::Application
{
	virtual void on_update() override
	{
		//std::cout << "Update frame: " << frame++ << std::endl;
	}

	unsigned int frame = 0;
};

int main()
{
	auto myApp = std::make_unique<MyApp>();

	int returnCode = myApp->start(1000, 800, "VoxelEngine");

	return returnCode;
}