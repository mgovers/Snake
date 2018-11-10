#include "GameObject.h"

namespace Snake {

  GameObject::GameObject(unsigned int width, unsigned int height) 
  {
    graphics = gcnew System::Windows::Forms::PictureBox();
    graphics->Image = gcnew System::Drawing::Bitmap(width, height);
  }

};