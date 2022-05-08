#pragma once

#include "imgui.h"

namespace big
{
#define FIND(value, list) find(value, sizeof(list) / sizeof(list[0]), list)
#define IS(value, list) FIND(value, list)
#define LEN(list) (sizeof(list) / sizeof(list[0]))

    template<typename T>
    inline bool find(T item, int n, const T* data)
    {
        for (int i = 0; i < n; i++)
        {
            if (data[i] == item)
                return true;
        }
        return false;
    }
}