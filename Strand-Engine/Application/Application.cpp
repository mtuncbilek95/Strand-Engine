// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "Application.hpp"

#include <Application/ApplicationModule.hpp>

namespace Strand
{

void Application::PostValidationRequest()
{

}

void Application::PostQuitMessage(const String& message)
{

}

void Application::RemoveAllModules()
{
    for(int i = 0; i < Modules_.GetSize(); i++)
        Modules_[i]->OnStop();

    Modules_.Clear();
}

void Application::OnStart()
{
    for(int i = 0; i < Modules_.GetSize(); i++)
    {
        if(Modules_[i]->IsTickEnabled())
            TickableModules_.AddLast(Modules_[i]);

        if(Modules_[i]->IsWindowEventEnabled())
            WindowEventModules_.AddLast(Modules_[i]);

        if(Modules_[i]->IsModuleInvalidated())
            InvalidatedModules_.AddLast(Modules_[i]);

        Modules_[i]->OnStart();
    }

}

void Application::OnPreTick()
{
    for(auto& module: Modules_) {
        module->OnPreTick();
    }
}

void Application::OnTick()
{
    for(auto& module: Modules_) {
        module->OnTick();
    }
}

void Application::OnPostTick()
{
    for(auto& module: Modules_) {
        module->OnPostTick();
    }
}

void Application::OnStop()
{
    for(auto& module: Modules_) {
        module->OnStop();
    }
}

void Application::PreValidation()
{
    for(auto& module: Modules_) {
        module->PreValidation();
    }
}

void Application::PostValidation()
{
    for(auto& module: Modules_) {
        module->PostValidation();
    }
}

void Application::OnWindowEvent(WindowEvent* windowEvent)
{
    for(auto& module: Modules_) {
        module->OnWindowEvent(windowEvent);
    }
}

} // Strand