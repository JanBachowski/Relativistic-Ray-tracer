// Rysowanie.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "math.h"
#include "conio.h"
#include "C:\bitmap\bitmap_image.hpp"

class vec3 {
public:
	float x;
	float y;
	float z;
	vec3(float xs = 1, float ys = 1, float zs = 1);
	void Normalize();
	void Rescale(float factor);
};

vec3::vec3(float xs, float ys, float zs) {
	x = xs; y = ys; z = zs;
}

void vec3::Normalize()
{
	float lenght = sqrt(x*x + y * y + z * z);
	x = x / lenght;
	y = y / lenght;
	z = z / lenght;
}

void vec3::Rescale(float factor) {
	x = x * factor;
	y = y * factor;
	z = z * factor;
}

class RGB {
public:
	int R;
	int G;
	int B;
	//RGB(int Rs = 0, int Gs = 0; int Bs = 0);
	RGB(int Rs = 0, int Gs = 0, int Bs = 0);
};

RGB::RGB(int Rs, int Gs, int Bs) {
	R = Rs; G = Gs; B = Bs;
}

class IntersectionParameters {
public:
	float alpha;
	float beta;
	float t;
	bool is_hit;
	IntersectionParameters(float alphas = 0, float betas = 0, float ts = 0, bool is_hits = false);
	IntersectionParameters(float alphas, float betas, float ts);
};

IntersectionParameters::IntersectionParameters(float alphas, float betas, float ts, bool is_hits) {
	alpha = alphas; beta = betas; t = ts;  is_hit = is_hits;
}

class triangle {
public:
	vec3 A, B, C;
	vec3 velocity;
	RGB own_color;
	float brightnes;
	triangle(vec3 As = vec3(1, 1, 1), vec3 Bs = vec3(1, 1, 1), vec3 Cs = vec3(1, 1, 1), vec3 velocitys = vec3(1, 1, 1), RGB own_colors = RGB(0, 0, 0), float brightness = 1);
	IntersectionParameters Hitpoint(vec3 ray, vec3 ray_origin);
	RGB GiveColor(IntersectionParameters place, vec3 ray);
};

triangle::triangle(vec3 As, vec3 Bs, vec3 Cs, vec3 velocitys, RGB own_colors, float brightness) {
	A = As; B = Bs; C = Cs; velocity = velocitys; own_color = own_colors; brightnes = brightness;
}

IntersectionParameters triangle::Hitpoint(vec3 ray, vec3 ray_origin) {
	float camx = ray_origin.x, camy = ray_origin.y, camz = ray_origin.z;
	float raycx = ray.x, raycy = ray.y, raycz = ray.z;
	float ax = A.x, ay = A.y, az = A.z;
	float bx = B.x, by = B.y, bz = B.z;
	float cx = C.x, cy = C.y, cz = C.z;
	float vx = velocity.x, vy = velocity.y, vz = velocity.z;

	IntersectionParameters hit_result = IntersectionParameters(0, 0, 0, 0);


	hit_result.alpha = (ax*(camy*(vz - raycz) + by * (raycz - vz) + (bz - camz)*vy + (camz - bz)*raycy) + camx * (by*(vz - raycz) + ay * (raycz - vz) + (az - bz)*vy + (bz - az)*raycy)

		+ bx * (ay*(vz - raycz) + camy * (raycz - vz) + (camz - az)*vy + (az - camz)*raycy) + (ay*(camz - bz) + by * (az - camz) + (bz - az)*camy)*vx + (by*(camz - az) + ay * (bz - camz) + (az - bz)*camy)*raycx)

		/ (ax*(cy*(vz - raycz) + by * (raycz - vz) + (bz - cz)*vy + (cz - bz)*raycy) + cx * (by*(vz - raycz) + ay * (raycz - vz) + (az - bz)*vy + (bz - az)*raycy) + bx * (ay*(vz - raycz) + cy * (raycz - vz) + (cz - az)*vy + (az - cz)*raycy)

			+ (ay*(cz - bz) + by * (az - cz) + (bz - az)*cy)*vx + (by*(cz - az) + ay * (bz - cz) + (az - bz)*cy)*raycx);

	hit_result.beta = (ax*(cy*(vz - raycz) + camy * (raycz - vz) + (camz - cz)*vy + (cz - camz)*raycy) + cx * (camy*(vz - raycz) + ay * (raycz - vz) + (az - camz)*vy + (camz - az)*raycy)

		+ camx * (ay*(vz - raycz) + cy * (raycz - vz) + (cz - az)*vy + (az - cz)*raycy) + (ay*(cz - camz) + camy * (az - cz) + (camz - az)*cy)*vx + (camy*(cz - az) + ay * (camz - cz) + (az - camz)*cy)*raycx)

		/ (ax*(cy*(vz - raycz) + by * (raycz - vz) + (bz - cz)*vy + (cz - bz)*raycy) + cx * (by*(vz - raycz) + ay * (raycz - vz) + (az - bz)*vy + (bz - az)*raycy) + bx * (ay*(vz - raycz) + cy * (raycz - vz) + (cz - az)*vy + (az - cz)*raycy)

			+ (ay*(cz - bz) + by * (az - cz) + (bz - az)*cy)*vx + (by*(cz - az) + ay * (bz - cz) + (az - bz)*cy)*raycx);

	hit_result.t = -(bx*(ay*(cz - camz) + camy * (az - cz) + (camz - az)*cy) + ax * (camy*(cz - bz) + by * (camz - cz) + (bz - camz)*cy) + camx * (by*(cz - az) + ay * (bz - cz) + (az - bz)*cy) + (ay*(camz - bz) + by * (az - camz) + (bz - az)*camy)*cx)

		/ (ax*(cy*(vz - raycz) + by * (raycz - vz) + (bz - cz)*vy + (cz - bz)*raycy) + cx * (by*(vz - raycz) + ay * (raycz - vz) + (az - bz)*vy + (bz - az)*raycy) + bx * (ay*(vz - raycz) + cy * (raycz - vz) + (cz - az)*vy + (az - cz)*raycy)

			+ (ay*(cz - bz) + by * (az - cz) + (bz - az)*cy)*vx + (by*(cz - az) + ay * (bz - cz) + (az - bz)*cy)*raycx);

	// check if the triangle was hitted by the ray
	if (hit_result.alpha >= 0 && hit_result.beta >= 0 && hit_result.alpha + hit_result.beta <= 1)
		hit_result.is_hit = true;
	else
		hit_result.is_hit = false;

	return hit_result;
}

RGB triangle::GiveColor(IntersectionParameters place, vec3 ray) {
	//float intensity = 100 * brightnes / (place.t * place.t);
	//RGB pixel = RGB(own_color.R, own_color.G, own_color.B);
	//return pixel;
	//	A.x = A.x + 2;
	vec3 BmA = vec3(B.x - A.x, B.y - A.y, B.z - A.z); // u
	vec3 CmA = vec3(C.x - A.x, C.y - A.y, C.z - A.z); // v
	vec3 Norm = vec3(BmA.y*CmA.z - BmA.z*CmA.y, BmA.z*CmA.x - BmA.x*CmA.z, BmA.x*CmA.y - BmA.y*CmA.x);
	Norm.Normalize();
	ray.Normalize();
	float cos_factor = Norm.x*ray.x + Norm.y*ray.y + Norm.z*ray.z;
	RGB pixel = RGB(own_color.R*cos_factor, own_color.G*cos_factor, own_color.B*cos_factor);
	return pixel;
}

class tetraedr {
public:
	vec3 A, B, C, D;
	vec3 velocity;
	triangle faces[4];
	tetraedr(vec3 As, vec3 Bs, vec3 Cs, vec3 Ds, vec3 velocity, RGB own_colors, float brightness_s);
	bool Is_hit(vec3 ray, vec3 ray_origin);
	IntersectionParameters Hitpoint(vec3 ray, vec3 ray_origin);
	RGB GiveColor(vec3 ray, vec3 ray_origin);
};

tetraedr::tetraedr(vec3 As, vec3 Bs, vec3 Cs, vec3 Ds, vec3 velocitys, RGB own_colors, float brightness_s) {
	faces[0] = triangle(As, Bs, Cs, velocitys, own_colors, brightness_s);
	faces[1] = triangle(As, Bs, Ds, velocitys, own_colors, brightness_s);
	faces[2] = triangle(As, Cs, Ds, velocitys, own_colors, brightness_s);
	faces[3] = triangle(Bs, Cs, Ds, velocitys, own_colors, brightness_s);
	velocity = velocitys;
}

RGB tetraedr::GiveColor(vec3 ray, vec3 ray_origin) {
	int index_of_hit_face = 0;
	IntersectionParameters result = faces[0].Hitpoint(ray, ray_origin);
	float t_min = 999999999;
	for (int i = 0; i < 4; i++) {
		IntersectionParameters face_hit = faces[i].Hitpoint(ray, ray_origin);
		if (face_hit.t <= t_min) {
			t_min = face_hit.t;
			//index_of_hit_face = i;
			result = face_hit;
		}
	}
	return faces[index_of_hit_face].GiveColor(result, ray);
}

bool tetraedr::Is_hit(vec3 ray, vec3 ray_origin) {
	bool result = false;
	for (int i = 0; i < 4; i++)
	{
		if (faces[i].Hitpoint(ray, ray_origin).is_hit == true)
		{
			result = true;
		}
	}
	return result;
}



RGB RenderRel_new(int xs, int ys)
{
	RGB pixel;
	float brightness_of_traingle = 1;
	float brightness_of_pyramyde = 2;
	RGB own_color_tri = RGB(200, 200, 0);
	vec3 camera = vec3(50, 50, -20);
	
	vec3 ray_direction = vec3(xs - camera.x, ys - camera.y, -camera.z);
	ray_direction.Normalize();
	float light_speed = 40;

	vec3 A = vec3(30, 30, 300);
	vec3 B = vec3(230, 30, 10);
	vec3 C = vec3(30, 230, 30);
	//vec3 D = vec3(110, 220, -1);
	vec3 velocity1 = vec3(1, 0, 0);
	// scene creation
	//tetraedr pyramyde = tetraedr(A, B, C, D, velocity1, own_color_dupa, brightness_of_pyramyde);
	//	triangle tri = triangle(A, B, C, velocity1, own_color_dupa, brightness_of_traingle);


	triangle tri = triangle(A, B, C, velocity1, own_color_tri, 1);


	IntersectionParameters hit = tri.Hitpoint(ray_direction, camera);
	//	float intensity = 2000 / (hit.t*hit.t);

	/*	if (pyramyde.Is_hit(ray_direction, camera) == true)
	pixel = pyramyde.GiveColor(ray_direction, camera);
	//pixel = RGB(100, 100, 240);
	else
	*///		pixel = RGB(0, 0, 0);

	IntersectionParameters ho = tri.Hitpoint(ray_direction, camera);
	if (ho.is_hit == true)
		pixel = tri.GiveColor(ho, ray_direction);
	else
		pixel = RGB(0, 0, 0);

	return pixel;
}



int main()
{
	bitmap_image image(1000, 1000);

	RGB kolor = RGB(23, 23, 4);


	image_drawer draw(image);

	for (int x = 0; x < 1000; x++)
	{
		for (int y = 0; y < 1000; y++)
		{
			image.set_pixel(x, y, RenderRel_new(x, y).R, RenderRel_new(x, y).G, RenderRel_new(x, y).B);
		}
	}

	image.save_image("output.bmp");

	return 0;
}


/*
float DopplerWaveCoefficient(vec3 origin, vec3 object, vec3 velocity) {
	vec3 pointer = vec3(object.x - origin.x, object.y - origin.y, object.z - origin.z);
	float v_r = DotProduct(velocity, pointer) / pointer.Length;
	1 + v_r / sqrt(1 - ((velocity*velocity) / (light_speed*light_speed)));
}


*/


/*

doppler effect code, using wavelenght

#include <iostream>
using namespace std;

int main()
{
	double w0, w1, v, c;
	int Sound;

	cout << "Is this sound or light? (1=sound, 2=light):";
	cin >> Sound;

	if (Sound == 1)
	{
		cout << "Sound selected" << endl;
		c = 340;
	}
	else
	{
		cout << "Light selected" << endl;
		c = 300000000;
	}

	cout << "Enter the wavelength of the stable source: ";
	cin >> w0;

	cout << "Enter the object's speed: ";
	cin >> v;

	w1 = w0 * (1 - v / c);

	cout << "The new doppler wavelength is " << w1 << endl;

	system("pause");
	return 0;
}

*/

