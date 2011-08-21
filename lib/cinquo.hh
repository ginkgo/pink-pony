#pragma once

#define ILUT_USE_OPENGL

#include "GL/GLee.h"
#include <GL/gl.h>
#include <GL/glfw.h>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <algorithm>

#include <ImathColor.h>
#include <ImathVec.h>
#include <ImathMatrix.h>
#include <ImathGL.h>
#include <ImathBox.h>

#include <assert.h>

// #include <audiere.h>

using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::list;
using std::map;
using std::auto_ptr;
using std::max;
using std::min;


using namespace Imath;

typedef Vec2<unsigned int> V2u;
typedef Vec3<unsigned int> V3u;


#include "utilities.hh"
