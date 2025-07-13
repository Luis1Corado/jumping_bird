#include <raylib.h>
#include <stdlib.h>
#include "raymath.h"
#include <stdio.h>

#define screenWidth 400
#define screenHeight 300
#define tubeWidth 40
#define tubeAperture 80
#define SpaceInBetween 100
#define tubeVelocity 1 
#define BIRDSIZE 10
#define GRAVITY 20.0f

typedef struct tube {
    Rectangle upperTube;
    Rectangle lowerTube;
    Vector2 position;
} tube; 

void move_tubes(tube* tubes, int length);
void initializetubes(tube* tubes, int length);

int main(){
    InitWindow(screenWidth, screenHeight, "jumping_bird");
    SetTargetFPS(30);
    float bird_velocity = 0; 
    float delta_time;  
    float bird_vposition = screenHeight/2 - BIRDSIZE;
    int number_of_tubes = (int)(screenWidth/(2*tubeWidth));
    tube tubes[number_of_tubes];

    initializetubes(tubes, number_of_tubes);

    while(!WindowShouldClose()){
        delta_time = GetFrameTime(); 
        bird_velocity += GRAVITY*delta_time;
        if (IsKeyPressed(KEY_SPACE)){
            bird_velocity = 0;
            bird_velocity -= 1000*delta_time;
        }
        bird_vposition += bird_velocity*delta_time; 

        Rectangle bird = {screenWidth/2 - BIRDSIZE, bird_vposition, BIRDSIZE, BIRDSIZE};
        
        move_tubes(tubes, number_of_tubes);
        
        BeginDrawing();
            ClearBackground(SKYBLUE);
            DrawRectangleRec(bird, YELLOW);
            for (int i = 0; i < number_of_tubes; i++){
                DrawRectangleRec(tubes[i].upperTube, GREEN);
                DrawRectangleRec(tubes[i].lowerTube, GREEN);
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

int random_in_range(int min, int max){
    return min + rand() % (max - min + 1);  // Inclusive of max
}

void move_tubes(tube* tubes, int length){
   for (int i = 0; i < length; i++){
       tubes[i].position.x -= tubeVelocity;

       if (tubes[i].position.x < -tubeWidth){

           int height_lower_tube = random_in_range(tubeAperture, screenHeight-30);
           tubes[i].position = (Vector2){screenWidth, height_lower_tube};
           tubes[i].lowerTube = (Rectangle){tubes[i].position.x, tubes[i].position.y ,tubeWidth, screenHeight - tubes[i].position.y}; 
           tubes[i].upperTube = (Rectangle){tubes[i].position.x, 0 ,tubeWidth, tubes[i].position.y-tubeAperture}; 
       }
       tubes[i].upperTube.x = tubes[i].position.x;
       tubes[i].lowerTube.x = tubes[i].position.x;
   }
}
void set_tubes(Vector2 pos){

}

void initializetubes(tube* tubes, int length){
    int initial_position = screenWidth;
    
    //FIRST TUBE WILL ALWAYS APPEAR IN THE SAME POSITION 
    tubes[0].position = (Vector2){initial_position, screenHeight/2 +20};
    tubes[0].lowerTube = (Rectangle){tubes[0].position.x, tubes[0].position.y ,tubeWidth, screenHeight - tubes[0].position.y}; 
    tubes[0].upperTube = (Rectangle){tubes[0].position.x, 0 ,tubeWidth, tubes[0].position.y-tubeAperture}; 

    int height_lower_tube; 
    for (int i = 1; i < length; i++){
        height_lower_tube = random_in_range(60, screenHeight-20);
        tubes[i].position = (Vector2){initial_position - i*SpaceInBetween, height_lower_tube};
        tubes[i].lowerTube = (Rectangle){tubes[i].position.x, tubes[i].position.y ,tubeWidth, screenHeight - tubes[i].position.y}; 
        tubes[i].upperTube = (Rectangle){tubes[i].position.x, 0 ,tubeWidth, tubes[i].position.y-tubeAperture}; 
    }
}


