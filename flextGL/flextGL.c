/* WARNING: This file was automatically generated */
/* Do not edit. */

#include "flextGL.h"
#include "GL/glfw.h"

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif


void flextLoadOpenGLFunctions(void);

int flextInit(void)
{
  
    int major = glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR);
    int minor = glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR);

    flextLoadOpenGLFunctions();
    
    /* --- Check for minimal version and profile --- */

    if (major * 10 + minor < 21) {
	fprintf(stderr, "Error: OpenGL version 2.1 not supported.\n");
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

    if (glfwExtensionSupported("GL_EXT_geometry_shader4")) {
        FLEXT_EXT_geometry_shader4 = GL_TRUE;
    }

    if (glfwExtensionSupported("GL_NV_transform_feedback")) {
        FLEXT_NV_transform_feedback = GL_TRUE;
    }


    return GL_TRUE;
}



void flextLoadOpenGLFunctions(void)
{
    /* --- Function pointer loading --- */


    /* GL_EXT_framebuffer_object */

    glpfIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXT_PROC*)glfwGetProcAddress("glIsRenderbufferEXT");
    glpfBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXT_PROC*)glfwGetProcAddress("glBindRenderbufferEXT");
    glpfDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXT_PROC*)glfwGetProcAddress("glDeleteRenderbuffersEXT");
    glpfGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXT_PROC*)glfwGetProcAddress("glGenRenderbuffersEXT");
    glpfRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXT_PROC*)glfwGetProcAddress("glRenderbufferStorageEXT");
    glpfGetRenderbufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXT_PROC*)glfwGetProcAddress("glGetRenderbufferParameterivEXT");
    glpfIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXT_PROC*)glfwGetProcAddress("glIsFramebufferEXT");
    glpfBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXT_PROC*)glfwGetProcAddress("glBindFramebufferEXT");
    glpfDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXT_PROC*)glfwGetProcAddress("glDeleteFramebuffersEXT");
    glpfGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXT_PROC*)glfwGetProcAddress("glGenFramebuffersEXT");
    glpfCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXT_PROC*)glfwGetProcAddress("glCheckFramebufferStatusEXT");
    glpfFramebufferTexture1DEXT = (PFNGLFRAMEBUFFERTEXTURE1DEXT_PROC*)glfwGetProcAddress("glFramebufferTexture1DEXT");
    glpfFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXT_PROC*)glfwGetProcAddress("glFramebufferTexture2DEXT");
    glpfFramebufferTexture3DEXT = (PFNGLFRAMEBUFFERTEXTURE3DEXT_PROC*)glfwGetProcAddress("glFramebufferTexture3DEXT");
    glpfFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXT_PROC*)glfwGetProcAddress("glFramebufferRenderbufferEXT");
    glpfGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXT_PROC*)glfwGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
    glpfGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXT_PROC*)glfwGetProcAddress("glGenerateMipmapEXT");


    /* GL_EXT_geometry_shader4 */

    glpfProgramParameteriEXT = (PFNGLPROGRAMPARAMETERIEXT_PROC*)glfwGetProcAddress("glProgramParameteriEXT");


    /* GL_NV_transform_feedback */

    glpfBeginTransformFeedbackNV = (PFNGLBEGINTRANSFORMFEEDBACKNV_PROC*)glfwGetProcAddress("glBeginTransformFeedbackNV");
    glpfEndTransformFeedbackNV = (PFNGLENDTRANSFORMFEEDBACKNV_PROC*)glfwGetProcAddress("glEndTransformFeedbackNV");
    glpfTransformFeedbackAttribsNV = (PFNGLTRANSFORMFEEDBACKATTRIBSNV_PROC*)glfwGetProcAddress("glTransformFeedbackAttribsNV");
    glpfBindBufferRangeNV = (PFNGLBINDBUFFERRANGENV_PROC*)glfwGetProcAddress("glBindBufferRangeNV");
    glpfBindBufferOffsetNV = (PFNGLBINDBUFFEROFFSETNV_PROC*)glfwGetProcAddress("glBindBufferOffsetNV");
    glpfBindBufferBaseNV = (PFNGLBINDBUFFERBASENV_PROC*)glfwGetProcAddress("glBindBufferBaseNV");
    glpfTransformFeedbackVaryingsNV = (PFNGLTRANSFORMFEEDBACKVARYINGSNV_PROC*)glfwGetProcAddress("glTransformFeedbackVaryingsNV");
    glpfActiveVaryingNV = (PFNGLACTIVEVARYINGNV_PROC*)glfwGetProcAddress("glActiveVaryingNV");
    glpfGetVaryingLocationNV = (PFNGLGETVARYINGLOCATIONNV_PROC*)glfwGetProcAddress("glGetVaryingLocationNV");
    glpfGetActiveVaryingNV = (PFNGLGETACTIVEVARYINGNV_PROC*)glfwGetProcAddress("glGetActiveVaryingNV");
    glpfGetTransformFeedbackVaryingNV = (PFNGLGETTRANSFORMFEEDBACKVARYINGNV_PROC*)glfwGetProcAddress("glGetTransformFeedbackVaryingNV");
    glpfTransformFeedbackStreamAttribsNV = (PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNV_PROC*)glfwGetProcAddress("glTransformFeedbackStreamAttribsNV");


    /* GL_VERSION_1_2 */

    glpfBlendColor = (PFNGLBLENDCOLOR_PROC*)glfwGetProcAddress("glBlendColor");
    glpfBlendEquation = (PFNGLBLENDEQUATION_PROC*)glfwGetProcAddress("glBlendEquation");
    glpfDrawRangeElements = (PFNGLDRAWRANGEELEMENTS_PROC*)glfwGetProcAddress("glDrawRangeElements");
    glpfTexImage3D = (PFNGLTEXIMAGE3D_PROC*)glfwGetProcAddress("glTexImage3D");
    glpfTexSubImage3D = (PFNGLTEXSUBIMAGE3D_PROC*)glfwGetProcAddress("glTexSubImage3D");
    glpfCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3D_PROC*)glfwGetProcAddress("glCopyTexSubImage3D");
    glpfColorTable = (PFNGLCOLORTABLE_PROC*)glfwGetProcAddress("glColorTable");
    glpfColorTableParameterfv = (PFNGLCOLORTABLEPARAMETERFV_PROC*)glfwGetProcAddress("glColorTableParameterfv");
    glpfColorTableParameteriv = (PFNGLCOLORTABLEPARAMETERIV_PROC*)glfwGetProcAddress("glColorTableParameteriv");
    glpfCopyColorTable = (PFNGLCOPYCOLORTABLE_PROC*)glfwGetProcAddress("glCopyColorTable");
    glpfGetColorTable = (PFNGLGETCOLORTABLE_PROC*)glfwGetProcAddress("glGetColorTable");
    glpfGetColorTableParameterfv = (PFNGLGETCOLORTABLEPARAMETERFV_PROC*)glfwGetProcAddress("glGetColorTableParameterfv");
    glpfGetColorTableParameteriv = (PFNGLGETCOLORTABLEPARAMETERIV_PROC*)glfwGetProcAddress("glGetColorTableParameteriv");
    glpfColorSubTable = (PFNGLCOLORSUBTABLE_PROC*)glfwGetProcAddress("glColorSubTable");
    glpfCopyColorSubTable = (PFNGLCOPYCOLORSUBTABLE_PROC*)glfwGetProcAddress("glCopyColorSubTable");
    glpfConvolutionFilter1D = (PFNGLCONVOLUTIONFILTER1D_PROC*)glfwGetProcAddress("glConvolutionFilter1D");
    glpfConvolutionFilter2D = (PFNGLCONVOLUTIONFILTER2D_PROC*)glfwGetProcAddress("glConvolutionFilter2D");
    glpfConvolutionParameterf = (PFNGLCONVOLUTIONPARAMETERF_PROC*)glfwGetProcAddress("glConvolutionParameterf");
    glpfConvolutionParameterfv = (PFNGLCONVOLUTIONPARAMETERFV_PROC*)glfwGetProcAddress("glConvolutionParameterfv");
    glpfConvolutionParameteri = (PFNGLCONVOLUTIONPARAMETERI_PROC*)glfwGetProcAddress("glConvolutionParameteri");
    glpfConvolutionParameteriv = (PFNGLCONVOLUTIONPARAMETERIV_PROC*)glfwGetProcAddress("glConvolutionParameteriv");
    glpfCopyConvolutionFilter1D = (PFNGLCOPYCONVOLUTIONFILTER1D_PROC*)glfwGetProcAddress("glCopyConvolutionFilter1D");
    glpfCopyConvolutionFilter2D = (PFNGLCOPYCONVOLUTIONFILTER2D_PROC*)glfwGetProcAddress("glCopyConvolutionFilter2D");
    glpfGetConvolutionFilter = (PFNGLGETCONVOLUTIONFILTER_PROC*)glfwGetProcAddress("glGetConvolutionFilter");
    glpfGetConvolutionParameterfv = (PFNGLGETCONVOLUTIONPARAMETERFV_PROC*)glfwGetProcAddress("glGetConvolutionParameterfv");
    glpfGetConvolutionParameteriv = (PFNGLGETCONVOLUTIONPARAMETERIV_PROC*)glfwGetProcAddress("glGetConvolutionParameteriv");
    glpfGetSeparableFilter = (PFNGLGETSEPARABLEFILTER_PROC*)glfwGetProcAddress("glGetSeparableFilter");
    glpfSeparableFilter2D = (PFNGLSEPARABLEFILTER2D_PROC*)glfwGetProcAddress("glSeparableFilter2D");
    glpfGetHistogram = (PFNGLGETHISTOGRAM_PROC*)glfwGetProcAddress("glGetHistogram");
    glpfGetHistogramParameterfv = (PFNGLGETHISTOGRAMPARAMETERFV_PROC*)glfwGetProcAddress("glGetHistogramParameterfv");
    glpfGetHistogramParameteriv = (PFNGLGETHISTOGRAMPARAMETERIV_PROC*)glfwGetProcAddress("glGetHistogramParameteriv");
    glpfGetMinmax = (PFNGLGETMINMAX_PROC*)glfwGetProcAddress("glGetMinmax");
    glpfGetMinmaxParameterfv = (PFNGLGETMINMAXPARAMETERFV_PROC*)glfwGetProcAddress("glGetMinmaxParameterfv");
    glpfGetMinmaxParameteriv = (PFNGLGETMINMAXPARAMETERIV_PROC*)glfwGetProcAddress("glGetMinmaxParameteriv");
    glpfHistogram = (PFNGLHISTOGRAM_PROC*)glfwGetProcAddress("glHistogram");
    glpfMinmax = (PFNGLMINMAX_PROC*)glfwGetProcAddress("glMinmax");
    glpfResetHistogram = (PFNGLRESETHISTOGRAM_PROC*)glfwGetProcAddress("glResetHistogram");
    glpfResetMinmax = (PFNGLRESETMINMAX_PROC*)glfwGetProcAddress("glResetMinmax");


    /* GL_VERSION_1_3 */

    glpfActiveTexture = (PFNGLACTIVETEXTURE_PROC*)glfwGetProcAddress("glActiveTexture");
    glpfSampleCoverage = (PFNGLSAMPLECOVERAGE_PROC*)glfwGetProcAddress("glSampleCoverage");
    glpfCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3D_PROC*)glfwGetProcAddress("glCompressedTexImage3D");
    glpfCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2D_PROC*)glfwGetProcAddress("glCompressedTexImage2D");
    glpfCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1D_PROC*)glfwGetProcAddress("glCompressedTexImage1D");
    glpfCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3D_PROC*)glfwGetProcAddress("glCompressedTexSubImage3D");
    glpfCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2D_PROC*)glfwGetProcAddress("glCompressedTexSubImage2D");
    glpfCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1D_PROC*)glfwGetProcAddress("glCompressedTexSubImage1D");
    glpfGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGE_PROC*)glfwGetProcAddress("glGetCompressedTexImage");
    glpfClientActiveTexture = (PFNGLCLIENTACTIVETEXTURE_PROC*)glfwGetProcAddress("glClientActiveTexture");
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
    glpfLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXF_PROC*)glfwGetProcAddress("glLoadTransposeMatrixf");
    glpfLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXD_PROC*)glfwGetProcAddress("glLoadTransposeMatrixd");
    glpfMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXF_PROC*)glfwGetProcAddress("glMultTransposeMatrixf");
    glpfMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXD_PROC*)glfwGetProcAddress("glMultTransposeMatrixd");


    /* GL_VERSION_1_4 */

    glpfBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATE_PROC*)glfwGetProcAddress("glBlendFuncSeparate");
    glpfMultiDrawArrays = (PFNGLMULTIDRAWARRAYS_PROC*)glfwGetProcAddress("glMultiDrawArrays");
    glpfMultiDrawElements = (PFNGLMULTIDRAWELEMENTS_PROC*)glfwGetProcAddress("glMultiDrawElements");
    glpfPointParameterf = (PFNGLPOINTPARAMETERF_PROC*)glfwGetProcAddress("glPointParameterf");
    glpfPointParameterfv = (PFNGLPOINTPARAMETERFV_PROC*)glfwGetProcAddress("glPointParameterfv");
    glpfPointParameteri = (PFNGLPOINTPARAMETERI_PROC*)glfwGetProcAddress("glPointParameteri");
    glpfPointParameteriv = (PFNGLPOINTPARAMETERIV_PROC*)glfwGetProcAddress("glPointParameteriv");
    glpfFogCoordf = (PFNGLFOGCOORDF_PROC*)glfwGetProcAddress("glFogCoordf");
    glpfFogCoordfv = (PFNGLFOGCOORDFV_PROC*)glfwGetProcAddress("glFogCoordfv");
    glpfFogCoordd = (PFNGLFOGCOORDD_PROC*)glfwGetProcAddress("glFogCoordd");
    glpfFogCoorddv = (PFNGLFOGCOORDDV_PROC*)glfwGetProcAddress("glFogCoorddv");
    glpfFogCoordPointer = (PFNGLFOGCOORDPOINTER_PROC*)glfwGetProcAddress("glFogCoordPointer");
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

    glpfGenQueries = (PFNGLGENQUERIES_PROC*)glfwGetProcAddress("glGenQueries");
    glpfDeleteQueries = (PFNGLDELETEQUERIES_PROC*)glfwGetProcAddress("glDeleteQueries");
    glpfIsQuery = (PFNGLISQUERY_PROC*)glfwGetProcAddress("glIsQuery");
    glpfBeginQuery = (PFNGLBEGINQUERY_PROC*)glfwGetProcAddress("glBeginQuery");
    glpfEndQuery = (PFNGLENDQUERY_PROC*)glfwGetProcAddress("glEndQuery");
    glpfGetQueryiv = (PFNGLGETQUERYIV_PROC*)glfwGetProcAddress("glGetQueryiv");
    glpfGetQueryObjectiv = (PFNGLGETQUERYOBJECTIV_PROC*)glfwGetProcAddress("glGetQueryObjectiv");
    glpfGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIV_PROC*)glfwGetProcAddress("glGetQueryObjectuiv");
    glpfBindBuffer = (PFNGLBINDBUFFER_PROC*)glfwGetProcAddress("glBindBuffer");
    glpfDeleteBuffers = (PFNGLDELETEBUFFERS_PROC*)glfwGetProcAddress("glDeleteBuffers");
    glpfGenBuffers = (PFNGLGENBUFFERS_PROC*)glfwGetProcAddress("glGenBuffers");
    glpfIsBuffer = (PFNGLISBUFFER_PROC*)glfwGetProcAddress("glIsBuffer");
    glpfBufferData = (PFNGLBUFFERDATA_PROC*)glfwGetProcAddress("glBufferData");
    glpfBufferSubData = (PFNGLBUFFERSUBDATA_PROC*)glfwGetProcAddress("glBufferSubData");
    glpfGetBufferSubData = (PFNGLGETBUFFERSUBDATA_PROC*)glfwGetProcAddress("glGetBufferSubData");
    glpfMapBuffer = (PFNGLMAPBUFFER_PROC*)glfwGetProcAddress("glMapBuffer");
    glpfUnmapBuffer = (PFNGLUNMAPBUFFER_PROC*)glfwGetProcAddress("glUnmapBuffer");
    glpfGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIV_PROC*)glfwGetProcAddress("glGetBufferParameteriv");
    glpfGetBufferPointerv = (PFNGLGETBUFFERPOINTERV_PROC*)glfwGetProcAddress("glGetBufferPointerv");


    /* GL_VERSION_2_0 */

    glpfBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATE_PROC*)glfwGetProcAddress("glBlendEquationSeparate");
    glpfDrawBuffers = (PFNGLDRAWBUFFERS_PROC*)glfwGetProcAddress("glDrawBuffers");
    glpfStencilOpSeparate = (PFNGLSTENCILOPSEPARATE_PROC*)glfwGetProcAddress("glStencilOpSeparate");
    glpfStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATE_PROC*)glfwGetProcAddress("glStencilFuncSeparate");
    glpfStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATE_PROC*)glfwGetProcAddress("glStencilMaskSeparate");
    glpfAttachShader = (PFNGLATTACHSHADER_PROC*)glfwGetProcAddress("glAttachShader");
    glpfBindAttribLocation = (PFNGLBINDATTRIBLOCATION_PROC*)glfwGetProcAddress("glBindAttribLocation");
    glpfCompileShader = (PFNGLCOMPILESHADER_PROC*)glfwGetProcAddress("glCompileShader");
    glpfCreateProgram = (PFNGLCREATEPROGRAM_PROC*)glfwGetProcAddress("glCreateProgram");
    glpfCreateShader = (PFNGLCREATESHADER_PROC*)glfwGetProcAddress("glCreateShader");
    glpfDeleteProgram = (PFNGLDELETEPROGRAM_PROC*)glfwGetProcAddress("glDeleteProgram");
    glpfDeleteShader = (PFNGLDELETESHADER_PROC*)glfwGetProcAddress("glDeleteShader");
    glpfDetachShader = (PFNGLDETACHSHADER_PROC*)glfwGetProcAddress("glDetachShader");
    glpfDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAY_PROC*)glfwGetProcAddress("glDisableVertexAttribArray");
    glpfEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAY_PROC*)glfwGetProcAddress("glEnableVertexAttribArray");
    glpfGetActiveAttrib = (PFNGLGETACTIVEATTRIB_PROC*)glfwGetProcAddress("glGetActiveAttrib");
    glpfGetActiveUniform = (PFNGLGETACTIVEUNIFORM_PROC*)glfwGetProcAddress("glGetActiveUniform");
    glpfGetAttachedShaders = (PFNGLGETATTACHEDSHADERS_PROC*)glfwGetProcAddress("glGetAttachedShaders");
    glpfGetAttribLocation = (PFNGLGETATTRIBLOCATION_PROC*)glfwGetProcAddress("glGetAttribLocation");
    glpfGetProgramiv = (PFNGLGETPROGRAMIV_PROC*)glfwGetProcAddress("glGetProgramiv");
    glpfGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOG_PROC*)glfwGetProcAddress("glGetProgramInfoLog");
    glpfGetShaderiv = (PFNGLGETSHADERIV_PROC*)glfwGetProcAddress("glGetShaderiv");
    glpfGetShaderInfoLog = (PFNGLGETSHADERINFOLOG_PROC*)glfwGetProcAddress("glGetShaderInfoLog");
    glpfGetShaderSource = (PFNGLGETSHADERSOURCE_PROC*)glfwGetProcAddress("glGetShaderSource");
    glpfGetUniformLocation = (PFNGLGETUNIFORMLOCATION_PROC*)glfwGetProcAddress("glGetUniformLocation");
    glpfGetUniformfv = (PFNGLGETUNIFORMFV_PROC*)glfwGetProcAddress("glGetUniformfv");
    glpfGetUniformiv = (PFNGLGETUNIFORMIV_PROC*)glfwGetProcAddress("glGetUniformiv");
    glpfGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDV_PROC*)glfwGetProcAddress("glGetVertexAttribdv");
    glpfGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFV_PROC*)glfwGetProcAddress("glGetVertexAttribfv");
    glpfGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIV_PROC*)glfwGetProcAddress("glGetVertexAttribiv");
    glpfGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERV_PROC*)glfwGetProcAddress("glGetVertexAttribPointerv");
    glpfIsProgram = (PFNGLISPROGRAM_PROC*)glfwGetProcAddress("glIsProgram");
    glpfIsShader = (PFNGLISSHADER_PROC*)glfwGetProcAddress("glIsShader");
    glpfLinkProgram = (PFNGLLINKPROGRAM_PROC*)glfwGetProcAddress("glLinkProgram");
    glpfShaderSource = (PFNGLSHADERSOURCE_PROC*)glfwGetProcAddress("glShaderSource");
    glpfUseProgram = (PFNGLUSEPROGRAM_PROC*)glfwGetProcAddress("glUseProgram");
    glpfUniform1f = (PFNGLUNIFORM1F_PROC*)glfwGetProcAddress("glUniform1f");
    glpfUniform2f = (PFNGLUNIFORM2F_PROC*)glfwGetProcAddress("glUniform2f");
    glpfUniform3f = (PFNGLUNIFORM3F_PROC*)glfwGetProcAddress("glUniform3f");
    glpfUniform4f = (PFNGLUNIFORM4F_PROC*)glfwGetProcAddress("glUniform4f");
    glpfUniform1i = (PFNGLUNIFORM1I_PROC*)glfwGetProcAddress("glUniform1i");
    glpfUniform2i = (PFNGLUNIFORM2I_PROC*)glfwGetProcAddress("glUniform2i");
    glpfUniform3i = (PFNGLUNIFORM3I_PROC*)glfwGetProcAddress("glUniform3i");
    glpfUniform4i = (PFNGLUNIFORM4I_PROC*)glfwGetProcAddress("glUniform4i");
    glpfUniform1fv = (PFNGLUNIFORM1FV_PROC*)glfwGetProcAddress("glUniform1fv");
    glpfUniform2fv = (PFNGLUNIFORM2FV_PROC*)glfwGetProcAddress("glUniform2fv");
    glpfUniform3fv = (PFNGLUNIFORM3FV_PROC*)glfwGetProcAddress("glUniform3fv");
    glpfUniform4fv = (PFNGLUNIFORM4FV_PROC*)glfwGetProcAddress("glUniform4fv");
    glpfUniform1iv = (PFNGLUNIFORM1IV_PROC*)glfwGetProcAddress("glUniform1iv");
    glpfUniform2iv = (PFNGLUNIFORM2IV_PROC*)glfwGetProcAddress("glUniform2iv");
    glpfUniform3iv = (PFNGLUNIFORM3IV_PROC*)glfwGetProcAddress("glUniform3iv");
    glpfUniform4iv = (PFNGLUNIFORM4IV_PROC*)glfwGetProcAddress("glUniform4iv");
    glpfUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FV_PROC*)glfwGetProcAddress("glUniformMatrix2fv");
    glpfUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FV_PROC*)glfwGetProcAddress("glUniformMatrix3fv");
    glpfUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FV_PROC*)glfwGetProcAddress("glUniformMatrix4fv");
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


    /* GL_VERSION_2_1 */

    glpfUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FV_PROC*)glfwGetProcAddress("glUniformMatrix2x3fv");
    glpfUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FV_PROC*)glfwGetProcAddress("glUniformMatrix3x2fv");
    glpfUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FV_PROC*)glfwGetProcAddress("glUniformMatrix2x4fv");
    glpfUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FV_PROC*)glfwGetProcAddress("glUniformMatrix4x2fv");
    glpfUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FV_PROC*)glfwGetProcAddress("glUniformMatrix3x4fv");
    glpfUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FV_PROC*)glfwGetProcAddress("glUniformMatrix4x3fv");


}

/* ----------------------- Extension flag definitions ---------------------- */
int FLEXT_EXT_framebuffer_object = GL_FALSE;
int FLEXT_EXT_geometry_shader4 = GL_FALSE;
int FLEXT_NV_transform_feedback = GL_FALSE;

/* ---------------------- Function pointer definitions --------------------- */

/* GL_EXT_framebuffer_object */

PFNGLISRENDERBUFFEREXT_PROC* glpfIsRenderbufferEXT = NULL;
PFNGLBINDRENDERBUFFEREXT_PROC* glpfBindRenderbufferEXT = NULL;
PFNGLDELETERENDERBUFFERSEXT_PROC* glpfDeleteRenderbuffersEXT = NULL;
PFNGLGENRENDERBUFFERSEXT_PROC* glpfGenRenderbuffersEXT = NULL;
PFNGLRENDERBUFFERSTORAGEEXT_PROC* glpfRenderbufferStorageEXT = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVEXT_PROC* glpfGetRenderbufferParameterivEXT = NULL;
PFNGLISFRAMEBUFFEREXT_PROC* glpfIsFramebufferEXT = NULL;
PFNGLBINDFRAMEBUFFEREXT_PROC* glpfBindFramebufferEXT = NULL;
PFNGLDELETEFRAMEBUFFERSEXT_PROC* glpfDeleteFramebuffersEXT = NULL;
PFNGLGENFRAMEBUFFERSEXT_PROC* glpfGenFramebuffersEXT = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXT_PROC* glpfCheckFramebufferStatusEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE1DEXT_PROC* glpfFramebufferTexture1DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXT_PROC* glpfFramebufferTexture2DEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE3DEXT_PROC* glpfFramebufferTexture3DEXT = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXT_PROC* glpfFramebufferRenderbufferEXT = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXT_PROC* glpfGetFramebufferAttachmentParameterivEXT = NULL;
PFNGLGENERATEMIPMAPEXT_PROC* glpfGenerateMipmapEXT = NULL;

/* GL_EXT_geometry_shader4 */

PFNGLPROGRAMPARAMETERIEXT_PROC* glpfProgramParameteriEXT = NULL;

/* GL_NV_transform_feedback */

PFNGLBEGINTRANSFORMFEEDBACKNV_PROC* glpfBeginTransformFeedbackNV = NULL;
PFNGLENDTRANSFORMFEEDBACKNV_PROC* glpfEndTransformFeedbackNV = NULL;
PFNGLTRANSFORMFEEDBACKATTRIBSNV_PROC* glpfTransformFeedbackAttribsNV = NULL;
PFNGLBINDBUFFERRANGENV_PROC* glpfBindBufferRangeNV = NULL;
PFNGLBINDBUFFEROFFSETNV_PROC* glpfBindBufferOffsetNV = NULL;
PFNGLBINDBUFFERBASENV_PROC* glpfBindBufferBaseNV = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSNV_PROC* glpfTransformFeedbackVaryingsNV = NULL;
PFNGLACTIVEVARYINGNV_PROC* glpfActiveVaryingNV = NULL;
PFNGLGETVARYINGLOCATIONNV_PROC* glpfGetVaryingLocationNV = NULL;
PFNGLGETACTIVEVARYINGNV_PROC* glpfGetActiveVaryingNV = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGNV_PROC* glpfGetTransformFeedbackVaryingNV = NULL;
PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNV_PROC* glpfTransformFeedbackStreamAttribsNV = NULL;

/* GL_VERSION_1_2 */

PFNGLBLENDCOLOR_PROC* glpfBlendColor = NULL;
PFNGLBLENDEQUATION_PROC* glpfBlendEquation = NULL;
PFNGLDRAWRANGEELEMENTS_PROC* glpfDrawRangeElements = NULL;
PFNGLTEXIMAGE3D_PROC* glpfTexImage3D = NULL;
PFNGLTEXSUBIMAGE3D_PROC* glpfTexSubImage3D = NULL;
PFNGLCOPYTEXSUBIMAGE3D_PROC* glpfCopyTexSubImage3D = NULL;
PFNGLCOLORTABLE_PROC* glpfColorTable = NULL;
PFNGLCOLORTABLEPARAMETERFV_PROC* glpfColorTableParameterfv = NULL;
PFNGLCOLORTABLEPARAMETERIV_PROC* glpfColorTableParameteriv = NULL;
PFNGLCOPYCOLORTABLE_PROC* glpfCopyColorTable = NULL;
PFNGLGETCOLORTABLE_PROC* glpfGetColorTable = NULL;
PFNGLGETCOLORTABLEPARAMETERFV_PROC* glpfGetColorTableParameterfv = NULL;
PFNGLGETCOLORTABLEPARAMETERIV_PROC* glpfGetColorTableParameteriv = NULL;
PFNGLCOLORSUBTABLE_PROC* glpfColorSubTable = NULL;
PFNGLCOPYCOLORSUBTABLE_PROC* glpfCopyColorSubTable = NULL;
PFNGLCONVOLUTIONFILTER1D_PROC* glpfConvolutionFilter1D = NULL;
PFNGLCONVOLUTIONFILTER2D_PROC* glpfConvolutionFilter2D = NULL;
PFNGLCONVOLUTIONPARAMETERF_PROC* glpfConvolutionParameterf = NULL;
PFNGLCONVOLUTIONPARAMETERFV_PROC* glpfConvolutionParameterfv = NULL;
PFNGLCONVOLUTIONPARAMETERI_PROC* glpfConvolutionParameteri = NULL;
PFNGLCONVOLUTIONPARAMETERIV_PROC* glpfConvolutionParameteriv = NULL;
PFNGLCOPYCONVOLUTIONFILTER1D_PROC* glpfCopyConvolutionFilter1D = NULL;
PFNGLCOPYCONVOLUTIONFILTER2D_PROC* glpfCopyConvolutionFilter2D = NULL;
PFNGLGETCONVOLUTIONFILTER_PROC* glpfGetConvolutionFilter = NULL;
PFNGLGETCONVOLUTIONPARAMETERFV_PROC* glpfGetConvolutionParameterfv = NULL;
PFNGLGETCONVOLUTIONPARAMETERIV_PROC* glpfGetConvolutionParameteriv = NULL;
PFNGLGETSEPARABLEFILTER_PROC* glpfGetSeparableFilter = NULL;
PFNGLSEPARABLEFILTER2D_PROC* glpfSeparableFilter2D = NULL;
PFNGLGETHISTOGRAM_PROC* glpfGetHistogram = NULL;
PFNGLGETHISTOGRAMPARAMETERFV_PROC* glpfGetHistogramParameterfv = NULL;
PFNGLGETHISTOGRAMPARAMETERIV_PROC* glpfGetHistogramParameteriv = NULL;
PFNGLGETMINMAX_PROC* glpfGetMinmax = NULL;
PFNGLGETMINMAXPARAMETERFV_PROC* glpfGetMinmaxParameterfv = NULL;
PFNGLGETMINMAXPARAMETERIV_PROC* glpfGetMinmaxParameteriv = NULL;
PFNGLHISTOGRAM_PROC* glpfHistogram = NULL;
PFNGLMINMAX_PROC* glpfMinmax = NULL;
PFNGLRESETHISTOGRAM_PROC* glpfResetHistogram = NULL;
PFNGLRESETMINMAX_PROC* glpfResetMinmax = NULL;

/* GL_VERSION_1_3 */

PFNGLACTIVETEXTURE_PROC* glpfActiveTexture = NULL;
PFNGLSAMPLECOVERAGE_PROC* glpfSampleCoverage = NULL;
PFNGLCOMPRESSEDTEXIMAGE3D_PROC* glpfCompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXIMAGE2D_PROC* glpfCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE1D_PROC* glpfCompressedTexImage1D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3D_PROC* glpfCompressedTexSubImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2D_PROC* glpfCompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1D_PROC* glpfCompressedTexSubImage1D = NULL;
PFNGLGETCOMPRESSEDTEXIMAGE_PROC* glpfGetCompressedTexImage = NULL;
PFNGLCLIENTACTIVETEXTURE_PROC* glpfClientActiveTexture = NULL;
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
PFNGLLOADTRANSPOSEMATRIXF_PROC* glpfLoadTransposeMatrixf = NULL;
PFNGLLOADTRANSPOSEMATRIXD_PROC* glpfLoadTransposeMatrixd = NULL;
PFNGLMULTTRANSPOSEMATRIXF_PROC* glpfMultTransposeMatrixf = NULL;
PFNGLMULTTRANSPOSEMATRIXD_PROC* glpfMultTransposeMatrixd = NULL;

/* GL_VERSION_1_4 */

PFNGLBLENDFUNCSEPARATE_PROC* glpfBlendFuncSeparate = NULL;
PFNGLMULTIDRAWARRAYS_PROC* glpfMultiDrawArrays = NULL;
PFNGLMULTIDRAWELEMENTS_PROC* glpfMultiDrawElements = NULL;
PFNGLPOINTPARAMETERF_PROC* glpfPointParameterf = NULL;
PFNGLPOINTPARAMETERFV_PROC* glpfPointParameterfv = NULL;
PFNGLPOINTPARAMETERI_PROC* glpfPointParameteri = NULL;
PFNGLPOINTPARAMETERIV_PROC* glpfPointParameteriv = NULL;
PFNGLFOGCOORDF_PROC* glpfFogCoordf = NULL;
PFNGLFOGCOORDFV_PROC* glpfFogCoordfv = NULL;
PFNGLFOGCOORDD_PROC* glpfFogCoordd = NULL;
PFNGLFOGCOORDDV_PROC* glpfFogCoorddv = NULL;
PFNGLFOGCOORDPOINTER_PROC* glpfFogCoordPointer = NULL;
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

PFNGLGENQUERIES_PROC* glpfGenQueries = NULL;
PFNGLDELETEQUERIES_PROC* glpfDeleteQueries = NULL;
PFNGLISQUERY_PROC* glpfIsQuery = NULL;
PFNGLBEGINQUERY_PROC* glpfBeginQuery = NULL;
PFNGLENDQUERY_PROC* glpfEndQuery = NULL;
PFNGLGETQUERYIV_PROC* glpfGetQueryiv = NULL;
PFNGLGETQUERYOBJECTIV_PROC* glpfGetQueryObjectiv = NULL;
PFNGLGETQUERYOBJECTUIV_PROC* glpfGetQueryObjectuiv = NULL;
PFNGLBINDBUFFER_PROC* glpfBindBuffer = NULL;
PFNGLDELETEBUFFERS_PROC* glpfDeleteBuffers = NULL;
PFNGLGENBUFFERS_PROC* glpfGenBuffers = NULL;
PFNGLISBUFFER_PROC* glpfIsBuffer = NULL;
PFNGLBUFFERDATA_PROC* glpfBufferData = NULL;
PFNGLBUFFERSUBDATA_PROC* glpfBufferSubData = NULL;
PFNGLGETBUFFERSUBDATA_PROC* glpfGetBufferSubData = NULL;
PFNGLMAPBUFFER_PROC* glpfMapBuffer = NULL;
PFNGLUNMAPBUFFER_PROC* glpfUnmapBuffer = NULL;
PFNGLGETBUFFERPARAMETERIV_PROC* glpfGetBufferParameteriv = NULL;
PFNGLGETBUFFERPOINTERV_PROC* glpfGetBufferPointerv = NULL;

/* GL_VERSION_2_0 */

PFNGLBLENDEQUATIONSEPARATE_PROC* glpfBlendEquationSeparate = NULL;
PFNGLDRAWBUFFERS_PROC* glpfDrawBuffers = NULL;
PFNGLSTENCILOPSEPARATE_PROC* glpfStencilOpSeparate = NULL;
PFNGLSTENCILFUNCSEPARATE_PROC* glpfStencilFuncSeparate = NULL;
PFNGLSTENCILMASKSEPARATE_PROC* glpfStencilMaskSeparate = NULL;
PFNGLATTACHSHADER_PROC* glpfAttachShader = NULL;
PFNGLBINDATTRIBLOCATION_PROC* glpfBindAttribLocation = NULL;
PFNGLCOMPILESHADER_PROC* glpfCompileShader = NULL;
PFNGLCREATEPROGRAM_PROC* glpfCreateProgram = NULL;
PFNGLCREATESHADER_PROC* glpfCreateShader = NULL;
PFNGLDELETEPROGRAM_PROC* glpfDeleteProgram = NULL;
PFNGLDELETESHADER_PROC* glpfDeleteShader = NULL;
PFNGLDETACHSHADER_PROC* glpfDetachShader = NULL;
PFNGLDISABLEVERTEXATTRIBARRAY_PROC* glpfDisableVertexAttribArray = NULL;
PFNGLENABLEVERTEXATTRIBARRAY_PROC* glpfEnableVertexAttribArray = NULL;
PFNGLGETACTIVEATTRIB_PROC* glpfGetActiveAttrib = NULL;
PFNGLGETACTIVEUNIFORM_PROC* glpfGetActiveUniform = NULL;
PFNGLGETATTACHEDSHADERS_PROC* glpfGetAttachedShaders = NULL;
PFNGLGETATTRIBLOCATION_PROC* glpfGetAttribLocation = NULL;
PFNGLGETPROGRAMIV_PROC* glpfGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOG_PROC* glpfGetProgramInfoLog = NULL;
PFNGLGETSHADERIV_PROC* glpfGetShaderiv = NULL;
PFNGLGETSHADERINFOLOG_PROC* glpfGetShaderInfoLog = NULL;
PFNGLGETSHADERSOURCE_PROC* glpfGetShaderSource = NULL;
PFNGLGETUNIFORMLOCATION_PROC* glpfGetUniformLocation = NULL;
PFNGLGETUNIFORMFV_PROC* glpfGetUniformfv = NULL;
PFNGLGETUNIFORMIV_PROC* glpfGetUniformiv = NULL;
PFNGLGETVERTEXATTRIBDV_PROC* glpfGetVertexAttribdv = NULL;
PFNGLGETVERTEXATTRIBFV_PROC* glpfGetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBIV_PROC* glpfGetVertexAttribiv = NULL;
PFNGLGETVERTEXATTRIBPOINTERV_PROC* glpfGetVertexAttribPointerv = NULL;
PFNGLISPROGRAM_PROC* glpfIsProgram = NULL;
PFNGLISSHADER_PROC* glpfIsShader = NULL;
PFNGLLINKPROGRAM_PROC* glpfLinkProgram = NULL;
PFNGLSHADERSOURCE_PROC* glpfShaderSource = NULL;
PFNGLUSEPROGRAM_PROC* glpfUseProgram = NULL;
PFNGLUNIFORM1F_PROC* glpfUniform1f = NULL;
PFNGLUNIFORM2F_PROC* glpfUniform2f = NULL;
PFNGLUNIFORM3F_PROC* glpfUniform3f = NULL;
PFNGLUNIFORM4F_PROC* glpfUniform4f = NULL;
PFNGLUNIFORM1I_PROC* glpfUniform1i = NULL;
PFNGLUNIFORM2I_PROC* glpfUniform2i = NULL;
PFNGLUNIFORM3I_PROC* glpfUniform3i = NULL;
PFNGLUNIFORM4I_PROC* glpfUniform4i = NULL;
PFNGLUNIFORM1FV_PROC* glpfUniform1fv = NULL;
PFNGLUNIFORM2FV_PROC* glpfUniform2fv = NULL;
PFNGLUNIFORM3FV_PROC* glpfUniform3fv = NULL;
PFNGLUNIFORM4FV_PROC* glpfUniform4fv = NULL;
PFNGLUNIFORM1IV_PROC* glpfUniform1iv = NULL;
PFNGLUNIFORM2IV_PROC* glpfUniform2iv = NULL;
PFNGLUNIFORM3IV_PROC* glpfUniform3iv = NULL;
PFNGLUNIFORM4IV_PROC* glpfUniform4iv = NULL;
PFNGLUNIFORMMATRIX2FV_PROC* glpfUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX3FV_PROC* glpfUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX4FV_PROC* glpfUniformMatrix4fv = NULL;
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

/* GL_VERSION_2_1 */

PFNGLUNIFORMMATRIX2X3FV_PROC* glpfUniformMatrix2x3fv = NULL;
PFNGLUNIFORMMATRIX3X2FV_PROC* glpfUniformMatrix3x2fv = NULL;
PFNGLUNIFORMMATRIX2X4FV_PROC* glpfUniformMatrix2x4fv = NULL;
PFNGLUNIFORMMATRIX4X2FV_PROC* glpfUniformMatrix4x2fv = NULL;
PFNGLUNIFORMMATRIX3X4FV_PROC* glpfUniformMatrix3x4fv = NULL;
PFNGLUNIFORMMATRIX4X3FV_PROC* glpfUniformMatrix4x3fv = NULL;



#ifdef __cplusplus
}
#endif
