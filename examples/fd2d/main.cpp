#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include "math.h"

#include "visualizer.hpp"
#include "setupAide.hpp"
#include "occa.hpp"

#if OCCA_GL_ENABLED
visualizer vis;
int click;
#endif

setupAide setup;

string model;
int deviceID, platformID;

int width, height;
int Bx, By;

tFloat heightScale;

tFloat currentTime;
tFloat dx, dt;

int stencilRadius;

int mX, mY;

tFloat freq;
tFloat minU, maxU;

vector<tFloat> u1, u2;
vector<tFloat> xyz;

void run();
void setupMesh();

void setupSolver();
void solve();

#if OCCA_GL_ENABLED
void glRun();
void update();
void drawMesh();
#endif

int main(int argc, char **argv){
#if OCCA_GL_ENABLED
  vis.setup("OCL Visualizer", argc, argv);
  glRun();
#else
  run();
#endif

  return 0;
}

#if OCCA_GL_ENABLED
void glRun(){
  setupMesh();
  setupSolver();

  click = 0;

  vis.setExternalFunction(update);
  vis.createViewports(1,1);

  vis.setOutlineColor(0, 0, 0);

  vis.fitBox(0, 0, -dx*width/2, dx*width/2, -dx*height/2, dx*height/2);

  vis.setBackground(0, 0,
                    (GLfloat) 0, (GLfloat) 0, (GLfloat) 0);

  vis.pause(0, 0);

  vis.start();
}
#endif

double totalIters = 0;
double totalFlops = 0;
double totalBW    = 0;
double totalNS    = 0;

void run(){
  setupMesh();
  setupSolver();

  for(int i = 0; i < 50; i++)
    solve();

  std::ofstream avgFile("avg.dat");

  avgFile << totalFlops/totalIters << " " << totalBW/totalIters << " " << totalNS/totalIters << '\n';

  avgFile.close();
  exit(0);
}

void setupMesh(){
  setup.read("setuprc");

  setup.getArgs("MODEL"   , model);
  setup.getArgs("PLATFORM", platformID);
  setup.getArgs("DEVICE"  , deviceID);

  setup.getArgs("STENCIL RADIUS" , stencilRadius);

  setup.getArgs("WIDTH" , width);
  setup.getArgs("HEIGHT", height);

  setup.getArgs("BX", Bx);
  setup.getArgs("BY", By);

  setup.getArgs("DX", dx);
  setup.getArgs("DT", dt);

  setup.getArgs("MIN U", minU);
  setup.getArgs("MAX U", maxU);

  setup.getArgs("FREQUENCY", freq);

  heightScale = 10000.0;

  currentTime = 0;

  std::cout << "MODEL          = " << model << '\n'
            << "STENCIL RADIUS = " << stencilRadius << '\n'
            << "WIDTH          = " << width << '\n'
            << "HEIGHT         = " << height << '\n'
            << "DX             = " << dx << '\n'
            << "DT             = " << dt << '\n'
            << "MIN U          = " << minU << '\n'
            << "MAX U          = " << maxU << '\n'
            << "FREQUENCY      = " << freq << '\n';

  u1.resize(width*height, 0);
  u2.resize(width*height, 0);

  xyz.resize(2*width*height);

  for(int h = 0; h < height; h++){
    for(int w = 0; w < width; w++){
      xyz[2*(h*width + w) + 0] = (w - width/2)*dx;
      xyz[2*(h*width + w) + 1] = (h - height/2)*dx;
    }
  }

  mX = width/2;
  mY = height/2;
}

#if OCCA_GL_ENABLED
void update(){
  if( vis.keyIsPressed(' ') ){
    if(!click){
      solve();
      click = 1;
    }
  }
  else
    click = 0;

  vis.placeViewport(0,0);

  if(!vis.isPaused())
    solve();

  drawMesh();
}

const tFloat colorRange[18] = {1.0, 0.0, 0.0,
                              1.0, 1.0, 0.0,
                              0.0, 1.0, 0.0,
                              0.0, 1.0, 1.0,
                              0.0, 0.0, 1.0};

void getColor(tFloat *ret, tFloat scale, tFloat value, tFloat min){
  tFloat c = (value - min)*scale;

  int b = ((int) 5.0*c) - ((int) c/1.0);

  tFloat ratio = 5.0*c - b;

  ret[0] = colorRange[3*b]   + ratio*(colorRange[3*(b+1)]   - colorRange[3*b]);
  ret[1] = colorRange[3*b+1] + ratio*(colorRange[3*(b+1)+1] - colorRange[3*b+1]);
  ret[2] = colorRange[3*b+2] + ratio*(colorRange[3*(b+1)+2] - colorRange[3*b+2]);
}

void getGrayscale(tFloat *ret, tFloat scale, tFloat value, tFloat min){
  tFloat v = (maxU - value)*scale;

  ret[0] = v;
  ret[1] = v;
  ret[2] = v;
}

void drawMesh(){
  glBegin(GL_QUADS);

  tFloat color1[3];
  tFloat color2[3];
  tFloat color3[3];
  tFloat color4[3];

  tFloat ratio;

  if(minU == maxU)
    ratio = 0;
  else
    ratio = 1.0/(maxU - minU);

  for(int h = 0; h < (height-1); h++){
    for(int w = 0; w < (width-1); w++){
#if 0 // Matlab-like colors
      getColor(color1, ratio, u1[w     + (h)*width]    , minU);
      getColor(color2, ratio, u1[(w+1) + (h)*width]    , minU);
      getColor(color3, ratio, u1[(w+1) + ((h+1)*width)], minU);
      getColor(color4, ratio, u1[w     + ((h+1)*width)], minU);
#else // Grayscale
      getGrayscale(color1, ratio, u1[w     + (h)*width]    , minU);
      getGrayscale(color2, ratio, u1[(w+1) + (h)*width]    , minU);
      getGrayscale(color3, ratio, u1[(w+1) + ((h+1)*width)], minU);
      getGrayscale(color4, ratio, u1[w     + ((h+1)*width)], minU);
#endif

      glColor3f(color1[0], color1[1], color1[2]);
      glVertex3f(xyz[2*(w + (h)*width) + 0],
                 xyz[2*(w + (h)*width) + 1],
                 heightScale*u1[w + (h)*width]);

      glColor3f(color2[0], color2[1], color2[2]);
      glVertex3f(xyz[2*((w+1) + (h)*width) + 0],
                 xyz[2*((w+1) + (h)*width) + 1],
                 heightScale*u1[(w+1) + (h)*width]);

      glColor3f(color3[0], color3[1], color3[2]);
      glVertex3f(xyz[2*((w+1) + ((h+1)*width)) + 0],
                 xyz[2*((w+1) + ((h+1)*width)) + 1],
                 heightScale*u1[(w+1) + ((h+1)*width)]);

      glColor3f(color4[0], color4[1], color4[2]);
      glVertex3f(xyz[2*(w + ((h+1)*width)) + 0],
                 xyz[2*(w + ((h+1)*width)) + 1],
                 heightScale*u1[w + ((h+1)*width)]);
    }
  }

  glEnd();
}
#endif

/*
  Width : Number of nodes in the x direction
  Height: Number of nodes in the y direction

  dx: Spacing between nodes

  dt: Timestepping size

  u1, u2: Recordings

  mX/mY: Wavelet source point
 */

occa::device dev;
occa::memory o_u1, o_u2, o_u3;
occa::kernel fd2d;

void setupSolver(){
  dev.setup(model.c_str(), platformID, deviceID);

  o_u1 = dev.malloc(u1.size()*sizeof(tFloat), &(u1[0]));
  o_u2 = dev.malloc(u1.size()*sizeof(tFloat), &(u1[0]));
  o_u3 = dev.malloc(u2.size()*sizeof(tFloat), &(u2[0]));

  size_t dims      = 2;
  occa::dim inner(Bx, By);
  occa::dim outer((width  + inner.x - 1)/inner.x,
                  (height + inner.y - 1)/inner.y);

  occa::kernelInfo fdInfo;

  fdInfo.addDefine("sr"  , stencilRadius);
  fdInfo.addDefine("w"   , width);
  fdInfo.addDefine("h"   , height);
  fdInfo.addDefine("dx"  , dx);
  fdInfo.addDefine("dt"  , dt);
  fdInfo.addDefine("freq", freq);
  fdInfo.addDefine("mX"  , mX);
  fdInfo.addDefine("mY"  , mY);
  fdInfo.addDefine("Bx"  , Bx);
  fdInfo.addDefine("By"  , By);

  if(sizeof(tFloat) == sizeof(float))
    fdInfo.addDefine("tFloat", "float");
  else
    fdInfo.addDefine("tFloat", "double");

  fd2d = dev.buildKernelFromSource("fd2d.okl", "fd2d", fdInfo);

  fd2d.setWorkingDims(dims, inner, outer);
}

void solve(){
  const int iterations = 20;

  if(currentTime > 1){
    dt = -dt;
  }
  if(currentTime < 0){
    dt = -dt;
  }
  occa::tag startTag;
  occa::tag endTag;

  for(int i = 0; i < iterations; i++){
    currentTime += dt;

    fd2d(o_u1, o_u2, o_u3, currentTime);
    o_u2.swap(o_u3);
    o_u1.swap(o_u2);
  }

  const int stencilDiameter = 2*stencilRadius + 1;

  const tFloat timeTakenPerIteration = 1.0;
  // const tFloat timeTakenPerIteration = fd2d.elapsed(); // Just measure 1 iteration
  const tFloat flops = width*height*(stencilDiameter*4 + 5);
  const tFloat bw    = sizeof(tFloat)*width*height*(2*stencilDiameter + 3);
  const tFloat ns    = width*height;

#if 1
  std::cout << "Time Taken: " << timeTakenPerIteration << '\n';
  std::cout << "GFLOPS    : " << flops/(1.0e9*timeTakenPerIteration) << '\n';
  std::cout << "BW        : " <<    bw/(1.0e9*timeTakenPerIteration) << '\n';
  std::cout << "NS        : " <<    ns/(1.0e6*timeTakenPerIteration) << '\n';
#endif

  totalFlops += flops/(1.0e9*timeTakenPerIteration);
  totalBW    += bw/(1.0e9*timeTakenPerIteration);
  totalNS    += ns/(1.0e6*timeTakenPerIteration);
  totalIters += 1;

  o_u1.copyTo( &(u1[0]) );

#if 0
  std::cout << "Time: " << currentTime << '\n';
  std::cout << "Min : " << *std::min_element(&u1[0], &u1.back()) << '\n';
  std::cout << "Max : " << *std::max_element(&u1[0], &u1.back()) << '\n';
#endif
}
