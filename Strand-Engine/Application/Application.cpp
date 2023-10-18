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
    for(auto& module: Modules_) {
        module->OnStop();
        module.reset();
    }

    Modules_.clear();
}

void Application::OnStart()
{
    for(auto& module: Modules_) {
        if(module->IsTickEnabled())
            TickableModules_.push_back(module);

        if(module->IsModuleInvalidated())
            InValidatedModules_.push_back(module);

        if(module->IsWindowEventEnabled())
            WindowEventModules_.push_back(module);

        module->OnStart();
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