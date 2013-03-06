#define _INCLUDE_MATH
#include "SDLExtension.h"

//int main(void)
//{
//    SDLWindow window;
//    SDLBitmap img;
//
//    window.Initialize(800, 600, false, "Test window");    
//    img.SetBitmap("test.bmp");
//    img.SetColorKey(0xFFFFFF);
//    
//    while( window.Run() )
//    {
//        window.BeginScene(0x0);
//        img.Draw(window.GetDisplaySurface(), point2<s32>(200, 200));
//        window.EndScene();
//    }
//
//    window.Release();
//    
//    return 0;
//}

#include <stdlib.h>
#include <time.h>

#define WIDTH 		800
#define HEIGHT		600
#define FILLCOLOR   0x000000
#define SPEED		0.5f

#undef main

u16 inds[16] = {
0, 1, 2, 3,
4, 5, 6, 7,
4, 5, 1, 0,
3, 2, 6, 7
};

SDLRenderer ren;

void DrawCube(vec4 pv[], u16 ind[], u16 icnt, const color3<u8>& color)
{
		for (int i = 0; i < icnt; i += 4)
			for (int j = 0; j < 4; j++)
				ren.DrawLine2d(point2<f32>(pv[ind[i+j%4]].x, pv[ind[i+j%4]].y), point2<f32>(pv[ind[i+(j+1)%4]].x, pv[ind[i+(j+1)%4]].y), color);
}

int main()
{
	mat4 model, proj, rotation, translation;
	vec4 verts[8], vpos[8];
	f32 angle = 0.0f;
	f32 pos = 1.0f;
	f32 dir = SPEED;
	float dt;
	u32 now, then;
    SDLWindow device;
	
	verts[0] = vec4(0.2, -0.2, -0.2, 1);
	verts[1] = vec4(0.2, 0.2, -0.2, 1);
	verts[2] = vec4(-0.2, 0.2, -0.2, 1);
	verts[3] = vec4(-0.2, -0.2, -0.2, 1);
	verts[4] = vec4(0.2, -0.2, 0.2, 1);
	verts[5] = vec4(0.2, 0.2, 0.2, 1);
	verts[6] = vec4(-0.2, 0.2, 0.2, 1);
	verts[7] = vec4(-0.2, -0.2, 0.2, 1);

	device.Initialize(WIDTH, HEIGHT, false, "LOL");
    ren.SetWindow(&device);
	
	model.Identity();
	proj.Perspective(45.0f, float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);

	then = clock();

	while( device.Run() )
	{
		now = clock();
		dt = float(now - then) / CLOCKS_PER_SEC;
		then = now;
	
		translation.Translation(0, 0, pos);
		rotation.Rotation(angle, angle, 0);
		model =  translation * rotation;
		
		for (int i = 0; i < 8; i++)
		{
			vpos[i] = verts[i] * model * proj;
			vpos[i] = vpos[i] / vpos[i].w;
		}
			
		device.BeginScene(FILLCOLOR);
		DrawCube(vpos, inds, 16, color3<u8>(255,0, 0));
		device.EndScene();        
		
		if (pos > 3.0f || pos < 0.9f)
			dir *= -1;
		
		angle += 1.0f * dt;
		pos += dir * dt;
	}
	
	device.Release();
	return 0;
}