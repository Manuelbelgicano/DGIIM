from random import shuffle

class tile_terrain:
    desert = "desert"
    clay = "clay"
    wood = "wood"
    grain = "grain"
    sheep = "sheep"
    stone = "stone"


class tile:
    def __init__(self,terrain,number=0):
        self.terrain = terrain
        self.number = number
    
    def str(self):
        return self.terrain + "-" + str(self.number)

def set_tilemap():
    map = []
    terrain = [tile_terrain.desert,tile_terrain.clay,tile_terrain.clay,
               tile_terrain.clay,tile_terrain.wood,tile_terrain.wood,
               tile_terrain.wood,tile_terrain.wood,tile_terrain.grain,
               tile_terrain.grain,tile_terrain.grain,tile_terrain.grain,
               tile_terrain.sheep,tile_terrain.sheep,tile_terrain.sheep,
               tile_terrain.sheep,tile_terrain.stone,tile_terrain.stone,
               tile_terrain.stone]
    numbers = [2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12]
    shuffle(numbers)
    
    for i in range(19):
        map.append(tile(terrain[i]))
    
    for i in range(18):
        map[i+1].number = numbers[i]
    
    shuffle(map)
    
    return map

def print_map(map):
    len_max = 10
    void_tile = "          "
    mid_void_tile = "     "
    map_str = ""
    for i in range(19):
        if i==0 or i==16:
            map_str += "\n" + void_tile
        elif i==3 or i==12:
            map_str += "\n" + mid_void_tile
        elif i==7:
            map_str += "\n"
        tile_str = map[i].str()
        sp_left = len_max - len(tile_str)
        mid = int(sp_left/2)
        for i in range(mid):
            map_str += " "
        map_str += tile_str
        for i in range(sp_left-mid):
            map_str += " "
    return map_str
    


map = set_tilemap()
print(print_map(map))