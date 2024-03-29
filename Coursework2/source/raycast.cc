#include "raycast.h"

// Globals:

// File names
char *_inputName       = NULL;
char *_outputNameRGB   = NULL;
char *_outputNameDepth = NULL;

// Image parameters.
int _width      = 100;
int _height     = 100;
float _depthMin = 0;
float _depthMax = 1;

Group * group;
Camera * camera;
Vec3f background;

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &, Image &);

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &, Image &);

int main(int argc, char** argv) {

  int i;
  // sample command lines:
  // raycast -input input.txt -size 100 100 -output output.ppm
  // raycast -input input.txt -size 100 100 -depth 5.5 8.8 output.ppm

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-input") == 0) {
      i++;assert (i < argc);
      _inputName = argv[i];
    } else if (strcmp(argv[i], "-size") == 0) {
      i++;assert (i < argc);
      _width = atoi(argv[i]);
      i++;assert (i < argc);
      _height = atoi(argv[i]);
    } else if (strcmp(argv[i], "-output") == 0) {
      i++;assert (i < argc);
      _outputNameRGB = argv[i];
    } else if (strcmp(argv[i], "-depth") == 0) {
      i++;assert (i < argc);
      _depthMin = atof(argv[i]);
      i++;assert (i < argc);
      _depthMax = atof(argv[i]);
      i++;assert (i < argc);
      _outputNameDepth = argv[i];
    } else {
      printf(
          "Error with command line argument %d: '%s'\n",
          i, argv[i]);
      assert(0);
    }
  }

  // Read in the scene description file, parsing the objects,
  // camera details, etc.
  SceneParser scene(_inputName);

  // Color and depth images.
  Image rgbImage(_width, _height);
  Image depthImage(_width, _height);

  // Do the rendering.
  renderRGBImage(scene, rgbImage);
  renderDepthImage(scene, depthImage);

  // Write results if necessary.
  if (_outputNameRGB != NULL) {
    rgbImage.SavePPM(_outputNameRGB);
  }

  if (_outputNameDepth != NULL){
    depthImage.SavePPM(_outputNameDepth);
  }

}

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &scene, Image &image) {
  
  // Get the group, camera and background
  group = scene.getGroup();
  camera = scene.getCamera();
  background = scene.getBackgroundColor();
  
  // generate rays for each pixel, update Hit and set the pixel in image.
  for(float x = 0; x < (float) image.Width(); ++x) {
    for(float y = 0; y < (float) image.Height(); ++y) {
      Vec2f point;
      point.Set(x / image.Width(), y / image.Height());
      Ray ray = camera->generateRay(point);
      Hit *hit = new Hit(_depthMax, background);
      group->intersect(ray, *hit);
      Vec3f newColour = hit->getColor();
      image.SetPixel(x, y, newColour);
    }
  }
  
}

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &scene, Image &image) {
  
    // Get the group, camera and background
  group = scene.getGroup();
  camera = scene.getCamera();
  background = scene.getBackgroundColor();
  
  // generate rays for each pixel, update Hit and set the pixel in image.
  for(float x = 0; x < (float) image.Width(); ++x) {
    for(float y = 0; y < (float) image.Height(); ++y) {
      Vec2f point;
      point.Set(x / image.Width(), y / image.Height());
      Ray ray = camera->generateRay(point);
      Hit *hit = new Hit(_depthMax, background);
      group->intersect(ray, *hit);
      float distance = hit->getT();
      float depth;
      if(distance <= _depthMin) {
	depth = 1.0;
      }
      else if(distance >= _depthMax) {
	depth = 0.0;
      }
      else {
	float a = _depthMax - _depthMin;
	float b = _depthMax - distance;
	depth = b / a;
      }
      Vec3f newColour;
      newColour.Set(depth, depth, depth);
      image.SetPixel(x, y, newColour);
    }
  }

}
