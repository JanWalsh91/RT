# RT
RT - Revamped Ray Tracer - First major group project

Check out the video: [link](https://www.youtube.com/watch?v=m4NBhRF1hxs&feature=youtu.be)

As a follow up to RTv1 (my first raytracer), RT is a group project in which we vastly expanded our raytracers' capabilities in addition to learning how to collarborate on a project with 4 people through github and other group task managing tools. Here are some additional features we are proud of:

- GTK interface
- GPU multithreading implemented through CUDA
- Handle object transparency, reflectivity with Frensel
- Light travelling through transparent objects have their color modified.
- Linking objects (to move or rotate grouped objects simultaneously)
- Ambient lighting
- Global lighting
- Parallel and Spherical lighting
- Textures (noise, Perlin noise, checkerboard and custom user-added textures)
- Normal mapping
- Antialiasing
- Filters (Sepia, Cartoon, Dalton, and sterioscopy)
- Photon Mapping with caustics
- Save and open .rt files
- Save scenes as bmp files

Click on the arrow to see an example of an .rt file our program will parse:

<details>
    <summary>RT file example</summary><p>

```xml
scene: Scene 1
{
	resolution: 1000, 1000
	ray depth: 5
	background color: 0.0000, 0.0000, 0.0000
	ambient light color: 255.0000, 255.0000, 255.0000
	ka: 0.1000
	sphere: Shere
	{
		position: 0.0000, 0.8000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 204.0000, 0.0000, 255.0000
		radius: 0.7000
		kd: 1.0000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0089
		transparency: 0.0000
		reflection: 0.0000
		beer lambert: 0.0000
	}
	plane: Plane
	{
		position: 0.0000, -2.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 114.0000, 159.0000, 207.0000
		kd: 0.9000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0089
		transparency: 0.0000
		reflection: 0.1000
		beer lambert: 0.0000
	}
	cylinder: Cylinder
	{
		position: -2.5000, 0.4000, -1.0000
		direction: -0.5524, 0.2683, 0.7891
		color: 252.0000, 175.0000, 62.0000
		radius: 0.3000
		height: 2.0000
		kd: 1.0000
		ks: 0.3000
		specular exponent: 31.0000
		ior: 1.0089
		transparency: 0.0000
		reflection: 0.0000
		beer lambert: 0.0000
	}
	cone: Cone
	{
		position: 3.0000, 1.7000, 0.0000
		direction: 0.0000, -1.0000, 0.0000
		color: 117.0000, 80.0000, 123.0000
		radius: 0.7000
		height: 1.5000
		kd: 1.0000
		ks: 0.1000
		specular exponent: 70.0000
		ior: 1.0089
		transparency: 0.0000
		reflection: 0.0000
		beer lambert: 0.0000
	}
	paraboloid: Paraboloid
	{
		position: -6.0000, 1.1000, 0.0000
		direction: 0.0000, -1.0000, 0.0000
		color: 143.6499, 188.1900, 255.0000
		radius: 0.1000
		height: 1.0000
		kd: 1.0000
		ks: 0.0000
		specular exponent: 31.0000
		ior: 1.0089
		transparency: 0.0000
		reflection: 0.0000
		beer lambert: 0.0000
	}
	disk: Disk
	{
		position: 5.8000, 0.5000, -0.5000
		direction: 0.0000, 0.8192, -0.5734
		color: 204.0000, 0.0000, 0.0000
		radius: 0.7000
		kd: 1.0000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0089
		transparency: 0.0000
		reflection: 0.0000
		beer lambert: 0.0000
	}
	cylinder: Socle 1
	{
		position: -6.0000, -2.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 136.0000, 138.0000, 133.0000
		radius: 1.0000
		height: 2.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	disk: Disk1
	{
		position: -3.0000, 0.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 255.0000, 255.0000, 255.0000
		radius: 1.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	cylinder: Socle 2
	{
		position: -3.0000, -2.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 136.0000, 138.0000, 133.0000
		radius: 1.0000
		height: 2.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	disk: Disk2
	{
		position: -6.0000, 0.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 255.0000, 255.0000, 255.0000
		radius: 1.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	cylinder: Socle 3
	{
		position: 0.0000, -2.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 136.0000, 138.0000, 133.0000
		radius: 1.0000
		height: 2.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	disk: Disk3
	{
		position: 0.0000, 0.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 255.0000, 255.0000, 255.0000
		radius: 1.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	cylinder: Socle 4
	{
		position: 3.0000, -2.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 136.0000, 138.0000, 133.0000
		radius: 1.0000
		height: 2.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	disk: Disk4
	{
		position: 3.0000, 0.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 255.0000, 255.0000, 255.0000
		radius: 1.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	cylinder: Socle 5
	{
		position: 6.0000, -2.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 136.0000, 138.0000, 133.0000
		radius: 1.0000
		height: 2.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	disk: Disk5
	{
		position: 6.0000, 0.0000, 0.0000
		direction: 0.0000, 1.0000, 0.0000
		color: 255.0000, 255.0000, 255.0000
		radius: 1.0000
		kd: 0.5000
		ks: 0.1000
		specular exponent: 200.0000
		ior: 1.0095
		transparency: 0.0000
		reflection: 0.5000
		beer lambert: 0.0000
	}
	plane: Bakcground
	{
		position: 0.0000, 0.0000, 18.0000
		direction: 0.0000, 0.0000, 1.0000
		color: 255.0000, 255.0000, 255.0000
		kd: 0.1000
		ks: 0.0000
		specular exponent: 200.0000
		ior: 1.0098
		transparency: 0.0000
		reflection: 1.0000
		beer lambert: 0.0000
	}
	light: Light
	{
		direction: 0.0000, -0.3778, 0.9258
		color:255.0000, 255.0000, 255.0000
		intensity: 40
		kflare: 0.0000
	}
	camera: New Camera
	{
		position: 0.0000, 2.0000, -20.0000
		direction: 0.0000, 0.0000, 1.0000
		fov: 45
		ior: 1.0089
	}
}
```
</p></details>

Here is the output of the file above: <br>
![Everything](https://github.com/JanWalsh91/RT/blob/master/Screenshots/everything.png "Everything") <br>
Objects can be linked together and moved or rotated around easily as a group: <br>
![Android](https://github.com/JanWalsh91/RT/blob/master/Screenshots/Android.png "Android") <br>
Textures such as Perlin Noise, noise, or checkerboard textures can be added to objects. The user can also add his/her own texture: <br>
![Textures](https://github.com/JanWalsh91/RT/blob/master/Screenshots/Textures.png "Textures") <br>
Reflection and Refraction Example: <br>
![Boules Fantaise](https://github.com/JanWalsh91/RT/blob/master/Screenshots/Boule_Fantaisie.png "Boules Fantaisie") <br>
Progressive Photon Map with Caustics: <br>
![PPM with Caustics](https://github.com/JanWalsh91/RT/blob/master/Screenshots/PPM%20with%20Caustics.png "PPM with Caustics") <br>

