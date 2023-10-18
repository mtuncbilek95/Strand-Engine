// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#include "ApplicationModule.hpp"

#include <Application/Application.hpp>

namespace Strand
{

void ApplicationModule::PostValidationRequest()
{
    OwnerApplication_->PostValidationRequest();
}

void ApplicationModule::PostQuitMessage(const String& message)
{
    OwnerApplication_->PostQuitMessage(message);
}

} // Strand