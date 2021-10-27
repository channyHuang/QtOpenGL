# Part 1 : Nehe
第一课：创建一个OpenGL窗口 opengl_window  
(sb7 Listing 2.1: Our first OpenGL application: simpleclear)  
第二课：你的第一个多边形 opengl_polygon  
(sb 7 Listing 2.9: Rendering a single triangle: singletri)  
第三课：上色 opengl_color  
(sb 7 Listing 3.12: Deriving a fragment’s color from its position: fragcolorfrompos)  
第四课：旋转 opengl_rotate  
(sb 7 Listing 5.25: Rendering loop for the spinning cube: spinnycube  
第五课：向三维进军 opengl_3d  
(sb 7 Listing 5.28: Rendering loop for the spinning cube: indexedcube)  
第六课：纹理映射 opengl_texture  
(sb 7 Listing 5.37: Reading from a texture in GLSL: simpletexture)

## Chapter 2
---
**Listing 2.1: Our first OpenGL application**
simpleclear  
**Listing 2.7: Rendering a single point**
singlepoint  
**Listing 2.9: Rendering a single triangle**
singletri  

---

# Part 2 : OpenGL Super Bible (7 edition)  

**编译环境**：windows 10 x64  
**Qt version**: 5.14.2

## Chapter 3  
### Tessellation  
opengl_tessellation  
(sb7 Listing 3.8: Our first tessellation evaluation shader: tessellatedtri)
Qt中删除了glPolygonMode  
opengl_tessellation-gs  
(sb7 Listing 3.9: Our first geometry shader: tessellatedgstri) 

---
**Listing 3.2: Updating a vertex attribute**
movingtri  
**Listing 3.8: Our first tessellation evaluation shader**
tessellatedtri  
**Listing 3.9: Our first geometry shader**
tessellatedgstri  
**Listing 3.12: Deriving a fragment’s color from its position**
fragcolorfrompos  
**?**
tessmodes  

---

## Chapter 4

Math
 
## Chapter 5
### Loading Textures from Files  
ktx专门为OpenGL设计的一种纹理文件  
glTexStorage1D在OpenGL 4.2 以上才有  
书中源码运行空白。。。
(sb 7 Listing 5.39: Loading a .KTX file: ktxview)  
书中使用了sbm模型文件
(sb 7 Listing 5.41: Fragment shader with a single texture coordinate: simpletexcoords)
### Mipmap
(sb 7 **Mipmaps in Action**: tunnel)
### Texture Wrap
书中源码运行空白。。。
(sb 7 **Texture Wrap**: mirrorclampedge)
### Accessing Texture Arrays
glVertexAttribI1i为OpenGL 4.2 Compacitility
### Atomic Operations on Images
Qt中运行异常
(sb 7 fragmentlist)

---
wrapmodes  
**Listing 5.25: Rendering loop for the spinning cube**
spinnycube  
**Listing 5.28: Rendering loop for the spinning cube**
indexedcube  
**Listing 5.37: Reading from a texture in GLSL**
simpletexture  
**Listing 5.39: Loading a .KTX file**
ktxview  
**Listing 5.41: Fragment shader with a single texture coordinate**
simpletexcoords  
**Mipmaps in Action**
tunnel  
**Texture Wrap**
mirrorclampedge  
**Listing 5.45: Rendering loop for the alien rain sample**
alienrain  
**Listing 5.48: Traversing a linked list in a fragment shader**
fragmentlist  

---

## Chapter 6  
### Separate Programs
(sb 7 **Listing 6.4: Printing interface information**: programinfo)
### Shader Subroutines
(sb 7 **Listing 6.5: Example subroutine uniform declaration**: subroutines)

---
**Listing 6.4: Printing interface information**
programinfo  
**Listing 6.5: Example subroutine uniform declaration**
subroutines  

---

## Chapter 7. Vertex Processing and Drawing Commands
### Combining Geometry Using Primitive Restart
grass  
### Getting Your Data Automatically
instancedattribs  
### Indirect Draws
multidrawindirect  
### Storing Transformed Vertices
sprintmass  
### User-Defined Clipping
clipdistance  

## Chapter 8. Primitive Processing
### Tessellation Primitive Modes
tessellatedcube
### Tessellation Using Isolines
tesssubdivmodes
### Tessellation Example: Terrain Rendering
dispmap
### Tessellation Example: Cubic Bézier Patches
cubicbezier
### Discarding Geometry in the Geometry Shader
gsculling
### Modifying Geometry in the Geometry Shader
objectexpolder
### Generating Geometry in the Geometry Shader
gstessellate
### Changing the Primitive Type in the Geometry Shader
normalviewer
### Rendering Quads Using a Geometry Shader
gsquads
### Multiple Viewport Transformations
multiviewport

## Chapter 9. Fragment Processing and the Framebuffer
### Scissor Testing
multiscissor
### Blending
blendmatrix
### Off-Screen Rendering
basicfbo
### Layered Rendering
gslayered
### Rendering in Stereo
3D立体渲染
stereo
### Antialiasing by Filtering
抗锯齿
linesmooth
### Sample Rate Shading
sampleshading
### Tone Mapping
hdrexposure
### Making Your Scene Bloom
hdrbloom
### Rendering a Star Field
starfield
### Shaped Points
shapedpoints
### 
depthclamp
hdrtonemap
msaanative
polygonsmooth

## Chapter 10. Compute Shaders
GPU并行处理计算，类似于CUDA
### Compute Shader Parallel Prefix Sum
prefixsum  
prefixsum2d  
dof
### Compute Shader Flocking
Flocking算法(蜂拥算法)  
csflocking

## Chapter 11
### Eliminating Binding
纹理一次性绑定
bindlesstex
### Sparsely Populated Textures
存储部分纹理
sparsetexture
### The RGTC Compression Scheme
纹理压缩
compressrgtc
### High-Quality Texture Filtering
hqfilter

## Chapter 12
OpenGL Query

## Chapter 13
三种光照模型
### The Phong Lighting Model
phonglighting
### Blinn-Phong Lighting
blinnphone
### Rim Lighting
rimlight
### Normal Mapping
法线贴图，通过贴图中的法线信息在较少的面片上渲染出更多凹凸不平的细节
bumpmapping
### Spherical Environment Maps
envmapsphere
### Equirectangular Environment Maps
equirectangular
### Cubemaps
天空盒
cubemapenv
### Material Properties
perpixelgloss
### Shadow Mapping
shadowmapping
### Cell Shading: Texels as Light
toonshading
### Generating the G-Buffer
deferredshading
### Ambient Occlusion
SSAO（Screen Space Ambient Occlusion）增加渲染的真实性
ssao
### Rendering without Triangles
Julia
### Ray Tracing in a Fragment Shader
raytracer
### Distance Field Textures
sdfdemo

## Chapter 14
smoothstep: 生成0到1的平滑过渡值，大概如下：
```
float smoothstep(float t1, float t2, float x) {
  x = clamp((x - t1) / (t2 - t1), 0.0, 1.0); 
  // Evaluate polynomial
  return x * x * (3 - 2 * x);
}
```
glBufferStorage需要OpenGL 4.4以上

---
**Listing 14.1: OpenMP particle updater**
ompparticles  
### Packet Buffers
packetbuffer  
### Indirect Rendering
indirectmaterial
**Listing 14.16: Candidate draws used for culling**
cullindirect
### Unmappable Resources
**Listing 14.20: Julia fractals on the CPU**
pmbfractal

---
