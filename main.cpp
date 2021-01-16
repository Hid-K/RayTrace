#include <SDL.h>
#include <iostream>
#include "MathVectors.hpp"
#include "RayMarch3D.hpp"
#include <chrono>
#include <thread>

size_t windowWidthDefault = 255;
size_t windowHeightDefault = 255;

size_t windowWidth = 255;
size_t windowHeight = 255;

size_t windowXResolution = windowWidth;
size_t windowYResolution = windowHeight;

double lightPower = 1000;
Vec3 lightPos = {0,0,100};

double camXYAngle = 0;
double camZYAngle = M_PI_2;

double FOV = 500;

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
void renderPixel(double maxRayLength, Vec3 startPoint, Vec3 tracingNormal, SDL_Renderer * renderer, size_t x, size_t y)
{
    RGB currPointColor = traceRay(maxRayLength, startPoint, tracingNormal, lightPos, lightPower);
    SDL_SetRenderDrawColor(renderer, currPointColor.r, currPointColor.g, currPointColor.b, 255);
    SDL_RenderDrawPoint(renderer, x*(windowWidth/windowWidthDefault), y*(windowHeight/windowHeightDefault));
};


void render(SDL_Renderer * renderer, size_t HEIGHT, size_t WIDTH, double maxRayLength)
{
    auto t0 = std::chrono::high_resolution_clock::now();
    static double a = 0;
    lightPos.x = cos(a)*100;
    lightPos.y = sin(a)*100;
    if(( a += 0.5 ) >= M_PI * 2)
    {
        a = 0;
    };
    SDL_RenderClear(renderer);
    for(size_t x = 0; x < WIDTH; ++x)
    {
        for(size_t y = 0; y < HEIGHT; ++y)
        {
            Vec3 startPoint = {0, 0, 0};
            Vec3 tracingNormal = {x - (double)WIDTH/2, 20, y - (double)HEIGHT/2};

            tracingNormal = tracingNormal.normalized();
            
            renderPixel(maxRayLength, startPoint, tracingNormal, renderer, x, y);
        };
    };
    SDL_RenderPresent(renderer);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout<<( (double)std::chrono::nanoseconds(1000000000).count() / ( (double)( (t1.time_since_epoch() - t0.time_since_epoch() ).count() ) ) )<<" FPS"<<std::endl;
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

    Object sp = {{255,0,0}, sphere};
    addNode(&sp);

    Object Zsurface = {{0,255,0}, infiniteDownSurface};
    addNode(&Zsurface);

    Object Ysurface = {{0,0,255}, infiniteYSidedSurface};
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