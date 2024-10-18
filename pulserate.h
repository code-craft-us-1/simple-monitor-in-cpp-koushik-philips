#pragma once
#include <set>
#include <string>
#include "./vital.h"

struct PulseRate : public Vital {
 private:
  enum class Category {
     BRADYCARDIA,
     NEAR_BRADY,
     NORMAL,
     NEAR_TACHY,
     TACHYCARDIA
  };
 public:
  explicit PulseRate(float pulserate);
  std::set<int> collectInvalidCategories() const override;
  std::string getMessage(int category) const override;
  friend std::string getPulseRateCategoryMessage(int category);
};
