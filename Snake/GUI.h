#pragma once

#include "Game.h"
#include <iostream>

namespace Snake {

  using namespace System;
  using namespace System::Collections::Generic;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  /// <summary>
  /// Summary for GUI
  /// </summary>
  public ref class GUI : public System::Windows::Forms::Form
  {
  public:
    GUI(void)
    {
      // Initialize all GUI components
      InitializeComponent();

      // Setup grid size to fit the window
      this->gridSize = Point(
        windowSize.X / gridDims.X,
        windowSize.Y / gridDims.Y);

      // Setup game
      game = new Game(this->gridDims.X, this->gridDims.Y);
      
      // Setup graphics
      graphics = gcnew List<PictureBox^>();
    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~GUI()
    {
      if (components)
      {
        delete components;
      }
    }

  private: 

    // Update the screen at a frame update
    void FrameUpdate(Object^ sender, EventArgs^ e);

    // Handle all keyboard input
    void KeyHandler(Object^ sender, KeyEventArgs^ e);
    
    System::ComponentModel::IContainer^  components;
    /// <summary>
    /// Required designer variable.
    /// </summary>

    // The timer that performs game update
    System::Windows::Forms::Timer^  gameTimer;
    unsigned int gameTickPeriod = 200; // The period of the game timer, in ms 

    // The main game object
    Game* game;

    // All graphics objects present in the GUI
    List<PictureBox^>^ graphics;

    // The current direction input
    unsigned int currentDirection = 0;

    // GUI Sizes
    Point windowSize = Point(640, 640); // Window size in pixels
    Point gridDims = Point(20, 20);     // Grid dimensions
    Point gridSize;                     // Grid size, computed to fit the window


#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
      this->components = (gcnew System::ComponentModel::Container());
      this->gameTimer = (gcnew System::Windows::Forms::Timer(this->components));
      this->SuspendLayout();
      // 
      // timer1
      // 
      this->gameTimer->Tick += gcnew System::EventHandler(this, &GUI::FrameUpdate);
      this->gameTimer->Interval = gameTickPeriod;
      this->gameTimer->Start();
      // 
      // GUI
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(480, 480);
      this->Name = L"GUI";
      this->Text = L"GUI";
      this->ResumeLayout(false);

      // Key Handling
      this->KeyPreview = true;
      this->KeyDown += gcnew KeyEventHandler(this, &GUI::KeyHandler);

    }
#pragma endregion

  };
}
