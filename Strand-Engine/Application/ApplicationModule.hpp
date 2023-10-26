// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <String.hpp>

using namespace Strand_Std;

namespace Strand
{

class Application;
class WindowEvent;

// @brief Base class for all modules that can be added to the application.
class ENGINE_API ApplicationModule
{
    friend class Application;
public:
    // @brief Checks if this module is tickable.
    FORCEINLINE virtual bool IsTickEnabled() const noexcept = 0;
    // @brief Checks if this module accepts window event.
    FORCEINLINE virtual bool IsWindowEventEnabled() const noexcept = 0;
    // @brief Checks if this module validated for root changes.
    FORCEINLINE virtual bool IsModuleInvalidated() const noexcept = 0;

    virtual void OnStart() = 0;
    virtual void OnPreTick() = 0;
    virtual void OnTick() = 0;
    virtual void OnPostTick() = 0;
    virtual void OnStop() = 0;

    virtual void PreValidation() = 0;
    virtual void PostValidation() = 0;

    virtual void OnWindowEvent(WindowEvent* windowEvent) = 0;

protected:
    ApplicationModule() = default;
    ApplicationModule(const ApplicationModule&) = delete;
    ApplicationModule& operator=(const ApplicationModule&) = delete;
    ApplicationModule(ApplicationModule&&) = delete;
    ApplicationModule& operator=(ApplicationModule&&) = delete;
    virtual ~ApplicationModule()
    {
        SetOwnerApplication(nullptr);
    }

    FORCEINLINE Application* GetOwnerApplication() const noexcept { return OwnerApplication_; }

    void PostValidationRequest();
    void PostQuitMessage(const String& message);

private:
    void SetOwnerApplication(Application* ownerApplication) noexcept { OwnerApplication_ = ownerApplication; }
private:
    Application* OwnerApplication_;
};

} // Strand
