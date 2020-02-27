# 2D Dungeon Crawler

## Controls
W
A
S
D
F
R

##TODO:

### 1.Map segments
Save each of the objects in the map to an array 
Save a grid for each of the map segment containing information about wich tiles are walkable + solid and not
This will be used for pathfinding and light map

### 2.Build world
Based on the dungeon map, take the appropirent segment and save it for each cell in the map


### 3.Chunks And World Rendering
Devide worldmap into a bigger grid, cells --> chunks
For each chunk: Save a pointer to each of those objects and put them in an array (For more memory optimization, delete those objects and save data about their current state when not rendering them)
Only draw closest chunks for optimization