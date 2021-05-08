#pragma once

#include <vector.h>
#include <geometry_msgs/PoseStamped.h>

namespace HybridAStar {

    class Tejas
    {
    private:
        /* data */
    public:
        vector<geometry_msgs::PoseStamped> poses;
    };
}
    