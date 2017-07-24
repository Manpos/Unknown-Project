//Hello world!
#include "Render.hpp"

int main() {

	R.Start(800, 800);
	R.LoadTexture("./src/Textures/SandCake_Sticker.png");
	R.LoadTexture("./src/Textures/twitterLogo.png");

	T.RotateObject(R.transformMat, (float)glfwGetTime() * 50.f, T.z);
	T.ScaleObject(R.transformMat, T.x, 1.5f);

	R.Draw();

	return 0;
}