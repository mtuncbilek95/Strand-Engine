// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>
#include <Common/Singleton.hpp>
#include <Editor/Editor.hpp>

#include <Graphics/Manager/GraphicsManager.hpp>
#include <Window/Manager/WindowManager.hpp>

namespace Strand
{

class EditorManager : public Singleton<EditorManager>
{
public:
    EditorManager() = default;
    ~EditorManager() = default;

    void InitializeEditor()
    {
        if(Editor_ == nullptr)
            Editor_ = new Editor(GraphicsManager::GetInstance().GetGraphicsDevice(), WindowManager::GetInstance().GetWindow());
    }

    Editor* GetEditor() const { return Editor_; }

private:
    Editor* Editor_;
};

} // Strand
