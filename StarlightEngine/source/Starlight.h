/* ---------------OPENGL----------------- */
#include "GL/glew.h"
#include "GLFW/glfw3.h"
/* -------------------------------------- */

#include "defines.h"

/* -----------------CORE----------------- */
#include "Core/Application.h"
#include "Core/AWindow.h"
#include "Core/Input.h"
#include "Core/enums.h"
#include "Core/Log.h"
/* -------------------------------------- */

/* --------------RENDERER----------------*/
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/IBuffers.h"
#include "Core/Renderer/IVertexArray.h"
#include "Core/Renderer/IShader.h"
#include "Core/Renderer/ITexture.h"
#include "Core/Renderer/ShaderLibrary.h"
#include "Core/Renderer/IFrameBuffer.h"
#include "Core/Renderer/Camera.h"
/* -------------------------------------- */

/* --------------Components-------------- */
#include "Components/Graphics/Light.h"
#include "Components/Graphics/Material.h"
#include "Components/Mesh/Mesh.h"
/* -------------------------------------- */

