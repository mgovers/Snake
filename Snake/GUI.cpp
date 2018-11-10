#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;

namespace Snake {

  // Update the screen on a frame clock trigger
  void GUI::FrameUpdate(Object^ sender, EventArgs^ e)
  {
    if (!this->game->step(currentDirection))
    {
      // Invalid move, game over!
      this->msgBox->Enabled = true;
      this->msgBox->Visible = true;
      this->msgBox->Text = gameOverText;
      // Stop the game timer
      this->gameTimer->Enabled = false;
      this->gameTimer->Stop();
      return;
    }

    // If body parts have been added in this step, add graphic objects for them
    unsigned int nrNewParts = this->game->getBody().size() - this->snakeGraphics->Count;
    for (unsigned int i = 0; i < nrNewParts; i++)
    {
      PictureBox^ newObj = gcnew PictureBox();
      newObj->Image = gcnew Bitmap(Image::FromFile(this->snakeResource), gridSize.X, gridSize.Y);
      this->Controls->Add(newObj);
      this->snakeGraphics->Add(newObj);
    }

    // Update head position
    this->snakeGraphics[0]->Location = Point(
      this->game->getBody()[0].x * gridSize.X,
      this->game->getBody()[0].y * gridSize.Y);

    this->snakeGraphics[0]->Update();
    this->snakeGraphics[0]->Refresh();

    // Check for new food spawn
    if (this->game->getTargets().size() == 0)
    {
      GridPos randPos;
      do {
        randPos = { 
          (int)round(rand() % gridDims.X),
          (int)round(rand() % gridDims.Y) 
        };
      } 
      while (!this->game->addNewTarget(randPos));

      foodGraphics->Location = Point(
        this->game->getTargets()[0].x * gridSize.X, 
        this->game->getTargets()[0].y * gridSize.Y);
      foodGraphics->Image = gcnew Bitmap(Image::FromFile(this->foodResource), gridSize.X, gridSize.Y);
    }

  }

  // Handle keyboard input
  void GUI::KeyHandler(Object^ sender, KeyEventArgs^ e)
  {
    switch (e->KeyCode)
    {
    case (Keys::D): // Right
      this->currentDirection = 0;
      break;
    case (Keys::W): // Up
      this->currentDirection = 1;
      break;
    case (Keys::A): // Left
      this->currentDirection = 2;
      break;
    case (Keys::S): // Right
      this->currentDirection = 3;
      break;
    }

  }

  void GUI::OnClickReset(Object^ sender, MouseEventArgs^ e)
  {
    // Reset game
    for each(PictureBox^ obj in snakeGraphics)
      delete obj;
    this->snakeGraphics = gcnew List<PictureBox^>();
    
    this->game = new Game(gridDims.X,gridDims.Y);
    this->gameTimer->Start();
    this->currentDirection = 0;
    // Suppress UI
    this->msgBox->Enabled = false;
    this->msgBox->Visible = false;
  }

    // Start the application
    void main(cli::array<String^>^ args)
  {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Snake::GUI gui;
    Application::Run(%gui);
  }

}