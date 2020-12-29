#include <SDL.h>
#include <iostream>
#include "MathVectors.hpp"
#include "RayMarch3D.hpp"
#include <thread>

std::mutex mainWindowRendererMutex;

size_t windowWidthDefault = 255;
size_t windowHeightDefault = 255;

size_t windowWidth = 255;
size_t windowHeight = 255;

size_t windowXResolution = windowWidth;
size_t windowYResolution = windowHeight;

double lightPower = 500;
Vec3 lightPos = {1,1,1};

double camXYAngle = 0;
double camZYAngle = M_PI_2;

double FOV = 2000;

double sphere(Vec3 point)
{
    Vec3 pos = {0,30,0};
    return pos.dest(point) - 10;
};

double infiniteDownSurface(Vec3 point)
{
    return ( 200 - sin(point.y/10) * 10 - sin(point.x/10) * 10) - point.z;
};
double infiniteYSidedSurface(Vec3 point)
{
    return  60 - point.y;
};

void render(SDL_Renderer * renderer, size_t HEIGHT, size_t WIDTH, double maxRayLength)
{
    double t0 = time(nullptr);
    static double a = 0;
    a++;
    if(a > M_PI * 2)
    {
        a = 0;
    };
    lightPos.y = sin(a);
    lightPos.x = cos(a);
    SDL_RenderClear(renderer);
    for(size_t x = 0; x < WIDTH; ++x)
    {
        for(size_t y = 0; y < HEIGHT; ++y)
        {
            Vec3 startPoint = {0, 0, 0};
            Vec3 tracingNormal = {x - (double)WIDTH/2, 20, y - (double)HEIGHT/2};

            tracingNormal = tracingNormal.normalized();

            RGB currPointColor = traceRay(maxRayLength, startPoint, tracingNormal, lightPos, lightPower);
            SDL_SetRenderDrawColor(renderer, currPointColor.r, currPointColor.g, currPointColor.b, 255);
            SDL_RenderDrawPoint(renderer, x*(windowWidth/windowWidthDefault), y*(windowHeight/windowHeightDefault));
        };
    };
    SDL_RenderPresent(renderer);
    double t1 = time(nullptr);
    std::cout<<(t1 - t0)/60<<" FPS"<<std::endl;
};


int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout<<"Cant init SDL"<<std::endl;
        return -1;
    };


    SDL_Window * mainWindow = SDL_CreateWindow("RayMarch3d", 0, 0, windowWidth, windowHeight,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

    if(mainWindow == nullptr)
    {
        std::cout<<"Cant create main window"<<std::endl;
        return -1;
    };


    SDL_Renderer * mainWindowRenderer = SDL_CreateRenderer(mainWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(mainWindowRenderer == nullptr)
    {
        std::cout<<"Cant create main window renderer"<<std::endl;
        return -1;
    };

    SDL_Event event;
    char quit = 0;

    Object sp = {0.0, {255,0,0}, sphere};
    addNode(&sp);

    Object Zsurface = {0.0, {0,255,0}, infiniteDownSurface};
    addNode(&Zsurface);

    Object Ysurface = {0.0, {0,0,255}, infiniteYSidedSurface};
    addNode(&Ysurface);

    for(;quit == 0;)
    {
        for(;SDL_PollEvent(&event);)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    Vec2 startPos = {(double)event.button.x, (double)event.button.y};
                    Vec2 stopPos;
                    for(;SDL_PollEvent(&event);)
                    {
                        stopPos = {(double)event.button.x, (double)event.button.y};
                    };
                    Vec2 dPos = stopPos - startPos;
                    camXYAngle = (dPos.x/M_PI)/50;
                    camZYAngle = (dPos.y/M_PI)/50;
                };
            break;

            case SDL_WINDOWEVENT:

                if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    windowWidth = event.window.data1;
                    windowHeight = event.window.data2;
                };

            break;
            
            default:
                break;
            }
        };
        render(mainWindowRenderer, windowHeight, windowWidth, FOV);
        SDL_Delay(10);
    };
    SDL_Quit();
    return 0;
};