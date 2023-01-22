#include <windows.h>

#define FIELD_SIDE 16
#define FIELD_SIZE FIELD_SIDE*FIELD_SIDE

#define WORLD_WIDTH 3

#define MAX_OBJECT_COUNT 10

HANDLE heap;
HANDLE stdout;
CHAR_INFO* playField;
BYTE* isSolid;


SHORT playerX;
SHORT playerY;
BYTE worldPos = -1;
BYTE nextLevel = 6; //load first level

BYTE objCollide = 0; //does player collide with current obj?

/*void print(char * string, DWORD stringLength) {

    WriteConsole(stdout, string, stringLength, NULL, NULL);
}*/


void draw(char c, WORD attribute, WORD attributeMask, BYTE x, BYTE y) {
    playField[y * FIELD_SIDE + x].Char.AsciiChar = c;
    playField[y * FIELD_SIDE + x].Attributes &= attributeMask;
    playField[y * FIELD_SIDE + x].Attributes |= attribute;
}

void loadLevel(BYTE levelPos);

#include "objects.h"

Object * objects;

#include "level_data.h"

BYTE * WORLD[] = {
    room00, room01, room02,
    room10, room11, room12,
    room20, room21, room22,
    rooms0, rooms1, rooms2
};

#include "level.h"



void _start() {

    //Create execution environment
    stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE stdin = GetStdHandle(STD_INPUT_HANDLE);
    //heap = HeapCreate(0, 20000, 50000);

    SetConsoleCursorPosition(stdout, (COORD){0, 16});


    //Create playfield
    /*playField = HeapAlloc(heap, 0, sizeof(CHAR_INFO) * FIELD_SIZE);
    isSolid = HeapAlloc(heap, 0, sizeof(BYTE) * FIELD_SIZE);*/
    CHAR_INFO _playField[FIELD_SIZE];
    BYTE _isSolid[FIELD_SIZE];
    playField = _playField;
    isSolid = _isSolid;

    for (int i=0;i<FIELD_SIZE;i++) {
        playField[i].Attributes = 0;
    }


    //Create object list
    //objects = HeapAlloc(heap, 0, sizeof(Object) * MAX_OBJECT_COUNT);
    Object _objects[MAX_OBJECT_COUNT];
    objects = _objects;


    //Create player
    playerX = 10;
    playerY = 10;

    //main rendering loop
    SMALL_RECT playfieldRegion = {0, 0, FIELD_SIDE, FIELD_SIDE};
    DWORD outLen;

    while (1) {
        if (nextLevel != 50) {
            worldPos = nextLevel;
            nextLevel = 50;
            loadLevel(worldPos);
        }

        //update objects
        for (int i=0; i<MAX_OBJECT_COUNT; i++) {
            if (objects[i].active) {
                objCollide = (playerX == objects[i].x && playerY == objects[i].y);
                //runObject(&objects[i]);
                OBJECT_FUNCTIONS[objects[i].type](&objects[i]);
                draw(objectChars[objects[i].type], objectColors[objects[i].type], 0xf0, objects[i].x, objects[i].y);
            }
        }

        draw('@', FOREGROUND_RED | FOREGROUND_INTENSITY, 0xf0, playerX, playerY);

        //render playfield
        WriteConsoleOutput(stdout, playField, (COORD){FIELD_SIDE,FIELD_SIDE}, (COORD){0, 0}, &playfieldRegion);

        //input and player movement
        INPUT_RECORD input;

        ReadConsoleInput(stdin, &input, 1, &outLen);

        if (outLen && input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            SHORT newPlayerX = playerX;
            SHORT newPlayerY = playerY;

            char pressedChar = input.Event.KeyEvent.uChar.AsciiChar;

            switch (pressedChar) {
                case 'w':
                    newPlayerY -= 1;
                    break;
                case 's':
                    newPlayerY += 1;
                    break;
                case 'a':
                    newPlayerX -= 1;
                    break;
                case 'd':
                    newPlayerX += 1;
                    break;
            }

            //passage to next world screen
            BYTE reload = 1;
            if (newPlayerY < 0) {
                worldPos -= WORLD_WIDTH;
                newPlayerY = FIELD_SIDE-1;
            }
            else if (newPlayerY >= FIELD_SIDE) {
                worldPos += WORLD_WIDTH;
                newPlayerY = 0;
            }
            else if (newPlayerX < 0) {
                worldPos--;
                newPlayerX = FIELD_SIDE-1;
            }
            else if (newPlayerX >= FIELD_SIDE){
                worldPos++;
                newPlayerX = 0;
            } else {
                reload = 0;
            }

            //load next screen, if no next screen, move player
            if (reload){
                loadLevel(worldPos);
            }

            if (!isSolid[newPlayerY * FIELD_SIDE + newPlayerX]) {
                //remove old player marker
                if (!reload) {
                    draw(' ', 0, 0xf0, playerX, playerY);
                }

                //player new player marker
                playerX = newPlayerX;
                playerY = newPlayerY;
            }

        }

        Sleep(50);
    }

    ExitProcess(0);
}
