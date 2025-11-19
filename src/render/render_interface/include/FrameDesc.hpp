#pragma once

#include <vector>
#include <iostream>

#include <DrawItemDesc.hpp>

namespace Perspective::render {

    struct FrameDesc {
        std::vector<DrawItemDesc> drawItems;
    };

}