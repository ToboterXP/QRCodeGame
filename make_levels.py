
GRASS = 0
STONE = 1
TREE = 2
WALL = 3
WOOD = 4
RIVER = 5
OOB = 6
WOOD_FLOOR = 7

TALKER = 0
KEY = 1
DOOR = 2
PUZZLE = 3
WIN_ITEM = 4


def start_level(name):
    return f"BYTE {name}[] = "+"{"

def l_object(type, x, y, init_value=0):
    assert type < 8 and init_value < 16
    b1 = hex(0b10000000 | (type<<4) | init_value)
    b2 = hex(x << 4 | y)
    return f"{b1}, {b2}, "

def tiles(type, x1, y1, x2, y2):
    assert type < 16
    b1 = hex(type << 4)
    b2 = hex(x1 << 4 | y1)
    b3 = hex(x2 << 4 | y2)
    return f"{b1}, {b2}, {b3}, "

def end_level():
    return "0xff};\n"





def make_test1():
    level = start_level("test_level1")
    level += tiles(1, 0,0, 15,15)
    level += tiles(0, 1,1, 15,14)
    level += l_object(0, 5,5)
    return level + end_level()

def make_test2():
    level = start_level("test_level2")
    level += tiles(1, 0,0, 15,15)
    level += tiles(0, 0,1, 14,14)
    return level + end_level()

def make_room00():
    level = start_level("room00")
    level += tiles(TREE, 0,0, 15,15)
    level += tiles(GRASS, 1,1, 15,15)
    level += tiles(RIVER, 11,11, 15,15)
    level += tiles(WALL, 12,12, 15,15)
    level += tiles(STONE, 13,13, 15,15)
    level += tiles(WALL, 3,3, 8,8)
    level += tiles(STONE, 4,4, 7,7)
    level += tiles(STONE, 8,5, 8,5)

    level += l_object(PUZZLE, 4,4, 0)
    level += l_object(PUZZLE, 4,7, 1)
    level += l_object(PUZZLE, 7,4, 2)
    level += l_object(PUZZLE, 7,7, 3)
    level += l_object(DOOR, 4,9, 4)
    return level + end_level()

def make_room01():
    level = start_level("room01")
    level += tiles(TREE, 0,0, 15,0)
    level += tiles(GRASS, 0,1, 15,10)
    level += tiles(RIVER, 0,11, 15,11)
    level += tiles(WALL, 0,12, 15,12)
    level += tiles(STONE, 0,13, 15,15)
    return level + end_level()

def make_room02():
    level = start_level("room02")
    level += tiles(TREE, 0,0, 15,15)
    level += tiles(GRASS, 0,1, 14,15)
    level += tiles(WALL, 0,12, 3,15)
    level += tiles(STONE, 0,13, 2,15)
    level += tiles(RIVER, 0,11, 15,11)
    level += tiles(STONE, 7,11, 7,11)
    return level + end_level()

def make_room10():
    level = start_level("room10")
    level += tiles(TREE, 0,0, 0,15)
    level += tiles(GRASS, 1,0, 11,15)
    level += tiles(WALL, 12,0, 12,15)
    level += tiles(STONE, 13,0, 15,15)
    level += tiles(RIVER, 0,5, 11,5)
    level += tiles(RIVER, 11,0, 11,5)
    level += tiles(STONE, 5,10, 5,15)

    #level += l_object(TALKER, 8,6, 0)
    level += l_object(KEY, 6,4, 1)
    return level + end_level()

def make_room11():
    level = start_level("room11")
    level += tiles(STONE, 0,0, 15,15)
    level += tiles(WALL, 7,7, 7,12)

    level += l_object(DOOR, 6,10, 6)
    return level + end_level()

def make_room12():
    level = start_level("room12")
    level += tiles(TREE, 15,0, 15,15)
    level += tiles(GRASS, 4,0, 14,15)
    level += tiles(WALL, 3,0, 3,15)
    level += tiles(STONE, 0,0, 2,15)
    return level + end_level()

def make_room20():
    level = start_level("room20")
    level += tiles(TREE, 0,0, 15,15)
    level += tiles(GRASS, 1,0, 15,14)
    level += tiles(WALL, 12,0, 15,3)
    level += tiles(STONE, 13,0, 15,2)
    level += tiles(STONE, 5,0, 5,8)
    return level + end_level()

def make_room21():
    level = start_level("room21")
    level += tiles(TREE, 0,15, 15,15)
    level += tiles(GRASS, 0,4, 15,14)
    level += tiles(WALL, 0,3, 15,3)
    level += tiles(STONE, 0,0, 15,2)
    return level + end_level()

def make_room22():
    level = start_level("room22")
    level += tiles(TREE, 0,0, 15,15)
    level += tiles(GRASS, 0,0, 14,14)
    level += tiles(WALL, 0,0, 3,3)
    level += tiles(STONE, 0,0, 2,2)
    level += tiles(WOOD, 8,8, 11,12)
    level += tiles(WOOD_FLOOR, 10,12, 10,12)

    level += l_object(DOOR, 10,12, 2)
    level += l_object(KEY, 1,1, 5)
    return level + end_level()

def make_rooms0():
    level = start_level("rooms0")
    level += tiles(OOB, 0,0, 15,15)
    level += tiles(WOOD, 5,5, 12,13)
    level += tiles(STONE, 6,6, 11,12)
    level += tiles(STONE, 10,13, 10,13)

    level += l_object(TALKER, 8,6, 0)
    level += l_object(DOOR, 10,13, 2)
    return level + end_level()

def make_rooms1():
    level = start_level("rooms1")
    level += tiles(OOB, 0,0, 15,15)
    level += tiles(WALL, 3,8, 15,10)
    level += tiles(WALL, 13,8, 15,15)
    level += tiles(STONE, 4,9, 14,9)
    level += tiles(STONE, 14,9, 14,14)
    level += l_object(DOOR, 14,14, 0)
    return level + end_level()

def make_rooms2():
    level = start_level("rooms2")
    level += tiles(OOB, 0,0, 15,15)
    level += tiles(WALL, 4,4, 12,12)
    level += tiles(STONE, 5,5, 11,11)

    #level += l_object(WIN_ITEM, 7,5)
    level += l_object(TALKER, 7,5, 1)
    return level + end_level()


if __name__ == '__main__':
    ret = "//generated by make_levels.py\n"
    ret += make_room00()
    ret += make_room01()
    ret += make_room02()
    ret += make_room10()
    ret += make_room11()
    ret += make_room12()
    ret += make_room20()
    ret += make_room21()
    ret += make_room22()
    ret += make_rooms0()
    ret += make_rooms1()
    ret += make_rooms2()
    with open("level_data.h", "w") as f:
        f.write(ret)
