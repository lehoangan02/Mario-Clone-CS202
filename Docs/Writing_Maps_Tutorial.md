# How to input data to create maps
## List of Enums used
Many of the data used to classified elements in maps are defined by enums.

Here are the list of enums used:
```cpp
class EnvironmentObjectFactory
{
    public:
    enum EnvironmentObjectType
    {
        WARP_PIPE, // 0
        WARP_PIPE_SHORT, // 1
        WARP_PIPE_TINY, // 2
        BRICK, // so on & so on
        HARD_BLOCK
    };
```
```cpp
class EnvironmentInteractiveObjectFactory // Singleton Factory
{
    public:
    enum EnvironmentInteractiveObjectType
    {
        QUESTION_BLOCK
    };
```
```cpp
class DrawableObjectFactory
{
    public:
    enum DrawableObjectType
    {
        GRASS,
        CLOUD,
        MOUNTAIN
    };
```
```cpp
class LevelFactory
{
    public:
        enum LevelType
        {
            LEVEL_101 = 0,
            HIDDEN_LEVEL_101,
            LEVEL_102,
            HIDDEN_LEVEL_102,
            HIDDEN_LEVEL_112,
            LEVEL_103,
            HIDDEN_LEVEL_103,
            
        };
```
## Format of the map file
All map files should be .txt files, with their name corresponding with the enum specified.

Files should be organised into list of many types of entities.

For example, the first number in the file is the number of enemies, followed by the list of enemies. It is the same for all distince type of entities (items, drawables, etc.).

### Format of an entity in a list

Every enity is represented in one line.

The first number is the type of that entity. The type number is relevant with the type of the list (please use enums for reference).
Following this number, there should be a pair of integer (**not float**) specifying the location.

Example:

![Example_1](/Docs/Images/Figure1.png)
Explanation:
- This map doesn't have any enemy or item
- There are 28 static environment object

*Note: Normally, the location of an entity is relative to the origin of the window (which is its top left corner). However, some entity (like the warp pipe), the Y position is relative to the ground (decreasing from the 750 at the ground).*

### Order of entities types (list order)

You have to input lists in a specified order (shown after this part). Each list contain similar-type entites.

**Order of types:**
1. Enemy
2. Item
3. Static Environment Object
4. Animated Evironment Object
5. Drawable
6. Hole

Example:

![Example_2](/Docs/Images/Figure2.png)

Explanation:
- There are 5 animated environment objects
- All of them are type 0 (QUESTION_BLOCK)
- There is 1 drawble (the type is CLOUD)
- There are 2 holes

*Note: Holes don't need any type; you just need to specify the X position and the width (e.g., 2 is 2 blocks, which is 2 * 100 pixels wide)


