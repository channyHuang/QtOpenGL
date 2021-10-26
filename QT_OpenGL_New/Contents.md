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
**Listing 2.1: Our first OpenGL application**  
simpleclear  
**Listing 2.7: Rendering a single point**
singlepoint  
**Listing 2.9: Rendering a single triangle**  
singletri 

# Part 2 : OpenGL Super Bible (7 edition)  
## Chapter 3  
### Tessellation  
opengl_tessellation  
(sb7 Listing 3.8: Our first tessellation evaluation shader: tessellatedtri)
Qt中删除了glPolygonMode  
opengl_tessellation-gs  
(sb7 Listing 3.9: Our first geometry shader: tessellatedgstri) 

# Chapter 3
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

# Chapter 4
 
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

## Chapter 6  
### Separate Programs
(sb 7 **Listing 6.4: Printing interface information**: programinfo)
### Shader Subroutines
(sb 7 **Listing 6.5: Example subroutine uniform declaration**: subroutines)

**Listing 6.4: Printing interface information**
programinfo
**Listing 6.5: Example subroutine uniform declaration**
subroutines

## Chapter 7
**Listing 7.6: Pseudocode for glDrawElementsInstanced()**
grass
**Listing 7.9: Getting ready for instanced rendering**
instancedattribs
**Listing 7.11: Setting up the indirect draw buffer for asteroids**
multidrawindirect
**Listing 7.17: Spring mass system vertex shader**
sprintmass
**Listing 7.20: Clipping an object against a plane and a sphere**
clipdistance

## Chapter 8
**Listing 8.1: Simple quad tessellation control shader example**
tessellatedcube
**Listing 8.7: Isoline spirals tessellation evaluation shader**
tesssubdivmodes
**Listing 8.8: Vertex shader for terrain rendering**
dispmap
**Listing 8.15: Cubic Bézier patch fragment shader**
cubicbezier
**Listing 8.20: Configuring the custom culling geometry shader**
gsculling
**Listing 8.24: Pushing a face out along its normal**
objectexpolder
**Listing 8.26: Setting up the “tessellator” geometry shader**
gstessellate
**Listing 8.33: Drawing a face normal in the geometry shader**
normalviewer
**Listing 8.35: Fragment shader for rendering quads**
gsquads
**Listing 8.36: Rendering to multiple viewports in a geometry shader**
multiviewport
# Chapter 9
**Listing 9.1: Setting up scissor rectangle arrays**
multiscissor
**Listing 9.3: Rendering with all blending functions**
blendmatrix
**Listing 9.5: Rendering to a texture**
basicfbo
**Listing 9.10: Displaying an array texture—vertex shader**
gslayered
**Listing 9.15: Drawing into a stereo window**
stereo
**Listing 9.18: Turning on line smoothing**
linesmooth
**Listing 9.22: Fragment shader producing high-frequency output**
sampleshading
**Listing 9.24: Applying a simple exposure coefficient to an HDR image**
hdrexposure
**Listing 9.26: Bloom fragment shader—output bright data to a separate buffer**
hdrbloom
**Listing 9.32: Fragment shader for the star field effect**
starfield
**Listing 9.33: Fragment shader for generating shaped points**
shapedpoints
**?**
depthclamp
hdrtonemap
msaanative
polygonsmooth
# Chapter 10
**Listing 10.5: Simple prefix sum implementation in C++**
prefixsum
**Listing 10.7: Compute shader to generate a 2D prefix sum**
prefixsum2d
**Listing 10.8: Depth of field using summed area tables**
dof
**Listing 10.14: Main body of the flocking update compute shader**
csflocking
# Chapter 11
**Listing 11.2: Declaring samplers inside uniform blocks**
bindlesstex
**Listing 11.4: Creating a sparse texture**
sparsetexture
**Listing 11.13: Main function for RGTC compression**
compressrgtc
**Listing 11.14: High-quality texture filtering function**
hqfilter
# Chapter 12
# Chapter 13
**Listing 13.4: The Phong shading fragment shader**
phonglighting
**Listing 13.5: Blinn-Phong fragment shader**
blinnphone
**Listing 13.6: Rim lighting shader function**
rimlight
**Listing 13.7: Vertex shader for normal mapping**
bumpmapping
**Listing 13.10: Spherical environment mapping fragment shader**
envmapsphere
**Listing 13.11: Equirectangular environment mapping fragment shader**
equirectangular
**Listing 13.16: Fragment shader for cubemap environment rendering**
cubemapenv
**Listing 13.17: Fragment shader for per-fragment shininess**
perpixelgloss
**Listing 13.22: Simplified fragment shader for shadow mapping**
shadowmapping
**Listing 13.26: The toon fragment shader**
toonshading
**Listing 13.28: Writing to a G-buffer**
deferredshading
**Listing 13.32: Ambient occlusion fragment shader**
ssao
**Listing 13.34: Inner loop of the Julia renderer**
Julia
**Listing 13.38: Ray–plane interesection test**
raytracer
**Listing 13.39: Fragment shader for distance field rendering**
sdfdemo