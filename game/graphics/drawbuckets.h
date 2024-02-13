#pragma once

#include <Tempest/StorageBuffer>

#include "material.h"

class StaticMesh;
class AnimMesh;

class DrawBuckets {
  public:
    DrawBuckets();

    struct Bucket {
      const StaticMesh* staticMesh = nullptr;
      const AnimMesh*   animMesh   = nullptr;
      Material          mat;
      };

    class Id {
      public:
        Id() = default;
        Id(DrawBuckets& owner):owner(&owner){}
        Id(Id&& other) noexcept;
        Id& operator = (Id&& other) noexcept;
        ~Id();

        uint16_t toInt() const { return id; }

        Bucket& operator *  () { return  owner->bucketsCpu[id]; }
        Bucket* operator -> () { return &owner->bucketsCpu[id]; }

      private:
        Id(DrawBuckets* owner, size_t id);

        DrawBuckets* owner = nullptr;
        uint16_t     id    = 0;
      friend class DrawBuckets;
      };

    Id   alloc(const Material& mat, const StaticMesh& mesh);
    Id   alloc(const Material& mat, const AnimMesh&   mesh);

    const Bucket& operator[](size_t i) { return bucketsCpu[i]; }

    auto ssbo() const -> const Tempest::StorageBuffer& { return bucketsGpu; }
    auto buckets() -> const std::vector<Bucket>&;

    bool commit(Tempest::Encoder<Tempest::CommandBuffer>& cmd, uint8_t fId);

  private:
    struct BucketGpu final {
      Tempest::Vec4  bbox[2];
      Tempest::Point texAniMapDirPeriod;
      float          bboxRadius       = 0;
      float          waveMaxAmplitude = 0;
      float          alphaWeight      = 1;
      float          envMapping       = 0;
      uint32_t       padd[2]          = {};
      };

    std::vector<Bucket>    bucketsCpu;
    Tempest::StorageBuffer bucketsGpu;
    bool                   bucketsDurtyBit = false;
  };
