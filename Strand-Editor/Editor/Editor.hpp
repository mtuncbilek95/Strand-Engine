// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Graphics/GraphicsDevice/GraphicsDevice.hpp>
#include <Window/Window.hpp>
#include <Graphics/Command/CommandList.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_dx11.h>

namespace Strand
{

class Editor
{
public:
    Editor(GraphicsDevice* device, Window* window){
        OwnedDevice_ = device;
        OwnedWindow_ = window;
    }

    ~Editor() = default;

    void CreateEditor()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGui_ImplGlfw_InitForOther(OwnedWindow_->GetWindow(), true);
        ImGui_ImplDX11_Init(OwnedDevice_->GetDevice().Get(), OwnedCommandList_->GetDefferedContext().Get());
        ImGui::StyleColorsDark();
    }

    void DestroyEditor()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void RunEditor()
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    ImGuiIO& GetIO()
    {
        return ImGui::GetIO();
    }

    void SetCommandList(CommandList* commandList)
    {
        OwnedCommandList_ = commandList;
    }

    CommandList* GetCommandList() const
    {
        return OwnedCommandList_;
    }

private:
    GraphicsDevice* OwnedDevice_;
    Window* OwnedWindow_;
    CommandList* OwnedCommandList_;
};

} // Strand
