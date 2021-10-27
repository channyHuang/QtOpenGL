# Part 1 : Nehe
��һ�Σ�����һ��OpenGL���� opengl_window  
(sb7 Listing 2.1: Our first OpenGL application: simpleclear)  
�ڶ��Σ���ĵ�һ������� opengl_polygon  
(sb 7 Listing 2.9: Rendering a single triangle: singletri)  
�����Σ���ɫ opengl_color  
(sb 7 Listing 3.12: Deriving a fragment��s color from its position: fragcolorfrompos)  
���ĿΣ���ת opengl_rotate  
(sb 7 Listing 5.25: Rendering loop for the spinning cube: spinnycube  
����Σ�����ά���� opengl_3d  
(sb 7 Listing 5.28: Rendering loop for the spinning cube: indexedcube)  
�����Σ�����ӳ�� opengl_texture  
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

**���뻷��**��windows 10 x64  
**Qt version**: 5.14.2

## Chapter 3  
### Tessellation  
opengl_tessellation  
(sb7 Listing 3.8: Our first tessellation evaluation shader: tessellatedtri)
Qt��ɾ����glPolygonMode  
opengl_tessellation-gs  
(sb7 Listing 3.9: Our first geometry shader: tessellatedgstri) 

---
**Listing 3.2: Updating a vertex attribute**
movingtri  
**Listing 3.8: Our first tessellation evaluation shader**
tessellatedtri  
**Listing 3.9: Our first geometry shader**
tessellatedgstri  
**Listing 3.12: Deriving a fragment��s color from its position**
fragcolorfrompos  
**?**
tessmodes  

---

## Chapter 4

Math
 
## Chapter 5
### Loading Textures from Files  
ktxר��ΪOpenGL��Ƶ�һ�������ļ�  
glTexStorage1D��OpenGL 4.2 ���ϲ���  
����Դ�����пհס�����
(sb 7 Listing 5.39: Loading a .KTX file: ktxview)  
����ʹ����sbmģ���ļ�
(sb 7 Listing 5.41: Fragment shader with a single texture coordinate: simpletexcoords)
### Mipmap
(sb 7 **Mipmaps in Action**: tunnel)
### Texture Wrap
����Դ�����пհס�����
(sb 7 **Texture Wrap**: mirrorclampedge)
### Accessing Texture Arrays
glVertexAttribI1iΪOpenGL 4.2 Compacitility
### Atomic Operations on Images
Qt�������쳣
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
### Tessellation Example: Cubic B��zier Patches
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
3D������Ⱦ
stereo
### Antialiasing by Filtering
�����
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
GPU���д�����㣬������CUDA
### Compute Shader Parallel Prefix Sum
prefixsum  
prefixsum2d  
dof
### Compute Shader Flocking
Flocking�㷨(��ӵ�㷨)  
csflocking

## Chapter 11
### Eliminating Binding
����һ���԰�
bindlesstex
### Sparsely Populated Textures
�洢��������
sparsetexture
### The RGTC Compression Scheme
����ѹ��
compressrgtc
### High-Quality Texture Filtering
hqfilter

## Chapter 12
OpenGL Query

## Chapter 13
���ֹ���ģ��
### The Phong Lighting Model
phonglighting
### Blinn-Phong Lighting
blinnphone
### Rim Lighting
rimlight
### Normal Mapping
������ͼ��ͨ����ͼ�еķ�����Ϣ�ڽ��ٵ���Ƭ����Ⱦ�����఼͹��ƽ��ϸ��
bumpmapping
### Spherical Environment Maps
envmapsphere
### Equirectangular Environment Maps
equirectangular
### Cubemaps
��պ�
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
SSAO��Screen Space Ambient Occlusion��������Ⱦ����ʵ��
ssao
### Rendering without Triangles
Julia
### Ray Tracing in a Fragment Shader
raytracer
### Distance Field Textures
sdfdemo

## Chapter 14
smoothstep: ����0��1��ƽ������ֵ��������£�
```
float smoothstep(float t1, float t2, float x) {
  x = clamp((x - t1) / (t2 - t1), 0.0, 1.0); 
  // Evaluate polynomial
  return x * x * (3 - 2 * x);
}
```
glBufferStorage��ҪOpenGL 4.4����

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
