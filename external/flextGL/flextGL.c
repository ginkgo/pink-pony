/* WARNING: This file was automatically generated */
/* Do not edit. */

#include "flextGL.h"
#include "GLFW/glfw3.h"

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif


void flextLoadOpenGLFunctions(void);

int flextInit(GLFWwindow* window)
{
  
    int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);

    flextLoadOpenGLFunctions();
    
    /* --- Check for minimal version and profile --- */

    if (major * 10 + minor < 20) {
        fprintf(stderr, "Error: OpenGL version 2.0 not supported.\n");
        fprintf(stderr, "       Your version is %d.%d.\n", major, minor);
        fprintf(stderr, "       Try updating your graphics driver.\n");
        return GL_FALSE;
    }


    /* --- Check for extensions --- */

    if (!glfwExtensionSupported("GL_EXT_framebuffer_object")) {
        fprintf(stderr, "Error: OpenGL extension EXT_framebuffer_object not supported.\n");
        fprintf(stderr, "       Try updating your graphics driver.\n");
        return GL_FALSE;
    }

    if (!glfwExtensionSupported("GL_ARB_texture_float")) {
        fprintf(stderr, "Error: OpenGL extension ARB_texture_float not supported.\n");
        fprintf(stderr, "       Try updating your graphics driver.\n");
        return GL_FALSE;
    }

    if (glfwExtensionSupported("GL_ARB_geometry_shader4")) {
        FLEXT_ARB_geometry_shader4 = GL_TRUE;
    }

    if (glfwExtensionSupported("GL_EXT_transform_feedback")) {
        FLEXT_EXT_transform_feedback = GL_TRUE;
    }

    if (glfwExtensionSupported("GL_EXT_texture_filter_anisotropic")) {
        FLEXT_EXT_texture_filter_anisotropic = GL_TRUE;
    }


    return GL_TRUE;
}



void flextLoadOpenGLFunctions(void)
{
    /* --- Function pointer loading --- */


    /* GL_ARB_geometry_shader4 */

    glpfFramebufferTextureARB = (PFNGLFRAMEBUFFERTEXTUREARB_PROC*)glfwGetProcAddress("glFramebufferTextureARB");
    glpfFramebufferTextureFaceARB = (PFNGLFRAMEBUFFERTEXTUREFACEARB_PROC*)glfwGetProcAddress("glFramebufferTextureFaceARB");
    glpfFramebufferTextureLayerARB = (PFNGLFRAMEBUFFERTEXTURELAYERARB_PROC*)glfwGetProcAddress("glFramebufferTextureLayerARB");
    glpfProgramParameteriARB = (PFNGLPROGRAMPARAMETERIARB_PROC*)glfwGetProcAddress("glProgramParameteriARB");


    /* GL_ARB_texture_float */



    /* GL_EXT_framebuffer_object */

    glpfBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXT_PROC*)glfwGetProcAddress("glBindFramebufferEXT");
    glpfBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXT_PROC*)glfwGetProcAddress("glBindRenderbufferEXT");
    glpfCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXT_PROC*)glfwGetProcAddress("glCheckFramebufferStatusEXT");
    glpfDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXT_PROC*)glfwGetProcAddress("glDeleteFramebuffersEXT");
    glpfDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXT_PROC*)glfwGetProcAddress("glDeleteRenderbuffersEXT");
    glpfFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXT_PROC*)glfwGetProcAddress("glFramebufferRenderbufferEXT");
    glpfFramebufferTexture1DEXT = (PFNGLFRAMEBUFFERTEXTURE1DEXT_PROC*)glfwGetProcAddress("glFramebufferTexture1DEXT");
    glpfFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXT_PROC*)glfwGetProcAddress("glFramebufferTexture2DEXT");
    glpfFramebufferTexture3DEXT = (PFNGLFRAMEBUFFERTEXTURE3DEXT_PROC*)glfwGetProcAddress("glFramebufferTexture3DEXT");
    glpfGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXT_PROC*)glfwGetProcAddress("glGenFramebuffersEXT");
    glpfGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXT_PROC*)glfwGetProcAddress("glGenRenderbuffersEXT");
    glpfGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXT_PROC*)glfwGetProcAddress("glGenerateMipmapEXT");
    glpfGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXT_PROC*)glfwGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
    glpfGetRenderbufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXT_PROC*)glfwGetProcAddress("glGetRenderbufferParameterivEXT");
    glpfIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXT_PROC*)glfwGetProcAddress("glIsFramebufferEXT");
    glpfIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXT_PROC*)glfwGetProcAddress("glIsRenderbufferEXT");
    glpfRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXT_PROC*)glfwGetProcAddress("glRenderbufferStorageEXT");


    /* GL_EXT_texture_filter_anisotropic */



    /* GL_EXT_transform_feedback */

    glpfBeginTransformFeedbackEXT = (PFNGLBEGINTRANSFORMFEEDBACKEXT_PROC*)glfwGetProcAddress("glBeginTransformFeedbackEXT");
    glpfBindBufferBaseEXT = (PFNGLBINDBUFFERBASEEXT_PROC*)glfwGetProcAddress("glBindBufferBaseEXT");
    glpfBindBufferOffsetEXT = (PFNGLBINDBUFFEROFFSETEXT_PROC*)glfwGetProcAddress("glBindBufferOffsetEXT");
    glpfBindBufferRangeEXT = (PFNGLBINDBUFFERRANGEEXT_PROC*)glfwGetProcAddress("glBindBufferRangeEXT");
    glpfEndTransformFeedbackEXT = (PFNGLENDTRANSFORMFEEDBACKEXT_PROC*)glfwGetProcAddress("glEndTransformFeedbackEXT");
    glpfGetTransformFeedbackVaryingEXT = (PFNGLGETTRANSFORMFEEDBACKVARYINGEXT_PROC*)glfwGetProcAddress("glGetTransformFeedbackVaryingEXT");
    glpfTransformFeedbackVaryingsEXT = (PFNGLTRANSFORMFEEDBACKVARYINGSEXT_PROC*)glfwGetProcAddress("glTransformFeedbackVaryingsEXT");


    /* GL_VERSION_1_2 */

    glpfCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3D_PROC*)glfwGetProcAddress("glCopyTexSubImage3D");
    glpfDrawRangeElements = (PFNGLDRAWRANGEELEMENTS_PROC*)glfwGetProcAddress("glDrawRangeElements");
    glpfTexImage3D = (PFNGLTEXIMAGE3D_PROC*)glfwGetProcAddress("glTexImage3D");
    glpfTexSubImage3D = (PFNGLTEXSUBIMAGE3D_PROC*)glfwGetProcAddress("glTexSubImage3D");


    /* GL_VERSION_1_3 */

    glpfActiveTexture = (PFNGLACTIVETEXTURE_PROC*)glfwGetProcAddress("glActiveTexture");
    glpfClientActiveTexture = (PFNGLCLIENTACTIVETEXTURE_PROC*)glfwGetProcAddress("glClientActiveTexture");
    glpfCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1D_PROC*)glfwGetProcAddress("glCompressedTexImage1D");
    glpfCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2D_PROC*)glfwGetProcAddress("glCompressedTexImage2D");
    glpfCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3D_PROC*)glfwGetProcAddress("glCompressedTexImage3D");
    glpfCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1D_PROC*)glfwGetProcAddress("glCompressedTexSubImage1D");
    glpfCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2D_PROC*)glfwGetProcAddress("glCompressedTexSubImage2D");
    glpfCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3D_PROC*)glfwGetProcAddress("glCompressedTexSubImage3D");
    glpfGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGE_PROC*)glfwGetProcAddress("glGetCompressedTexImage");
    glpfLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXD_PROC*)glfwGetProcAddress("glLoadTransposeMatrixd");
    glpfLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXF_PROC*)glfwGetProcAddress("glLoadTransposeMatrixf");
    glpfMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXD_PROC*)glfwGetProcAddress("glMultTransposeMatrixd");
    glpfMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXF_PROC*)glfwGetProcAddress("glMultTransposeMatrixf");
    glpfMultiTexCoord1d = (PFNGLMULTITEXCOORD1D_PROC*)glfwGetProcAddress("glMultiTexCoord1d");
    glpfMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DV_PROC*)glfwGetProcAddress("glMultiTexCoord1dv");
    glpfMultiTexCoord1f = (PFNGLMULTITEXCOORD1F_PROC*)glfwGetProcAddress("glMultiTexCoord1f");
    glpfMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FV_PROC*)glfwGetProcAddress("glMultiTexCoord1fv");
    glpfMultiTexCoord1i = (PFNGLMULTITEXCOORD1I_PROC*)glfwGetProcAddress("glMultiTexCoord1i");
    glpfMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IV_PROC*)glfwGetProcAddress("glMultiTexCoord1iv");
    glpfMultiTexCoord1s = (PFNGLMULTITEXCOORD1S_PROC*)glfwGetProcAddress("glMultiTexCoord1s");
    glpfMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SV_PROC*)glfwGetProcAddress("glMultiTexCoord1sv");
    glpfMultiTexCoord2d = (PFNGLMULTITEXCOORD2D_PROC*)glfwGetProcAddress("glMultiTexCoord2d");
    glpfMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DV_PROC*)glfwGetProcAddress("glMultiTexCoord2dv");
    glpfMultiTexCoord2f = (PFNGLMULTITEXCOORD2F_PROC*)glfwGetProcAddress("glMultiTexCoord2f");
    glpfMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FV_PROC*)glfwGetProcAddress("glMultiTexCoord2fv");
    glpfMultiTexCoord2i = (PFNGLMULTITEXCOORD2I_PROC*)glfwGetProcAddress("glMultiTexCoord2i");
    glpfMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IV_PROC*)glfwGetProcAddress("glMultiTexCoord2iv");
    glpfMultiTexCoord2s = (PFNGLMULTITEXCOORD2S_PROC*)glfwGetProcAddress("glMultiTexCoord2s");
    glpfMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SV_PROC*)glfwGetProcAddress("glMultiTexCoord2sv");
    glpfMultiTexCoord3d = (PFNGLMULTITEXCOORD3D_PROC*)glfwGetProcAddress("glMultiTexCoord3d");
    glpfMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DV_PROC*)glfwGetProcAddress("glMultiTexCoord3dv");
    glpfMultiTexCoord3f = (PFNGLMULTITEXCOORD3F_PROC*)glfwGetProcAddress("glMultiTexCoord3f");
    glpfMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FV_PROC*)glfwGetProcAddress("glMultiTexCoord3fv");
    glpfMultiTexCoord3i = (PFNGLMULTITEXCOORD3I_PROC*)glfwGetProcAddress("glMultiTexCoord3i");
    glpfMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IV_PROC*)glfwGetProcAddress("glMultiTexCoord3iv");
    glpfMultiTexCoord3s = (PFNGLMULTITEXCOORD3S_PROC*)glfwGetProcAddress("glMultiTexCoord3s");
    glpfMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SV_PROC*)glfwGetProcAddress("glMultiTexCoord3sv");
    glpfMultiTexCoord4d = (PFNGLMULTITEXCOORD4D_PROC*)glfwGetProcAddress("glMultiTexCoord4d");
    glpfMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DV_PROC*)glfwGetProcAddress("glMultiTexCoord4dv");
    glpfMultiTexCoord4f = (PFNGLMULTITEXCOORD4F_PROC*)glfwGetProcAddress("glMultiTexCoord4f");
    glpfMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FV_PROC*)glfwGetProcAddress("glMultiTexCoord4fv");
    glpfMultiTexCoord4i = (PFNGLMULTITEXCOORD4I_PROC*)glfwGetProcAddress("glMultiTexCoord4i");
    glpfMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IV_PROC*)glfwGetProcAddress("glMultiTexCoord4iv");
    glpfMultiTexCoord4s = (PFNGLMULTITEXCOORD4S_PROC*)glfwGetProcAddress("glMultiTexCoord4s");
    glpfMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SV_PROC*)glfwGetProcAddress("glMultiTexCoord4sv");
    glpfSampleCoverage = (PFNGLSAMPLECOVERAGE_PROC*)glfwGetProcAddress("glSampleCoverage");


    /* GL_VERSION_1_4 */

    glpfBlendColor = (PFNGLBLENDCOLOR_PROC*)glfwGetProcAddress("glBlendColor");
    glpfBlendEquation = (PFNGLBLENDEQUATION_PROC*)glfwGetProcAddress("glBlendEquation");
    glpfBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATE_PROC*)glfwGetProcAddress("glBlendFuncSeparate");
    glpfFogCoordPointer = (PFNGLFOGCOORDPOINTER_PROC*)glfwGetProcAddress("glFogCoordPointer");
    glpfFogCoordd = (PFNGLFOGCOORDD_PROC*)glfwGetProcAddress("glFogCoordd");
    glpfFogCoorddv = (PFNGLFOGCOORDDV_PROC*)glfwGetProcAddress("glFogCoorddv");
    glpfFogCoordf = (PFNGLFOGCOORDF_PROC*)glfwGetProcAddress("glFogCoordf");
    glpfFogCoordfv = (PFNGLFOGCOORDFV_PROC*)glfwGetProcAddress("glFogCoordfv");
    glpfMultiDrawArrays = (PFNGLMULTIDRAWARRAYS_PROC*)glfwGetProcAddress("glMultiDrawArrays");
    glpfMultiDrawElements = (PFNGLMULTIDRAWELEMENTS_PROC*)glfwGetProcAddress("glMultiDrawElements");
    glpfPointParameterf = (PFNGLPOINTPARAMETERF_PROC*)glfwGetProcAddress("glPointParameterf");
    glpfPointParameterfv = (PFNGLPOINTPARAMETERFV_PROC*)glfwGetProcAddress("glPointParameterfv");
    glpfPointParameteri = (PFNGLPOINTPARAMETERI_PROC*)glfwGetProcAddress("glPointParameteri");
    glpfPointParameteriv = (PFNGLPOINTPARAMETERIV_PROC*)glfwGetProcAddress("glPointParameteriv");
    glpfSecondaryColor3b = (PFNGLSECONDARYCOLOR3B_PROC*)glfwGetProcAddress("glSecondaryColor3b");
    glpfSecondaryColor3bv = (PFNGLSECONDARYCOLOR3BV_PROC*)glfwGetProcAddress("glSecondaryColor3bv");
    glpfSecondaryColor3d = (PFNGLSECONDARYCOLOR3D_PROC*)glfwGetProcAddress("glSecondaryColor3d");
    glpfSecondaryColor3dv = (PFNGLSECONDARYCOLOR3DV_PROC*)glfwGetProcAddress("glSecondaryColor3dv");
    glpfSecondaryColor3f = (PFNGLSECONDARYCOLOR3F_PROC*)glfwGetProcAddress("glSecondaryColor3f");
    glpfSecondaryColor3fv = (PFNGLSECONDARYCOLOR3FV_PROC*)glfwGetProcAddress("glSecondaryColor3fv");
    glpfSecondaryColor3i = (PFNGLSECONDARYCOLOR3I_PROC*)glfwGetProcAddress("glSecondaryColor3i");
    glpfSecondaryColor3iv = (PFNGLSECONDARYCOLOR3IV_PROC*)glfwGetProcAddress("glSecondaryColor3iv");
    glpfSecondaryColor3s = (PFNGLSECONDARYCOLOR3S_PROC*)glfwGetProcAddress("glSecondaryColor3s");
    glpfSecondaryColor3sv = (PFNGLSECONDARYCOLOR3SV_PROC*)glfwGetProcAddress("glSecondaryColor3sv");
    glpfSecondaryColor3ub = (PFNGLSECONDARYCOLOR3UB_PROC*)glfwGetProcAddress("glSecondaryColor3ub");
    glpfSecondaryColor3ubv = (PFNGLSECONDARYCOLOR3UBV_PROC*)glfwGetProcAddress("glSecondaryColor3ubv");
    glpfSecondaryColor3ui = (PFNGLSECONDARYCOLOR3UI_PROC*)glfwGetProcAddress("glSecondaryColor3ui");
    glpfSecondaryColor3uiv = (PFNGLSECONDARYCOLOR3UIV_PROC*)glfwGetProcAddress("glSecondaryColor3uiv");
    glpfSecondaryColor3us = (PFNGLSECONDARYCOLOR3US_PROC*)glfwGetProcAddress("glSecondaryColor3us");
    glpfSecondaryColor3usv = (PFNGLSECONDARYCOLOR3USV_PROC*)glfwGetProcAddress("glSecondaryColor3usv");
    glpfSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTER_PROC*)glfwGetProcAddress("glSecondaryColorPointer");
    glpfWindowPos2d = (PFNGLWINDOWPOS2D_PROC*)glfwGetProcAddress("glWindowPos2d");
    glpfWindowPos2dv = (PFNGLWINDOWPOS2DV_PROC*)glfwGetProcAddress("glWindowPos2dv");
    glpfWindowPos2f = (PFNGLWINDOWPOS2F_PROC*)glfwGetProcAddress("glWindowPos2f");
    glpfWindowPos2fv = (PFNGLWINDOWPOS2FV_PROC*)glfwGetProcAddress("glWindowPos2fv");
    glpfWindowPos2i = (PFNGLWINDOWPOS2I_PROC*)glfwGetProcAddress("glWindowPos2i");
    glpfWindowPos2iv = (PFNGLWINDOWPOS2IV_PROC*)glfwGetProcAddress("glWindowPos2iv");
    glpfWindowPos2s = (PFNGLWINDOWPOS2S_PROC*)glfwGetProcAddress("glWindowPos2s");
    glpfWindowPos2sv = (PFNGLWINDOWPOS2SV_PROC*)glfwGetProcAddress("glWindowPos2sv");
    glpfWindowPos3d = (PFNGLWINDOWPOS3D_PROC*)glfwGetProcAddress("glWindowPos3d");
    glpfWindowPos3dv = (PFNGLWINDOWPOS3DV_PROC*)glfwGetProcAddress("glWindowPos3dv");
    glpfWindowPos3f = (PFNGLWINDOWPOS3F_PROC*)glfwGetProcAddress("glWindowPos3f");
    glpfWindowPos3fv = (PFNGLWINDOWPOS3FV_PROC*)glfwGetProcAddress("glWindowPos3fv");
    glpfWindowPos3i = (PFNGLWINDOWPOS3I_PROC*)glfwGetProcAddress("glWindowPos3i");
    glpfWindowPos3iv = (PFNGLWINDOWPOS3IV_PROC*)glfwGetProcAddress("glWindowPos3iv");
    glpfWindowPos3s = (PFNGLWINDOWPOS3S_PROC*)glfwGetProcAddress("glWindowPos3s");
    glpfWindowPos3sv = (PFNGLWINDOWPOS3SV_PROC*)glfwGetProcAddress("glWindowPos3sv");


    /* GL_VERSION_1_5 */

    glpfBeginQuery = (PFNGLBEGINQUERY_PROC*)glfwGetProcAddress("glBeginQuery");
    glpfBindBuffer = (PFNGLBINDBUFFER_PROC*)glfwGetProcAddress("glBindBuffer");
    glpfBufferData = (PFNGLBUFFERDATA_PROC*)glfwGetProcAddress("glBufferData");
    glpfBufferSubData = (PFNGLBUFFERSUBDATA_PROC*)glfwGetProcAddress("glBufferSubData");
    glpfDeleteBuffers = (PFNGLDELETEBUFFERS_PROC*)glfwGetProcAddress("glDeleteBuffers");
    glpfDeleteQueries = (PFNGLDELETEQUERIES_PROC*)glfwGetProcAddress("glDeleteQueries");
    glpfEndQuery = (PFNGLENDQUERY_PROC*)glfwGetProcAddress("glEndQuery");
    glpfGenBuffers = (PFNGLGENBUFFERS_PROC*)glfwGetProcAddress("glGenBuffers");
    glpfGenQueries = (PFNGLGENQUERIES_PROC*)glfwGetProcAddress("glGenQueries");
    glpfGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIV_PROC*)glfwGetProcAddress("glGetBufferParameteriv");
    glpfGetBufferPointerv = (PFNGLGETBUFFERPOINTERV_PROC*)glfwGetProcAddress("glGetBufferPointerv");
    glpfGetBufferSubData = (PFNGLGETBUFFERSUBDATA_PROC*)glfwGetProcAddress("glGetBufferSubData");
    glpfGetQueryObjectiv = (PFNGLGETQUERYOBJECTIV_PROC*)glfwGetProcAddress("glGetQueryObjectiv");
    glpfGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIV_PROC*)glfwGetProcAddress("glGetQueryObjectuiv");
    glpfGetQueryiv = (PFNGLGETQUERYIV_PROC*)glfwGetProcAddress("glGetQueryiv");
    glpfIsBuffer = (PFNGLISBUFFER_PROC*)glfwGetProcAddress("glIsBuffer");
    glpfIsQuery = (PFNGLISQUERY_PROC*)glfwGetProcAddress("glIsQuery");
    glpfMapBuffer = (PFNGLMAPBUFFER_PROC*)glfwGetProcAddress("glMapBuffer");
    glpfUnmapBuffer = (PFNGLUNMAPBUFFER_PROC*)glfwGetProcAddress("glUnmapBuffer");


    /* GL_VERSION_2_0 */

    glpfAttachShader = (PFNGLATTACHSHADER_PROC*)glfwGetProcAddress("glAttachShader");
    glpfBindAttribLocation = (PFNGLBINDATTRIBLOCATION_PROC*)glfwGetProcAddress("glBindAttribLocation");
    glpfBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATE_PROC*)glfwGetProcAddress("glBlendEquationSeparate");
    glpfCompileShader = (PFNGLCOMPILESHADER_PROC*)glfwGetProcAddress("glCompileShader");
    glpfCreateProgram = (PFNGLCREATEPROGRAM_PROC*)glfwGetProcAddress("glCreateProgram");
    glpfCreateShader = (PFNGLCREATESHADER_PROC*)glfwGetProcAddress("glCreateShader");
    glpfDeleteProgram = (PFNGLDELETEPROGRAM_PROC*)glfwGetProcAddress("glDeleteProgram");
    glpfDeleteShader = (PFNGLDELETESHADER_PROC*)glfwGetProcAddress("glDeleteShader");
    glpfDetachShader = (PFNGLDETACHSHADER_PROC*)glfwGetProcAddress("glDetachShader");
    glpfDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAY_PROC*)glfwGetProcAddress("glDisableVertexAttribArray");
    glpfDrawBuffers = (PFNGLDRAWBUFFERS_PROC*)glfwGetProcAddress("glDrawBuffers");
    glpfEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAY_PROC*)glfwGetProcAddress("glEnableVertexAttribArray");
    glpfGetActiveAttrib = (PFNGLGETACTIVEATTRIB_PROC*)glfwGetProcAddress("glGetActiveAttrib");
    glpfGetActiveUniform = (PFNGLGETACTIVEUNIFORM_PROC*)glfwGetProcAddress("glGetActiveUniform");
    glpfGetAttachedShaders = (PFNGLGETATTACHEDSHADERS_PROC*)glfwGetProcAddress("glGetAttachedShaders");
    glpfGetAttribLocation = (PFNGLGETATTRIBLOCATION_PROC*)glfwGetProcAddress("glGetAttribLocation");
    glpfGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOG_PROC*)glfwGetProcAddress("glGetProgramInfoLog");
    glpfGetProgramiv = (PFNGLGETPROGRAMIV_PROC*)glfwGetProcAddress("glGetProgramiv");
    glpfGetShaderInfoLog = (PFNGLGETSHADERINFOLOG_PROC*)glfwGetProcAddress("glGetShaderInfoLog");
    glpfGetShaderSource = (PFNGLGETSHADERSOURCE_PROC*)glfwGetProcAddress("glGetShaderSource");
    glpfGetShaderiv = (PFNGLGETSHADERIV_PROC*)glfwGetProcAddress("glGetShaderiv");
    glpfGetUniformLocation = (PFNGLGETUNIFORMLOCATION_PROC*)glfwGetProcAddress("glGetUniformLocation");
    glpfGetUniformfv = (PFNGLGETUNIFORMFV_PROC*)glfwGetProcAddress("glGetUniformfv");
    glpfGetUniformiv = (PFNGLGETUNIFORMIV_PROC*)glfwGetProcAddress("glGetUniformiv");
    glpfGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERV_PROC*)glfwGetProcAddress("glGetVertexAttribPointerv");
    glpfGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDV_PROC*)glfwGetProcAddress("glGetVertexAttribdv");
    glpfGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFV_PROC*)glfwGetProcAddress("glGetVertexAttribfv");
    glpfGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIV_PROC*)glfwGetProcAddress("glGetVertexAttribiv");
    glpfIsProgram = (PFNGLISPROGRAM_PROC*)glfwGetProcAddress("glIsProgram");
    glpfIsShader = (PFNGLISSHADER_PROC*)glfwGetProcAddress("glIsShader");
    glpfLinkProgram = (PFNGLLINKPROGRAM_PROC*)glfwGetProcAddress("glLinkProgram");
    glpfShaderSource = (PFNGLSHADERSOURCE_PROC*)glfwGetProcAddress("glShaderSource");
    glpfStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATE_PROC*)glfwGetProcAddress("glStencilFuncSeparate");
    glpfStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATE_PROC*)glfwGetProcAddress("glStencilMaskSeparate");
    glpfStencilOpSeparate = (PFNGLSTENCILOPSEPARATE_PROC*)glfwGetProcAddress("glStencilOpSeparate");
    glpfUniform1f = (PFNGLUNIFORM1F_PROC*)glfwGetProcAddress("glUniform1f");
    glpfUniform1fv = (PFNGLUNIFORM1FV_PROC*)glfwGetProcAddress("glUniform1fv");
    glpfUniform1i = (PFNGLUNIFORM1I_PROC*)glfwGetProcAddress("glUniform1i");
    glpfUniform1iv = (PFNGLUNIFORM1IV_PROC*)glfwGetProcAddress("glUniform1iv");
    glpfUniform2f = (PFNGLUNIFORM2F_PROC*)glfwGetProcAddress("glUniform2f");
    glpfUniform2fv = (PFNGLUNIFORM2FV_PROC*)glfwGetProcAddress("glUniform2fv");
    glpfUniform2i = (PFNGLUNIFORM2I_PROC*)glfwGetProcAddress("glUniform2i");
    glpfUniform2iv = (PFNGLUNIFORM2IV_PROC*)glfwGetProcAddress("glUniform2iv");
    glpfUniform3f = (PFNGLUNIFORM3F_PROC*)glfwGetProcAddress("glUniform3f");
    glpfUniform3fv = (PFNGLUNIFORM3FV_PROC*)glfwGetProcAddress("glUniform3fv");
    glpfUniform3i = (PFNGLUNIFORM3I_PROC*)glfwGetProcAddress("glUniform3i");
    glpfUniform3iv = (PFNGLUNIFORM3IV_PROC*)glfwGetProcAddress("glUniform3iv");
    glpfUniform4f = (PFNGLUNIFORM4F_PROC*)glfwGetProcAddress("glUniform4f");
    glpfUniform4fv = (PFNGLUNIFORM4FV_PROC*)glfwGetProcAddress("glUniform4fv");
    glpfUniform4i = (PFNGLUNIFORM4I_PROC*)glfwGetProcAddress("glUniform4i");
    glpfUniform4iv = (PFNGLUNIFORM4IV_PROC*)glfwGetProcAddress("glUniform4iv");
    glpfUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FV_PROC*)glfwGetProcAddress("glUniformMatrix2fv");
    glpfUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FV_PROC*)glfwGetProcAddress("glUniformMatrix3fv");
    glpfUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FV_PROC*)glfwGetProcAddress("glUniformMatrix4fv");
    glpfUseProgram = (PFNGLUSEPROGRAM_PROC*)glfwGetProcAddress("glUseProgram");
    glpfValidateProgram = (PFNGLVALIDATEPROGRAM_PROC*)glfwGetProcAddress("glValidateProgram");
    glpfVertexAttrib1d = (PFNGLVERTEXATTRIB1D_PROC*)glfwGetProcAddress("glVertexAttrib1d");
    glpfVertexAttrib1dv = (PFNGLVERTEXATTRIB1DV_PROC*)glfwGetProcAddress("glVertexAttrib1dv");
    glpfVertexAttrib1f = (PFNGLVERTEXATTRIB1F_PROC*)glfwGetProcAddress("glVertexAttrib1f");
    glpfVertexAttrib1fv = (PFNGLVERTEXATTRIB1FV_PROC*)glfwGetProcAddress("glVertexAttrib1fv");
    glpfVertexAttrib1s = (PFNGLVERTEXATTRIB1S_PROC*)glfwGetProcAddress("glVertexAttrib1s");
    glpfVertexAttrib1sv = (PFNGLVERTEXATTRIB1SV_PROC*)glfwGetProcAddress("glVertexAttrib1sv");
    glpfVertexAttrib2d = (PFNGLVERTEXATTRIB2D_PROC*)glfwGetProcAddress("glVertexAttrib2d");
    glpfVertexAttrib2dv = (PFNGLVERTEXATTRIB2DV_PROC*)glfwGetProcAddress("glVertexAttrib2dv");
    glpfVertexAttrib2f = (PFNGLVERTEXATTRIB2F_PROC*)glfwGetProcAddress("glVertexAttrib2f");
    glpfVertexAttrib2fv = (PFNGLVERTEXATTRIB2FV_PROC*)glfwGetProcAddress("glVertexAttrib2fv");
    glpfVertexAttrib2s = (PFNGLVERTEXATTRIB2S_PROC*)glfwGetProcAddress("glVertexAttrib2s");
    glpfVertexAttrib2sv = (PFNGLVERTEXATTRIB2SV_PROC*)glfwGetProcAddress("glVertexAttrib2sv");
    glpfVertexAttrib3d = (PFNGLVERTEXATTRIB3D_PROC*)glfwGetProcAddress("glVertexAttrib3d");
    glpfVertexAttrib3dv = (PFNGLVERTEXATTRIB3DV_PROC*)glfwGetProcAddress("glVertexAttrib3dv");
    glpfVertexAttrib3f = (PFNGLVERTEXATTRIB3F_PROC*)glfwGetProcAddress("glVertexAttrib3f");
    glpfVertexAttrib3fv = (PFNGLVERTEXATTRIB3FV_PROC*)glfwGetProcAddress("glVertexAttrib3fv");
    glpfVertexAttrib3s = (PFNGLVERTEXATTRIB3S_PROC*)glfwGetProcAddress("glVertexAttrib3s");
    glpfVertexAttrib3sv = (PFNGLVERTEXATTRIB3SV_PROC*)glfwGetProcAddress("glVertexAttrib3sv");
    glpfVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBV_PROC*)glfwGetProcAddress("glVertexAttrib4Nbv");
    glpfVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIV_PROC*)glfwGetProcAddress("glVertexAttrib4Niv");
    glpfVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSV_PROC*)glfwGetProcAddress("glVertexAttrib4Nsv");
    glpfVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUB_PROC*)glfwGetProcAddress("glVertexAttrib4Nub");
    glpfVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBV_PROC*)glfwGetProcAddress("glVertexAttrib4Nubv");
    glpfVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIV_PROC*)glfwGetProcAddress("glVertexAttrib4Nuiv");
    glpfVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSV_PROC*)glfwGetProcAddress("glVertexAttrib4Nusv");
    glpfVertexAttrib4bv = (PFNGLVERTEXATTRIB4BV_PROC*)glfwGetProcAddress("glVertexAttrib4bv");
    glpfVertexAttrib4d = (PFNGLVERTEXATTRIB4D_PROC*)glfwGetProcAddress("glVertexAttrib4d");
    glpfVertexAttrib4dv = (PFNGLVERTEXATTRIB4DV_PROC*)glfwGetProcAddress("glVertexAttrib4dv");
    glpfVertexAttrib4f = (PFNGLVERTEXATTRIB4F_PROC*)glfwGetProcAddress("glVertexAttrib4f");
    glpfVertexAttrib4fv = (PFNGLVERTEXATTRIB4FV_PROC*)glfwGetProcAddress("glVertexAttrib4fv");
    glpfVertexAttrib4iv = (PFNGLVERTEXATTRIB4IV_PROC*)glfwGetProcAddress("glVertexAttrib4iv");
    glpfVertexAttrib4s = (PFNGLVERTEXATTRIB4S_PROC*)glfwGetProcAddress("glVertexAttrib4s");
    glpfVertexAttrib4sv = (PFNGLVERTEXATTRIB4SV_PROC*)glfwGetProcAddress("glVertexAttrib4sv");
    glpfVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBV_PROC*)glfwGetProcAddress("glVertexAttrib4ubv");
    glpfVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIV_PROC*)glfwGetProcAddress("glVertexAttrib4uiv");
    glpfVertexAttrib4usv = (PFNGLVERTEXATTRIB4USV_PROC*)glfwGetProcAddress("glVertexAttrib4usv");
    glpfVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTER_PROC*)glfwGetProcAddress("glVertexAttribPointer");


}

/* ----------------------- Extension flag definitions ---------------------- */
int FLEXT_EXT_framebuffer_object = GL_FALSE;
int FLEXT_ARB_texture_float = GL_FALSE;
int FLEXT_ARB_geometry_shader4 = GL_FALSE;
int FLEXT_EXT_transform_feedback = GL_FALSE;
int FLEXT_EXT_texture_filter_anisotropic = GL_FALSE;

/* ---------------------- Function pointer definitions --------------------- */

/* GL_ARB_geometry_shader4 */

PFNGLFRAMEBUFFERTEXTUREARB_PROC* glpfFramebufferTextureARB = NULL;
PFNGLFRAMEBUFFERTEXTUREFACEARB_PROC* glpfFramebufferTextureFaceARB = NULL;
PFNGLFRAMEBUFFERTEXTURELAYERARB_PROC* glpfFramebufferTextureLayerARB = NULL;
PFNGLPROGRAMPARAMETERIARB_PROC* glpfProgramParameteriARB = NULL;

/* GL_EXT_framebuffer_object */

PFNGLBINDFRAMEBUFFEREXT_PROC* glpfBindFramebufferEXT = NULL;
PFNGLBINDRENDERBUFFEREXT_PROC* glpfBindRenderbufferEXT = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXT_PROC* glpfCheckFramebufferStatusEXT = NULL;
PFNGLDELETEFRAMEBUFFERSEXT_PROC* glpfDeleteFramebuffersEXT = NULL;
PFNGLDELETERENDERBUFFERSEXT_PROC* glpfDeleteRenderbuffersEXT = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXT_PROC* glpfFramebufferRenderbufferEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE1DEXT_PROC* glpfFramebufferTexture1DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXT_PROC* glpfFramebufferTexture2DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE3DEXT_PROC* glpfFramebufferTexture3DEXT = NULL;
PFNGLGENFRAMEBUFFERSEXT_PROC* glpfGenFramebuffersEXT = NULL;
PFNGLGENRENDERBUFFERSEXT_PROC* glpfGenRenderbuffersEXT = NULL;
PFNGLGENERATEMIPMAPEXT_PROC* glpfGenerateMipmapEXT = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXT_PROC* glpfGetFramebufferAttachmentParameterivEXT = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVEXT_PROC* glpfGetRenderbufferParameterivEXT = NULL;
PFNGLISFRAMEBUFFEREXT_PROC* glpfIsFramebufferEXT = NULL;
PFNGLISRENDERBUFFEREXT_PROC* glpfIsRenderbufferEXT = NULL;
PFNGLRENDERBUFFERSTORAGEEXT_PROC* glpfRenderbufferStorageEXT = NULL;

/* GL_EXT_transform_feedback */

PFNGLBEGINTRANSFORMFEEDBACKEXT_PROC* glpfBeginTransformFeedbackEXT = NULL;
PFNGLBINDBUFFERBASEEXT_PROC* glpfBindBufferBaseEXT = NULL;
PFNGLBINDBUFFEROFFSETEXT_PROC* glpfBindBufferOffsetEXT = NULL;
PFNGLBINDBUFFERRANGEEXT_PROC* glpfBindBufferRangeEXT = NULL;
PFNGLENDTRANSFORMFEEDBACKEXT_PROC* glpfEndTransformFeedbackEXT = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGEXT_PROC* glpfGetTransformFeedbackVaryingEXT = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSEXT_PROC* glpfTransformFeedbackVaryingsEXT = NULL;

/* GL_VERSION_1_2 */

PFNGLCOPYTEXSUBIMAGE3D_PROC* glpfCopyTexSubImage3D = NULL;
PFNGLDRAWRANGEELEMENTS_PROC* glpfDrawRangeElements = NULL;
PFNGLTEXIMAGE3D_PROC* glpfTexImage3D = NULL;
PFNGLTEXSUBIMAGE3D_PROC* glpfTexSubImage3D = NULL;

/* GL_VERSION_1_3 */

PFNGLACTIVETEXTURE_PROC* glpfActiveTexture = NULL;
PFNGLCLIENTACTIVETEXTURE_PROC* glpfClientActiveTexture = NULL;
PFNGLCOMPRESSEDTEXIMAGE1D_PROC* glpfCompressedTexImage1D = NULL;
PFNGLCOMPRESSEDTEXIMAGE2D_PROC* glpfCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE3D_PROC* glpfCompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1D_PROC* glpfCompressedTexSubImage1D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2D_PROC* glpfCompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3D_PROC* glpfCompressedTexSubImage3D = NULL;
PFNGLGETCOMPRESSEDTEXIMAGE_PROC* glpfGetCompressedTexImage = NULL;
PFNGLLOADTRANSPOSEMATRIXD_PROC* glpfLoadTransposeMatrixd = NULL;
PFNGLLOADTRANSPOSEMATRIXF_PROC* glpfLoadTransposeMatrixf = NULL;
PFNGLMULTTRANSPOSEMATRIXD_PROC* glpfMultTransposeMatrixd = NULL;
PFNGLMULTTRANSPOSEMATRIXF_PROC* glpfMultTransposeMatrixf = NULL;
PFNGLMULTITEXCOORD1D_PROC* glpfMultiTexCoord1d = NULL;
PFNGLMULTITEXCOORD1DV_PROC* glpfMultiTexCoord1dv = NULL;
PFNGLMULTITEXCOORD1F_PROC* glpfMultiTexCoord1f = NULL;
PFNGLMULTITEXCOORD1FV_PROC* glpfMultiTexCoord1fv = NULL;
PFNGLMULTITEXCOORD1I_PROC* glpfMultiTexCoord1i = NULL;
PFNGLMULTITEXCOORD1IV_PROC* glpfMultiTexCoord1iv = NULL;
PFNGLMULTITEXCOORD1S_PROC* glpfMultiTexCoord1s = NULL;
PFNGLMULTITEXCOORD1SV_PROC* glpfMultiTexCoord1sv = NULL;
PFNGLMULTITEXCOORD2D_PROC* glpfMultiTexCoord2d = NULL;
PFNGLMULTITEXCOORD2DV_PROC* glpfMultiTexCoord2dv = NULL;
PFNGLMULTITEXCOORD2F_PROC* glpfMultiTexCoord2f = NULL;
PFNGLMULTITEXCOORD2FV_PROC* glpfMultiTexCoord2fv = NULL;
PFNGLMULTITEXCOORD2I_PROC* glpfMultiTexCoord2i = NULL;
PFNGLMULTITEXCOORD2IV_PROC* glpfMultiTexCoord2iv = NULL;
PFNGLMULTITEXCOORD2S_PROC* glpfMultiTexCoord2s = NULL;
PFNGLMULTITEXCOORD2SV_PROC* glpfMultiTexCoord2sv = NULL;
PFNGLMULTITEXCOORD3D_PROC* glpfMultiTexCoord3d = NULL;
PFNGLMULTITEXCOORD3DV_PROC* glpfMultiTexCoord3dv = NULL;
PFNGLMULTITEXCOORD3F_PROC* glpfMultiTexCoord3f = NULL;
PFNGLMULTITEXCOORD3FV_PROC* glpfMultiTexCoord3fv = NULL;
PFNGLMULTITEXCOORD3I_PROC* glpfMultiTexCoord3i = NULL;
PFNGLMULTITEXCOORD3IV_PROC* glpfMultiTexCoord3iv = NULL;
PFNGLMULTITEXCOORD3S_PROC* glpfMultiTexCoord3s = NULL;
PFNGLMULTITEXCOORD3SV_PROC* glpfMultiTexCoord3sv = NULL;
PFNGLMULTITEXCOORD4D_PROC* glpfMultiTexCoord4d = NULL;
PFNGLMULTITEXCOORD4DV_PROC* glpfMultiTexCoord4dv = NULL;
PFNGLMULTITEXCOORD4F_PROC* glpfMultiTexCoord4f = NULL;
PFNGLMULTITEXCOORD4FV_PROC* glpfMultiTexCoord4fv = NULL;
PFNGLMULTITEXCOORD4I_PROC* glpfMultiTexCoord4i = NULL;
PFNGLMULTITEXCOORD4IV_PROC* glpfMultiTexCoord4iv = NULL;
PFNGLMULTITEXCOORD4S_PROC* glpfMultiTexCoord4s = NULL;
PFNGLMULTITEXCOORD4SV_PROC* glpfMultiTexCoord4sv = NULL;
PFNGLSAMPLECOVERAGE_PROC* glpfSampleCoverage = NULL;

/* GL_VERSION_1_4 */

PFNGLBLENDCOLOR_PROC* glpfBlendColor = NULL;
PFNGLBLENDEQUATION_PROC* glpfBlendEquation = NULL;
PFNGLBLENDFUNCSEPARATE_PROC* glpfBlendFuncSeparate = NULL;
PFNGLFOGCOORDPOINTER_PROC* glpfFogCoordPointer = NULL;
PFNGLFOGCOORDD_PROC* glpfFogCoordd = NULL;
PFNGLFOGCOORDDV_PROC* glpfFogCoorddv = NULL;
PFNGLFOGCOORDF_PROC* glpfFogCoordf = NULL;
PFNGLFOGCOORDFV_PROC* glpfFogCoordfv = NULL;
PFNGLMULTIDRAWARRAYS_PROC* glpfMultiDrawArrays = NULL;
PFNGLMULTIDRAWELEMENTS_PROC* glpfMultiDrawElements = NULL;
PFNGLPOINTPARAMETERF_PROC* glpfPointParameterf = NULL;
PFNGLPOINTPARAMETERFV_PROC* glpfPointParameterfv = NULL;
PFNGLPOINTPARAMETERI_PROC* glpfPointParameteri = NULL;
PFNGLPOINTPARAMETERIV_PROC* glpfPointParameteriv = NULL;
PFNGLSECONDARYCOLOR3B_PROC* glpfSecondaryColor3b = NULL;
PFNGLSECONDARYCOLOR3BV_PROC* glpfSecondaryColor3bv = NULL;
PFNGLSECONDARYCOLOR3D_PROC* glpfSecondaryColor3d = NULL;
PFNGLSECONDARYCOLOR3DV_PROC* glpfSecondaryColor3dv = NULL;
PFNGLSECONDARYCOLOR3F_PROC* glpfSecondaryColor3f = NULL;
PFNGLSECONDARYCOLOR3FV_PROC* glpfSecondaryColor3fv = NULL;
PFNGLSECONDARYCOLOR3I_PROC* glpfSecondaryColor3i = NULL;
PFNGLSECONDARYCOLOR3IV_PROC* glpfSecondaryColor3iv = NULL;
PFNGLSECONDARYCOLOR3S_PROC* glpfSecondaryColor3s = NULL;
PFNGLSECONDARYCOLOR3SV_PROC* glpfSecondaryColor3sv = NULL;
PFNGLSECONDARYCOLOR3UB_PROC* glpfSecondaryColor3ub = NULL;
PFNGLSECONDARYCOLOR3UBV_PROC* glpfSecondaryColor3ubv = NULL;
PFNGLSECONDARYCOLOR3UI_PROC* glpfSecondaryColor3ui = NULL;
PFNGLSECONDARYCOLOR3UIV_PROC* glpfSecondaryColor3uiv = NULL;
PFNGLSECONDARYCOLOR3US_PROC* glpfSecondaryColor3us = NULL;
PFNGLSECONDARYCOLOR3USV_PROC* glpfSecondaryColor3usv = NULL;
PFNGLSECONDARYCOLORPOINTER_PROC* glpfSecondaryColorPointer = NULL;
PFNGLWINDOWPOS2D_PROC* glpfWindowPos2d = NULL;
PFNGLWINDOWPOS2DV_PROC* glpfWindowPos2dv = NULL;
PFNGLWINDOWPOS2F_PROC* glpfWindowPos2f = NULL;
PFNGLWINDOWPOS2FV_PROC* glpfWindowPos2fv = NULL;
PFNGLWINDOWPOS2I_PROC* glpfWindowPos2i = NULL;
PFNGLWINDOWPOS2IV_PROC* glpfWindowPos2iv = NULL;
PFNGLWINDOWPOS2S_PROC* glpfWindowPos2s = NULL;
PFNGLWINDOWPOS2SV_PROC* glpfWindowPos2sv = NULL;
PFNGLWINDOWPOS3D_PROC* glpfWindowPos3d = NULL;
PFNGLWINDOWPOS3DV_PROC* glpfWindowPos3dv = NULL;
PFNGLWINDOWPOS3F_PROC* glpfWindowPos3f = NULL;
PFNGLWINDOWPOS3FV_PROC* glpfWindowPos3fv = NULL;
PFNGLWINDOWPOS3I_PROC* glpfWindowPos3i = NULL;
PFNGLWINDOWPOS3IV_PROC* glpfWindowPos3iv = NULL;
PFNGLWINDOWPOS3S_PROC* glpfWindowPos3s = NULL;
PFNGLWINDOWPOS3SV_PROC* glpfWindowPos3sv = NULL;

/* GL_VERSION_1_5 */

PFNGLBEGINQUERY_PROC* glpfBeginQuery = NULL;
PFNGLBINDBUFFER_PROC* glpfBindBuffer = NULL;
PFNGLBUFFERDATA_PROC* glpfBufferData = NULL;
PFNGLBUFFERSUBDATA_PROC* glpfBufferSubData = NULL;
PFNGLDELETEBUFFERS_PROC* glpfDeleteBuffers = NULL;
PFNGLDELETEQUERIES_PROC* glpfDeleteQueries = NULL;
PFNGLENDQUERY_PROC* glpfEndQuery = NULL;
PFNGLGENBUFFERS_PROC* glpfGenBuffers = NULL;
PFNGLGENQUERIES_PROC* glpfGenQueries = NULL;
PFNGLGETBUFFERPARAMETERIV_PROC* glpfGetBufferParameteriv = NULL;
PFNGLGETBUFFERPOINTERV_PROC* glpfGetBufferPointerv = NULL;
PFNGLGETBUFFERSUBDATA_PROC* glpfGetBufferSubData = NULL;
PFNGLGETQUERYOBJECTIV_PROC* glpfGetQueryObjectiv = NULL;
PFNGLGETQUERYOBJECTUIV_PROC* glpfGetQueryObjectuiv = NULL;
PFNGLGETQUERYIV_PROC* glpfGetQueryiv = NULL;
PFNGLISBUFFER_PROC* glpfIsBuffer = NULL;
PFNGLISQUERY_PROC* glpfIsQuery = NULL;
PFNGLMAPBUFFER_PROC* glpfMapBuffer = NULL;
PFNGLUNMAPBUFFER_PROC* glpfUnmapBuffer = NULL;

/* GL_VERSION_2_0 */

PFNGLATTACHSHADER_PROC* glpfAttachShader = NULL;
PFNGLBINDATTRIBLOCATION_PROC* glpfBindAttribLocation = NULL;
PFNGLBLENDEQUATIONSEPARATE_PROC* glpfBlendEquationSeparate = NULL;
PFNGLCOMPILESHADER_PROC* glpfCompileShader = NULL;
PFNGLCREATEPROGRAM_PROC* glpfCreateProgram = NULL;
PFNGLCREATESHADER_PROC* glpfCreateShader = NULL;
PFNGLDELETEPROGRAM_PROC* glpfDeleteProgram = NULL;
PFNGLDELETESHADER_PROC* glpfDeleteShader = NULL;
PFNGLDETACHSHADER_PROC* glpfDetachShader = NULL;
PFNGLDISABLEVERTEXATTRIBARRAY_PROC* glpfDisableVertexAttribArray = NULL;
PFNGLDRAWBUFFERS_PROC* glpfDrawBuffers = NULL;
PFNGLENABLEVERTEXATTRIBARRAY_PROC* glpfEnableVertexAttribArray = NULL;
PFNGLGETACTIVEATTRIB_PROC* glpfGetActiveAttrib = NULL;
PFNGLGETACTIVEUNIFORM_PROC* glpfGetActiveUniform = NULL;
PFNGLGETATTACHEDSHADERS_PROC* glpfGetAttachedShaders = NULL;
PFNGLGETATTRIBLOCATION_PROC* glpfGetAttribLocation = NULL;
PFNGLGETPROGRAMINFOLOG_PROC* glpfGetProgramInfoLog = NULL;
PFNGLGETPROGRAMIV_PROC* glpfGetProgramiv = NULL;
PFNGLGETSHADERINFOLOG_PROC* glpfGetShaderInfoLog = NULL;
PFNGLGETSHADERSOURCE_PROC* glpfGetShaderSource = NULL;
PFNGLGETSHADERIV_PROC* glpfGetShaderiv = NULL;
PFNGLGETUNIFORMLOCATION_PROC* glpfGetUniformLocation = NULL;
PFNGLGETUNIFORMFV_PROC* glpfGetUniformfv = NULL;
PFNGLGETUNIFORMIV_PROC* glpfGetUniformiv = NULL;
PFNGLGETVERTEXATTRIBPOINTERV_PROC* glpfGetVertexAttribPointerv = NULL;
PFNGLGETVERTEXATTRIBDV_PROC* glpfGetVertexAttribdv = NULL;
PFNGLGETVERTEXATTRIBFV_PROC* glpfGetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBIV_PROC* glpfGetVertexAttribiv = NULL;
PFNGLISPROGRAM_PROC* glpfIsProgram = NULL;
PFNGLISSHADER_PROC* glpfIsShader = NULL;
PFNGLLINKPROGRAM_PROC* glpfLinkProgram = NULL;
PFNGLSHADERSOURCE_PROC* glpfShaderSource = NULL;
PFNGLSTENCILFUNCSEPARATE_PROC* glpfStencilFuncSeparate = NULL;
PFNGLSTENCILMASKSEPARATE_PROC* glpfStencilMaskSeparate = NULL;
PFNGLSTENCILOPSEPARATE_PROC* glpfStencilOpSeparate = NULL;
PFNGLUNIFORM1F_PROC* glpfUniform1f = NULL;
PFNGLUNIFORM1FV_PROC* glpfUniform1fv = NULL;
PFNGLUNIFORM1I_PROC* glpfUniform1i = NULL;
PFNGLUNIFORM1IV_PROC* glpfUniform1iv = NULL;
PFNGLUNIFORM2F_PROC* glpfUniform2f = NULL;
PFNGLUNIFORM2FV_PROC* glpfUniform2fv = NULL;
PFNGLUNIFORM2I_PROC* glpfUniform2i = NULL;
PFNGLUNIFORM2IV_PROC* glpfUniform2iv = NULL;
PFNGLUNIFORM3F_PROC* glpfUniform3f = NULL;
PFNGLUNIFORM3FV_PROC* glpfUniform3fv = NULL;
PFNGLUNIFORM3I_PROC* glpfUniform3i = NULL;
PFNGLUNIFORM3IV_PROC* glpfUniform3iv = NULL;
PFNGLUNIFORM4F_PROC* glpfUniform4f = NULL;
PFNGLUNIFORM4FV_PROC* glpfUniform4fv = NULL;
PFNGLUNIFORM4I_PROC* glpfUniform4i = NULL;
PFNGLUNIFORM4IV_PROC* glpfUniform4iv = NULL;
PFNGLUNIFORMMATRIX2FV_PROC* glpfUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX3FV_PROC* glpfUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX4FV_PROC* glpfUniformMatrix4fv = NULL;
PFNGLUSEPROGRAM_PROC* glpfUseProgram = NULL;
PFNGLVALIDATEPROGRAM_PROC* glpfValidateProgram = NULL;
PFNGLVERTEXATTRIB1D_PROC* glpfVertexAttrib1d = NULL;
PFNGLVERTEXATTRIB1DV_PROC* glpfVertexAttrib1dv = NULL;
PFNGLVERTEXATTRIB1F_PROC* glpfVertexAttrib1f = NULL;
PFNGLVERTEXATTRIB1FV_PROC* glpfVertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB1S_PROC* glpfVertexAttrib1s = NULL;
PFNGLVERTEXATTRIB1SV_PROC* glpfVertexAttrib1sv = NULL;
PFNGLVERTEXATTRIB2D_PROC* glpfVertexAttrib2d = NULL;
PFNGLVERTEXATTRIB2DV_PROC* glpfVertexAttrib2dv = NULL;
PFNGLVERTEXATTRIB2F_PROC* glpfVertexAttrib2f = NULL;
PFNGLVERTEXATTRIB2FV_PROC* glpfVertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB2S_PROC* glpfVertexAttrib2s = NULL;
PFNGLVERTEXATTRIB2SV_PROC* glpfVertexAttrib2sv = NULL;
PFNGLVERTEXATTRIB3D_PROC* glpfVertexAttrib3d = NULL;
PFNGLVERTEXATTRIB3DV_PROC* glpfVertexAttrib3dv = NULL;
PFNGLVERTEXATTRIB3F_PROC* glpfVertexAttrib3f = NULL;
PFNGLVERTEXATTRIB3FV_PROC* glpfVertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB3S_PROC* glpfVertexAttrib3s = NULL;
PFNGLVERTEXATTRIB3SV_PROC* glpfVertexAttrib3sv = NULL;
PFNGLVERTEXATTRIB4NBV_PROC* glpfVertexAttrib4Nbv = NULL;
PFNGLVERTEXATTRIB4NIV_PROC* glpfVertexAttrib4Niv = NULL;
PFNGLVERTEXATTRIB4NSV_PROC* glpfVertexAttrib4Nsv = NULL;
PFNGLVERTEXATTRIB4NUB_PROC* glpfVertexAttrib4Nub = NULL;
PFNGLVERTEXATTRIB4NUBV_PROC* glpfVertexAttrib4Nubv = NULL;
PFNGLVERTEXATTRIB4NUIV_PROC* glpfVertexAttrib4Nuiv = NULL;
PFNGLVERTEXATTRIB4NUSV_PROC* glpfVertexAttrib4Nusv = NULL;
PFNGLVERTEXATTRIB4BV_PROC* glpfVertexAttrib4bv = NULL;
PFNGLVERTEXATTRIB4D_PROC* glpfVertexAttrib4d = NULL;
PFNGLVERTEXATTRIB4DV_PROC* glpfVertexAttrib4dv = NULL;
PFNGLVERTEXATTRIB4F_PROC* glpfVertexAttrib4f = NULL;
PFNGLVERTEXATTRIB4FV_PROC* glpfVertexAttrib4fv = NULL;
PFNGLVERTEXATTRIB4IV_PROC* glpfVertexAttrib4iv = NULL;
PFNGLVERTEXATTRIB4S_PROC* glpfVertexAttrib4s = NULL;
PFNGLVERTEXATTRIB4SV_PROC* glpfVertexAttrib4sv = NULL;
PFNGLVERTEXATTRIB4UBV_PROC* glpfVertexAttrib4ubv = NULL;
PFNGLVERTEXATTRIB4UIV_PROC* glpfVertexAttrib4uiv = NULL;
PFNGLVERTEXATTRIB4USV_PROC* glpfVertexAttrib4usv = NULL;
PFNGLVERTEXATTRIBPOINTER_PROC* glpfVertexAttribPointer = NULL;



#ifdef __cplusplus
}
#endif
