// Kamys, Potrox and Bell404ll developers project
//
//          @ All rights reserved
//
// Not open source version, only for course work

#define LOADERROR 3

#include <SDL.h>
#include <GameModule.h>
#include <iostream>

// include WorldInit
// include Fight
// include MainMenu

using namespace std;


const int WIDTH = 1046, HEIGHT = 1024;
const int worldsize = 992;

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

SDL_Surface* knight = NULL;
SDL_Surface* world_texture = NULL;
SDL_Surface* chest = NULL;


int init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Could not init SDL: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow("Dungeon Guardian", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    // Check that the window was successfully created
    if (window == NULL)
    {
        std::cout << "Could not create window: " << SDL_GetError() << endl;
        return 2;
    }

    surface = SDL_GetWindowSurface(window);

    return 0;
}

int load()
{
    knight = SDL_LoadBMP("../SDL2 Test/Materials/Texture/knight.bmp");
    if (knight == NULL)
    {
        return LOADERROR;
    }

    world_texture = SDL_LoadBMP("../SDL2 Test/Materials/Texture/worldmap.bmp");
    if (world_texture == NULL)
    {
        return LOADERROR;
    }

    chest = SDL_LoadBMP("../SDL2 Test/Materials/Texture/chest.bmp");
    if (world_texture == NULL)
    {
        return LOADERROR;
    }

    return 0;
    
}

int draw(PlayerData player, AreaData* world)
{
    //function for draw in SDL
    /*if (SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF) == -1)
    {
        cout << "Could not create render: " << SDL_GetError() << endl;
        return 4;
    }

    SDL_Rect rect1 = { 10, 10, 50, 50 };*/

    SDL_Rect coord;
    
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));


    for (int i = 0; i < worldsize; i++)
    {
        coord.x = world[i].posx;
        coord.y = world[i].posy;
        if (world[i].tileStatus == true)
        {
            if (world[i].tileName == tileType::EMPTY)
            {
                SDL_BlitSurface(world_texture, NULL, surface, &coord);
            }
            else if (world[i].tileName == tileType::CHEST)
            {
                SDL_BlitSurface(world_texture, NULL, surface, &coord);
                SDL_BlitSurface(chest, NULL, surface, &coord);
            }
        }
    }

    coord.x = player.posx;
    coord.y = player.posy;

    SDL_BlitSurface(knight, NULL, surface, &coord);

    return 0;
}

int exit()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    return 0;
}

int SDL_main(int argc, char* argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);    // Hide console window (enable on ~)

    int error_code;
    if ((error_code = init()) != 0)
    {
        std::cout << "Could not init window: " << SDL_GetError() << endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    if ((error_code = load()) != 0)
    {
        std::cout << "Could not load files: " << SDL_GetError() << endl;
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        return error_code;
    }

    AreaData* world = new AreaData[worldsize];
    PlayerData player(1, 50, 0, 1, 1, 10, 10);

    SDL_Event windowEvent;
    bool CnStatus = false, FPSshowhide = false;
    int fps_count = 0, fps_time = time(NULL);

    int count = 32;

    // Two different versions of the fill world function
    for (int i = 1; i < worldsize; i++)
    {
        world[i].posx = world[i - 1].posx + 32;
        world[i].posy = world[i - 1].posy;
        world[i].tileName = tileType::EMPTY;
        world[i].tileStatus = false;

        if (i == count)
        {
            world[i].posx = 10;
            world[i].posy = world[i].posy + 32;
            count += 32;
        }
    }

    world[654].tileName = tileType::CHEST;
    // Two different versions of the fill world function
    /*for (int i = 1, flag = 10; i < (int)sqrt(worldsize); i ++)
    {
        for (int j = i * 32; j < i * 32 + 32; j++)
        {
            if (j == i * 32)
            {
                world[j - 1].posx = 10;
            }
            world[j].posy = flag;
            world[j].posx = world[j - 1].posx + 32;
        }
        flag += 32;
    }*/


    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
            {
                break;
            }
            if (windowEvent.type == SDL_KEYDOWN)
            {
                cout << "Pressed key is: " << windowEvent.key.keysym.sym << endl;
                switch (windowEvent.key.keysym.sym)
                {
                case 96:                        // Show or hide console
                {
                    HideShowConsole(CnStatus);
                    break;
                }
                case 9:                         // Show or hide FPS
                {
                    if (!FPSshowhide)
                    {
                        FPSshowhide = true;
                    }
                    else
                    {
                        FPSshowhide = false;
                        system("CLS");
                    }
                    break;
                }
                case 100:                       // Movment
                {
                    player.posx += 32;
                    break;
                }
                case 115:
                {
                    player.posy += 32;
                    break;
                }
                case 119:
                {
                    player.posy -= 32;
                    break;
                }
                case 97:                        // Endof Movmet
                {
                    player.posx -= 32;
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
        }

        // Check all status of world
        for (int i = 0; i < worldsize; i++)
        {
            if (time(NULL) - world[i].tileStatusTimer > 10)
            {
                world[i].tileStatus = false;
            }

            if (world[i].posy == player.posy)
            {
                if (world[i].posx == player.posx)
                {
                    world[i].tileStatus = true;
                    world[i].tileStatusTimer = time(NULL);
                }
            }
        }


        if (FPSshowhide)
        {
            FPSCounter(fps_count, fps_time);
        }

        draw(player, world);

        SDL_UpdateWindowSurface(window);
    }

    exit();

    return EXIT_SUCCESS;
}