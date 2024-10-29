#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

// ffmpeg -f rawvideo -pixel_format rgba -video_size 800x450 -framerate 30 -i output_video.raw -c:v libx264 output_video.mp4

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int targetFPS = 30;

    InitWindow(screenWidth, screenHeight, "Raylib - Frame-by-Frame Video Capture");

    // Set desired duration in seconds
    float durationInSeconds = 60;

    // Calculate the total number of frames based on duration and frame rate
    const int totalFrames = (int)(durationInSeconds * targetFPS);
    const int frameDataSize = screenWidth * screenHeight * 4; // RGBA format

    // Open the output file for writing
    FILE *file = fopen("output_video.raw", "wb");
    if (!file) {
        printf("Failed to open file for writing.\n");
        CloseWindow();
        return -1;
    }

    SetTargetFPS(targetFPS);

    int frameCount = 0;

    while (!WindowShouldClose() && frameCount < totalFrames)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw example content
        DrawText("Capturing Frames Without Storing All in Memory", 10, 10, 20, DARKGRAY);

        EndDrawing();

        // Capture frame data and write it to the file
        Image image = LoadImageFromScreen();
        fwrite(image.data, 1, frameDataSize, file);
        UnloadImage(image); // Free the frame data from memory

        frameCount++;
    }

    // Close the file after all frames have been written
    fclose(file);
    CloseWindow();

    return 0;
}
