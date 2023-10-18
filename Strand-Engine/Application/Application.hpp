// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Common/Common.hpp>

namespace Strand
{

class WindowEvent;
class ApplicationModule;

class Application
{
public:
    Application() = default;
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    virtual ~Application() = default;

    virtual void OnStart();
    virtual void OnPreTick();
    virtual void OnTick();
    virtual void OnPostTick();
    virtual void OnStop();

    virtual void PreValidation();
    virtual void PostValidation();

    virtual void OnWindowEvent(WindowEvent* windowEvent);

    template<typename T, typename... Args>
    requires std::derived_from<T, ApplicationModule>
    SharedHeap<T> RegisterModule(Args&&... args)
    {
        auto module = std::make_shared<T>(args...);
        Modules_.push_back(module);
        module->SetOwnerApplication(this);

        return module;
    }

    void RemoveAllModules();

    template<typename T>
    SharedHeap<T> GetModule()
    {
        for(auto& module: Modules_) {
            if(auto castedModule = std::dynamic_pointer_cast<T>(module)) {
                return castedModule;
            }
        }

        return nullptr;
    }

    template<typename T>
    ArrayList<SharedHeap<T>> GetModules()
    {
        ArrayList<SharedHeap<T>> modules;
        for(auto& module: Modules_) {
            if(auto castedModule = std::dynamic_pointer_cast<T>(module)) {
                modules.push_back(castedModule);
            }
        }
        return modules;
    }

    void PostValidationRequest();
    void PostQuitMessage(const String& message);

private:
    ArrayList<SharedHeap<ApplicationModule>> Modules_;
    ArrayList<SharedHeap<ApplicationModule>> TickableModules_;
    ArrayList<SharedHeap<ApplicationModule>> WindowEventModules_;
    ArrayList<SharedHeap<ApplicationModule>> InValidatedModules_;
};

} // Strand
