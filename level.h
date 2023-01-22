// aaaaaaaa bbbbbbbb cccccccc
// oaaaaaaa bbbbbbbb cccccccc (o = object?)
//tiles: ottt---- xxxxyyyy xxxxyyyy (tttt = type, xxxxyyyy = edge coords)
//objects: otttiiii xxxxyyyy (ttt = type, iiii = init value, xxxxyyy = pos)
//terminator FF


//tiles
WCHAR TILE_CHARS[] = {
	' ',
	' ',
	'%',
	'#',
	'=',
	'~',
	' ',
	' '};
BYTE TILE_COLORS[] = {
	BACKGROUND_GREEN,
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED,
	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE,
	0,
	BACKGROUND_RED | BACKGROUND_GREEN
	};

BYTE TILE_SOLID[] = {0, 0, 1, 1, 1, 1, 1, 0};


void loadLevel(BYTE levelPos) {
	BYTE * levelData = WORLD[levelPos];

	//delete all objects
	for (int i=0; i<MAX_OBJECT_COUNT; i++) {
		objects[i].active = 0;
	}

	puzzle_progress = 0;

	BYTE last_object = 0;

	//load level data
	while (*levelData != 0xff) {
		//first bit determins if data is object or tiles
		if ((*levelData) & 0b10000000) {
			//create objects
			BYTE type = ((*levelData) >> 4) & 0b111;
			BYTE init = (*levelData) & 0b1111;

			levelData += sizeof(BYTE);

			BYTE x = ((*levelData) >> 4) & 0b1111;
			BYTE y = (*levelData) & 0b1111;

			objects[last_object].active = 1;
			objects[last_object].type = type;
			objects[last_object].x = x;
			objects[last_object].y = y;
			objects[last_object].data[1] = 0;
			objects[last_object++].data[0] = init;

		} else {
			//place tile square
			BYTE type = ((*levelData) >> 4) & 0b111;

			levelData += sizeof(BYTE);

			BYTE x1 = ((*levelData) >> 4) & 0b1111;
			BYTE y1 = (*levelData) & 0b1111;

			levelData += sizeof(BYTE);

			BYTE x2 = ((*levelData) >> 4) & 0b1111;
			BYTE y2 = (*levelData) & 0b1111;

			//fill rectangle
			for (BYTE i = y1; i<=y2; i++) {
				for (BYTE j = x1; j <=x2; j++) {
					draw(TILE_CHARS[type], TILE_COLORS[type], 0, j, i);
					isSolid[i*FIELD_SIDE + j] = TILE_SOLID[type];
				}
			}
		}
		levelData += sizeof(BYTE);
	}
}
