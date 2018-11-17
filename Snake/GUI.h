#pragma once

#include "GameManager.h"
#include "AI_Easy.h"
#include <cstdlib>
#include <ctime>

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
      srand(time(0));
      // Initialize all GUI components
      InitializeComponent();

      // Setup grid size to fit the window
      this->gridSize = Point(
        windowSize.X / gridDims.X,
        windowSize.Y / gridDims.Y);

      // Setup game and AI 
      SetupGame();

      
      // Setup graphics
      snakeGraphics = gcnew List<PictureBox^>();
      foodGraphics = AddNewGraphicsObject(foodResource, { 0,0 });
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

    //
    // Handlers
    //

    // Update the screen at a frame update
    void FrameUpdate(Object^ sender, EventArgs^ e);

    // Handle all keyboard input
    void KeyHandler(Object^ sender, KeyEventArgs^ e);
    
    // Handle mouse press
    void OnClickReset(Object^ sender, MouseEventArgs^ e);

    //
    // Methods
    //

    void SetupGame();

    Point IndexToPixel(Point pixel);
    Point IndexToPixel(BodyPart pos);
    PictureBox^ AddNewGraphicsObject(String^ resource, BodyPart location);

    //
    // Properties
    //

    System::ComponentModel::IContainer^  components;
    /// <summary>
    /// Required designer variable.
    /// </summary>

    // The timer that performs game update
    System::Windows::Forms::Timer^  gameTimer;
    unsigned int gameTickInitialPeriod = 200; // The period of the game timer, in ms
    float gameTickSpeedupFactor = 1.5f; // The factor to speed up the timer per speedup instance
    Label^ msgBox;

    // The main game object
    GameManager* gameManager;
    unsigned int currentDirection = 0;     // The current direction input

    // All graphics objects present in the GUI
    List<PictureBox^>^ snakeGraphics;
    PictureBox^ foodGraphics;
    
    // AI 
    bool aiEnabled = false;
    AI* ai;
    Label^ aiStatusBox;

    // GUI Sizes
    Point windowSize = Point(640, 640); // Window size in pixels
    Point gridDims = Point(20, 20);     // Grid dimensions
    Point gridSize;                     // Grid size, computed to fit the window

    // Resources
    Color backgroundColor = Color::DimGray;
    Color messageBoxColor = Color::Wheat;
    String^ snakeResource = gcnew String("./Resources/body.png");
    String^ foodResource = gcnew String("./Resources/food.png");
    String^ gameOverText = gcnew String("Game Over!\n\nClick to restart.");
    String^ aiBoxText = gcnew String("AI Enabled");

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
      this->components = (gcnew System::ComponentModel::Container());
      this->gameTimer = (gcnew System::Windows::Forms::Timer(this->components));
      this->BackColor = backgroundColor;
      this->SuspendLayout();
      // 
      // gameTimer
      // 
      this->gameTimer->Tick += gcnew System::EventHandler(this, &GUI::FrameUpdate);
      this->gameTimer->Interval = gameTickInitialPeriod;
      this->gameTimer->Start();
      //
      // aiBox
      //
      this->aiStatusBox = gcnew Label();
      this->aiStatusBox->BackColor = messageBoxColor;
      this->aiStatusBox->Location = Point(windowSize.X / 10, windowSize.Y / 10);
      this->aiStatusBox->Text = aiBoxText;
      this->aiStatusBox->Visible = 0;
      this->Controls->Add(this->aiStatusBox);
      //
      // msgBox
      //
      this->msgBox = (gcnew Label());
      this->msgBox->Location = Point(0,0);
      this->msgBox->BackColor = messageBoxColor;
      this->msgBox->Size = System::Drawing::Size(windowSize.X, windowSize.Y);
      this->msgBox->Enabled = false;
      this->msgBox->Visible = false;
      this->msgBox->TextAlign = ContentAlignment::MiddleCenter;
      this->msgBox->MouseClick += gcnew MouseEventHandler(this, &GUI::OnClickReset);
      this->Controls->Add(this->msgBox);      
      // 
      // GUI
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(windowSize.X, windowSize.Y);
      this->Name = L"Snake AI";
      this->Text = L"Snake AI";
      this->ResumeLayout(false);

      // Key Handling
      this->KeyPreview = true;
      this->KeyDown += gcnew KeyEventHandler(this, &GUI::KeyHandler);

    }
#pragma endregion

  };
}
