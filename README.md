![Banner.png](Resources%2FBanner.png)
# Strand Engine

This is Strand Engine. It is my custom game engine that will be used in my future projects. It is 
written in C++ and uses Vulkan API for rendering. It is still in development. I will add more features 
as I learn more about game engine development. It will most probably use Nvidia Physx for physics
engine. But in the meantime, that doesn't mean I will not try to implement my own physics' engine. It is also 
mean that I will most probably use Wwise for audio engine. But I don't think that I will implement my own.
This engine currently runs with DirectX11. But when I release the first version, it will run with only Vulkan.

## Future Integrated Libraries
- [Vulkan](https://www.khronos.org/vulkan/) (Currently only DirectX11 is supported)
- [GLFW](https://www.glfw.org/) (Windows OS won't be supported in the future)
- [ImGui](https://github.com/ocornut/imgui)
- [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)
- [ImGuiNodes](https://github.com/thedmd/imgui-node-editor)
- [Assimp](https://github.com/assimp/assimp) (Work in progress)
- [Physx](https://www.nvidia.com/en-us/drivers/physx/physx-9-19-0218-driver/) (Will have the opportunity to change it to Strand Physics Engine)
- [Wwise](https://www.audiokinetic.com/products/wwise/)
- [STB](https://github.com/nothings/stb) (Have no abstraction layer yet)


## What is done so far
- [x] Framebuffer
- [x] Swapchain
- [x] Graphics Device
- [x] Device Object
- [x] Command List
- [x] Shader
- [x] Pipeline v1
- [x] Buffer Object
- [x] Texture View Object
- [x] Shader Resource View in Texture View Object
- [x] Sampler State
- [x] Command List Bindings for Pipeline v1
- [ ] Assimp Model Loader + Mesh Abstraction Layer
- [ ] ECS System
- [ ] Game Structure to Create Objects
- [ ] Basic Light
- [ ] Camera
- [ ] PBR
- [ ] Input System for both Games and Editor
- [ ] Imgui Editor to edit my projects in this game engine.
- [ ] Reflection System & Metadata
- [ ] Reflection Parser
- [ ] Multi-Framebuffer System

### Next Goals:

- Callback event listener for Window class is needed
- Assimp + Mesh Abstraction Layer
- ECS
- PBR
- Imgui
- Forward Deferred Rendering (Shadow Mapping)

Tasks:
- Fix Mesh Structure

## WARNING
## System is not working at the moment 