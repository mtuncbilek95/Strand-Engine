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

    virtual void OnStart() = 0;
    virtual void OnPreTick() = 0;
    virtual void OnTick() = 0;
    virtual void OnPostTick() = 0;
    virtual void OnStop() = 0;

    virtual void PreValidation() = 0;
    virtual void PostValidation() = 0;

    virtual void OnWindowEvent(WindowEvent* windowEvent) = 0;

    template<typename T, typename... Args>
    requires std::derived_from<T, ApplicationModule>
    T* RegisterModule(Args&&... args)
    {
        T* module = new T(args...);
        module->SetOwnerApplication(this);
        Modules_.push_back(module);
        return module;
    }

    void RemoveAllModules()
    {
        for(auto& module: Modules_) {
            delete module;
            module = nullptr;
        }

        Modules_.clear();
    }

    template<typename T>
    T* GetModule()
    {
        for (auto& module : Modules_)
        {
            if (dynamic_cast<T*>(module))
                return dynamic_cast<T*>(module);
        }
        return nullptr;
    }

    template<typename T>
    std::vector<T*> GetModules()
    {
        std::vector<T*> modules;
        for (auto& module : Modules_)
        {
            if (dynamic_cast<T*>(module))
                modules.push_back(dynamic_cast<T*>(module));
        }
        return modules;
    }

    void PostValidationRequest();
    void PostQuitMessgage(const std::string& message);

private:
    std::vector<ApplicationModule*> Modules_;
    std::vector<ApplicationModule*> TickableModules_;
    std::vector<ApplicationModule*> WindowEventModules_;
    std::vector<ApplicationModule*> InValidatedModules_;
};

} // Strand
