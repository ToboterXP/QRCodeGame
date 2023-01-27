

typedef struct _Object {
	BOOL active;
	BYTE type;
	BYTE x;
	BYTE y;
	BYTE data[2];
} Object;


SHORT progress = 1; //stores progress in game as bitflags
//bit 0: reserved 1
//bit 1: house key
//bit 2: house door
//bit 3: reserved 0
//bit 4: graveyard puzzle, door
//bit 5: castle key
//bit 6: castle door
//bit 7: win item


char texts[2][30] = {
	//"Oh no, I can't reach the key!\n",
	"The true secret is 1324!     \n",
	"You Found and Won The Game!  \n"
};


char objectChars[] = {'@', 'f', '|', 'x'};
WORD objectColors[] = {
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	0,//doesn't matter, door handles itself
	FOREGROUND_RED};


//prints the message indicated by its init value when talked to
void talker(Object * obj) {
	//draw('@', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, 0b11110000, obj->x, obj->y);
	if (objCollide && obj->data[1] == 0) {
		WriteConsole(stdout, &texts[obj->data[0]], 30, NULL, NULL);
		if (obj->data[0]) {
			Sleep(5000);
			ExitProcess(0);
		}
		obj->data[1] = 1;
	}
}

//sets a progress flag when collected
void key(Object * obj) {
	//draw('f', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, 0b11110000, obj->x, obj->y);
	if (progress & (1 << obj->data[0])) objectChars[1] = ' ';
	else objectChars[1] = 'f';

	if (objCollide) {
		progress |= (1 << obj->data[0]);
	}

}

BYTE door_targets[12] = {10,0,0, 0,11,0, 0,0,9, 8,0,4};
//checks init bit if opened, and bit before for key. If opened and player collides, brings player to screen init
void door(Object * obj) {
	BYTE open = progress & (1 << obj->data[0]);
	//isSolid[obj->y * FIELD_SIDE + obj->x] = 0;
	if (open) {
		objectChars[2] = 'O';
		objectColors[2] = BACKGROUND_RED | BACKGROUND_GREEN;
		//draw('O', BACKGROUND_RED | BACKGROUND_GREEN, 0, obj->x, obj->y);
	} else {
		objectChars[2] = '|';
		objectColors[2] = BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED;
		//draw('|', BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED, 0, obj->x, obj->y);
	}

	if (objCollide) {
		if (open) {
			nextLevel = door_targets[worldPos];
		} else if (progress & (1 << ((obj->data[0])-1))){
			progress |= 1 << obj->data[0];
		}
	}
}

//puzzle pressure plate, init = order in progress
BYTE puzzle_progress = 0;
void puzzle_plate(Object * obj) {
	SHORT color = FOREGROUND_RED;
	if (progress & 0b10000) { //if puzzle solved, green
		color = FOREGROUND_GREEN |FOREGROUND_INTENSITY;
	}
	else if (obj->data[1] == 1) { //if plate was pressed, yellow
		color = FOREGROUND_RED |FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	} else if (objCollide){ //unpressed plate is pressed
		obj->data[1] = 1;
		if (obj->data[0] == puzzle_progress) { //check if plate is in order
			puzzle_progress++;
			if (obj->data[0] == 3) progress |= 0b10000; //if it's last plate, solve puzzle
		}
	}
	objectColors[3] = color;
	//draw('x', color, 0xf0, obj->x, obj->y);

}


/*void end_game_item(Object * obj) {
	draw('G', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, 0xf0, 7, 5);
	if (playerX == 7 && playerY == 5) {
		WriteConsole(stdout, "You Found and Won The Game!\n", 28, NULL, NULL);
		Sleep(5000);
		ExitProcess(0);
	}
}*/

void (*OBJECT_FUNCTIONS[4]) (Object * obj) = {&talker, &key, &door, &puzzle_plate/*, &end_game_item*/};
