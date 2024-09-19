//main.cpp for OpenBaseball
//https://github.com/svet-am/openBaseball
//written by Tony McDowell (svet.am@gmail.com)
#include <time.h>
#include <stdlib.h> 
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "SFML/Graphics.hpp"
#include "obb_version.hpp"
#include "obb_utils.hpp"

using namespace std;
 
int main(int argc, char *argv[])
{
	//get current path of the executable
	string obbPathString = getBasePath(&argv[0]);
	
	//create the splash screen window
	sf::RenderWindow splashWindow(sf::VideoMode(512, 512), "Splash Screen", sf::Style::None);
	sf::Texture splashScreenLogoTexture;
	
	if (!splashScreenLogoTexture.loadFromFile(obbPathString.append("/img/obb_logo.png"), sf::IntRect(0, 0, 512, 512)))
		return -1;

	sf::Sprite splashScreenLogoSprite(splashScreenLogoTexture);	
	splashWindow.draw(splashScreenLogoSprite);
    splashWindow.display();		
	Sleep(5000);	
	splashWindow.close();
	
	
    // create the main window
    sf::Window glWindow(sf::VideoMode(640, 480), OBB_NAME_VER, sf::Style::Default, sf::ContextSettings(24));
    glWindow.setVerticalSyncEnabled(true);

    // activate the window
    glWindow.setActive(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (glWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...

        // end the current frame (internally swaps the front and back buffers)
        glWindow.display();
    }

    // release resources...

    return 0;
}