#include "raylib.h"
#include "WindowsDefines.h" // fixes nameing issues with windows.h and raylib, also must be included after raylib
#include "Logger/Logger.h"

#include "Input System/Input.h"

void LogCustom(int msgType, const char* text, va_list args)
{
    int length = _vscprintf(text, args) + 1; // _vscprintf doesn't count the terminating '\0'
    char* buffer = new char[length];

    if (buffer != NULL)
    {
        vsprintf_s(buffer, length, text, args);

        switch (msgType)
        {
        case LOG_INFO: ARC_ENGINE_INFO(buffer); break;
        case LOG_ERROR: ARC_ENGINE_ERROR(buffer); break;
        case LOG_WARNING: ARC_ENGINE_WARNING(buffer); break;
        case LOG_DEBUG: ARC_ENGINE_TRACE(buffer); break;
        default: break;
        }
    }

    delete(buffer);
}

using namespace Architect;

int main(void)
{
    Logger::Init();

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetTraceLogCallback(LogCustom);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        if (Input::GetKeyUp(KeyCode::Alfa0))
        {
            ARC_INFO("0 Key Pressed");
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}