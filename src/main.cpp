//Hello world!
#include "Render.hpp"

int main() {

	R.Start(600, 600);
	R.LoadTexture("./src/Textures/SandCake_Sticker.png");
	R.LoadTexture("./src/Textures/twitterLogo.png");
	R.Update();

	return 0;
}