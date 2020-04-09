#include <cmath>
#include <math.h>
#include <SDL2/SDL.h>
#include <iostream>

#define CAM_POS_X 0
#define CAM_POS_Y 0
#define CAM_POS_Z 0

// #define CAM_DIRECTION_X 
// #define CAM_DIRECTION_Y
// #define CAM_DIRECTION_Z

#define RESOLUTION_X 512
#define RESOLUTION_Y 512

namespace RayTraycing{

	const u_int64_t MAX_MARCHING_STEPS = 320;

	const double FAR = 1300.0;

	const double NEAR = 0.0;

	const double EPSILON = 0.001;

	struct Vec2
	{
		double x, y;
		Vec2 	operator+(Vec2 r){return Vec2(x+r.x,y+r.y);} //Vector add
		Vec2 	operator+(double a){return Vec2(x+a,y+a);} //Vector add
		Vec2 	operator*(double r){return Vec2(x*r,y*r);}       //Vector scaling
		double 	operator%(Vec2 r){return x*r.x+y*r.y;}    //Vector dot product
		// Vec2 	operator^(Vec2 r){return Vec2(y*r.z-z*r.y,z*r.x-x*r.z,x*r.y-y*r.x);} //Cross-product
		Vec2(double a, double b){x=a;y=b;}            //Constructor
		Vec2(){};
		void operator=(Vec2 arg){x=arg.x; x=arg.y;};
	};

	struct Vec3
	{
		double x ,y ,z;
		Vec3 	operator+(Vec3 r){return Vec3(x+r.x,y+r.y,z+r.z);} //Vector add
		Vec3 	operator+(double a)
		{return Vec3(x+a,y+a,z+a);} //Vector add
		Vec3 	operator+(Vec2 r){return Vec3(x+r.x,y+r.y, z);} //Vector add
		Vec3 	operator*(double r){return Vec3(x*r,y*r,z*r);}       //Vector scaling
		double 	operator%(Vec3 r){return x*r.x+y*r.y+z*r.z;}    //Vector dot product
		Vec3 	operator^(Vec3 r){return Vec3(y*r.z-z*r.y,z*r.x-x*r.z,x*r.y-y*r.x);} //Cross-product
		Vec3(double a, double b, double c){x=a;y=b;z=c;}            //Constructor
		Vec3(){};
		void operator=(Vec3 arg){x=arg.x; x=arg.y; x=arg.z;};
		Vec3 operator/(double a){return Vec3(x/a, y/a, z/a);};
		Vec3 operator-(Vec3 a){return Vec3(x-a.x, y-a.y, z-a.z);};
	};

	double min(double * arr, u_int64_t size)
	{
		double res = FAR+1;
		for (u_int64_t i = 0; i < size; ++i)
		{
			if(arr[i] < res){res = arr[i];};
		}
		return res;
	};

	double min(double a, double b)
	{
		if (a<b)
		{
			return a;
		};
		return b;
	};

	double max(double a, double b)
	{
		if (a>b)
		{
			return a;
		};
		return b;
	};

	Vec3 max(Vec3 a, double b)
	{
		if (a.x > b || a.y > b || a.z > b)
		{
			return a;
		}
		return Vec3(b,b,b);
	};

	inline double length(Vec3 vector)
	{
		return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	};

	inline double length(Vec2 vector)
	{
		return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	};

	inline Vec3 normalize(Vec3 vector)
	{
		return vector / length(vector);
	};

	inline double radians(double angleDegrees)
	{
		return (angleDegrees) * M_PI / 180.0;
	};

	inline double dot(Vec3 a, Vec3 b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	};

	inline double Sphere(Vec3 start_point, double rad)
	{
		return length(start_point) - rad;
	};

	inline double Cube( Vec3 p, Vec3 b )
	{
	    Vec3 d = Vec3(abs(p.x),abs(p.y),abs(p.z)) - b;
	    return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d, 0.0));
	};

	double scene(Vec3 pos)
	{
		double figures[] = 
		{
			Sphere(pos, 80.0),
			Sphere(pos - Vec3(80.0,0.0,0.0), 80.0)
			// Cube(pos, Vec3(60.0,60.0,60.0))
		};
		return min(figures, sizeof(figures)/sizeof(*figures));
	};

	inline Vec3 getNormal(Vec3 p)
	{
		return normalize(
			Vec3(
				scene(Vec3(p.x + EPSILON, p.y, p.z)) - scene(Vec3(p.x - EPSILON, p.y, p.z)),
		        scene(Vec3(p.x, p.y + EPSILON, p.z)) - scene(Vec3(p.x, p.y - EPSILON, p.z)),
		        scene(Vec3(p.x, p.y, p.z  + EPSILON)) - scene(Vec3(p.x, p.y, p.z - EPSILON))
				)
			);
	};

	inline double vectorsDist(Vec3 v1, Vec3 v2)
	{
		return sqrt(pow(v1.x - v2.x , 2) + pow(v1.y - v2.y , 2) + pow(v1.z - v2.z , 2));
	};

	double getDistance(Vec3 cam, Vec2 direction)
	{
		double depth =  0;
		for (u_int64_t i = 0; i < MAX_MARCHING_STEPS; ++i)
		{
			float dist = scene(cam + direction + depth);
	        if(dist < EPSILON) {
	            return depth;
	        };

	        depth += dist;

	        if(depth >= FAR) {
	            return FAR;
	        };
		};
		return FAR;
	};

	inline Vec3 cross(Vec3 v1, Vec3 v2)
	{
		return Vec3(v1.y*v2.z - v2.y*v1.z,
					v1.z*v2.x - v2.x*v1.z,
					v1.y*v2.x - v2.y*v1.x);
	};

	Vec3 getRay(Vec2 p, double fov, Vec3 eye, Vec3 target, Vec3 up)
	{
		Vec3 dir = normalize(eye - target);
		Vec3 side = normalize(cross(up, dir));
		double z = - up.y / tan(radians(fov) * 0.5);
		return normalize(side * p.x + up * p.y + dir * z);
	};

	double render(Vec3 cam_pos, Vec2 direction)
	{
		double res = 0.0;
		for (u_int64_t i = 0; i < MAX_MARCHING_STEPS; ++i)
		{
			double dest = getDistance(cam_pos, direction);
			res += dest;
			if(res == NEAR)
			{
				return res;
			};
			if(res >= FAR)
			{
				return FAR;
			};
			if(dest <= EPSILON)
			{
				return res;
			};
			direction = direction + Vec2(cam_pos.x, cam_pos.y) + dest;
		}
		return FAR;
	};

};

int main(int argc, char const *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);

	double cam_x_pos = -395.702;
	double cam_y_pos = 32.2979;
	double cam_z_pos = 60;

	double cam_x_direction = 0;
	double cam_y_direction = 0;
	double cam_z_direction = 0;

	RENDER:

	RayTraycing::Vec3 cam(cam_x_pos, cam_y_pos, cam_z_pos);
	RayTraycing::Vec3 cam_direction(cam_x_direction, cam_y_direction, cam_z_direction);

	RayTraycing::Vec3 pixel(1, 0, 0);

	std::cout<<"Starting render...."<<'\n';

	for (u_int64_t x = 0; x < 512; ++x)
	for (u_int64_t y = 0; y < 512; ++y)
	{
		pixel.x=pixel.y=pixel.z = RayTraycing::render(cam, {(x - cam_direction.x),
															(y - cam_direction.y)});

		SDL_SetRenderDrawColor(renderer, pixel.x, pixel.y, pixel.x, 255);

  		SDL_RenderDrawPoint(renderer, y, x); //Renders on middle of screen.
	};
	SDL_RenderPresent(renderer);

	bool quit = 0;

	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				std::cout<<"Closed by user."<<'\n';
				quit = 1;
	    		SDL_Quit();
			};

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int start_x = event.button.x;
				int start_y = event.button.y;

				int stop_x1 = 0;
				int stop_y1 = 0;

				while(event.button.button == SDL_BUTTON_LEFT)
				{
					// std::cout<<"Gettihg mouce pos."<<'\n';
					stop_x1 = event.button.x;
					stop_y1 = event.button.y;
					SDL_PollEvent(&event);
					SDL_Delay(10);
				};
				
				cam_y_pos += (start_x - stop_x1);
				cam_x_pos += (start_y - stop_y1);

				std::cout<<"X pos ="<<cam_x_pos<<'\n';
				std::cout<<"Y pos ="<<cam_y_pos<<'\n';

				goto RENDER;
			}

			if (event.button.button == SDL_BUTTON_MIDDLE)
			{
				/* code */
			};

			if(event.type == SDL_MOUSEWHEEL)
		    {
		    	RayTraycing::Vec3 cam_norm = normalize(cam) + 0.1;
		    	if(event.wheel.y > 0) // scroll up
		    	{
		    		cam_x_pos += cam_norm.x;
		    		cam_y_pos += cam_norm.y;
		    		cam_z_pos += cam_norm.z;
		    	}
		    	else if(event.wheel.y < 0) // scroll down
		    	{
		    		cam_x_pos -= cam_norm.x;
		    		cam_y_pos -= cam_norm.y;
		    		cam_z_pos -= cam_norm.z;
		    	};
		    	std::cout<<"cam_x_pos="<<cam_x_pos
						 <<" cam_y_pos="<<cam_y_pos
						 <<" cam_z_pos="<<cam_z_pos<<'\n';

				std::cout<<"cam_x_norm="<<cam_norm.x
						 <<" cam_y_norm="<<cam_norm.y
						 <<" cam_z_norm="<<cam_norm.z<<'\n';
		    	goto RENDER;
		    }

		};
		SDL_Delay(90);
	};

	return 0;
}
