#pragma once
#include <set>
#include <string>
#include "./vital.h"

struct SPO2 : public Vital {
    private:
        enum class Category {
            HYPOAXEMIA,
            NEAR_HYPOAXEMIA,
            NORMAL,
            NEAR_HYPEROAXEMIA,
            HYPEROAXEMIA
        };
    public:
        explicit SPO2(float spo2);
        std::set<int> collectInvalidCategories() const override;
        std::string getMessage(int category) const override;
};
