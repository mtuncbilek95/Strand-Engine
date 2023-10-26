// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <Core.hpp>
#include <String.hpp>
#include <ArrayList.hpp>

using namespace Strand_Std;

namespace Strand
{

class WindowEvent;
class ApplicationModule;

class ENGINE_API Application
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
    T* RegisterModule(Args&&... args)
    {
        auto module = new T(args...);
        Modules_.AddLast(module);
        module->SetOwnerApplication(this);

        return module;
    }

    void RemoveAllModules();

    template<typename T>
    T* GetModule()
    {
    }

    template<typename T>
    ArrayList<T*> GetModules()
    {
    }

    void PostValidationRequest();
    void PostQuitMessage(const String& message);

private:
    ArrayList<ApplicationModule*> Modules_;
    ArrayList<ApplicationModule*> TickableModules_;
    ArrayList<ApplicationModule*> WindowEventModules_;
    ArrayList<ApplicationModule*> InvalidatedModules_;
};

} // Strand
