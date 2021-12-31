//
// Created by Stefan Annell on 2021-12-31.
//

#pragma once
#include "hittable.h"
#include <vector>
#include <memory>

class hittable_list : public hittable {
public:
  hittable_list();
  hittable_list(std::shared_ptr<hittable> object);

  void clear();
  void add(std::shared_ptr<hittable> object);
  bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

public:
  std::vector<std::shared_ptr<hittable>> objects;
};
