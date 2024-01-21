#pragma once

#include "../Utility/Common/Common.hpp"

interface IWindow {
    virtual ~IWindow() {};
    virtual void setHandle(void* handle) = 0;
    virtual void setSize(float width, float height) = 0;
    virtual void render() = 0;
    virtual void setTitle(void* title) = 0;
    virtual bool isParentWindow() = 0;
    virtual void* getHandleInstance() = 0;
    virtual void initialize() = 0;
};