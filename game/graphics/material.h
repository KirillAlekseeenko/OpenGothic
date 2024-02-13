#pragma once

#include <Tempest/Texture2d>

#include <phoenix/material.hh>
#include <phoenix/world/vob_tree.hh>
#include <phoenix/ext/daedalus_classes.hh>

class Material final {
  public:
    Material()=default;
    Material(const phoenix::material& m, bool enableAlphaTest);
    Material(const phoenix::vob& vob);
    Material(const phoenix::c_particle_fx &src);

    enum AlphaFunc:uint8_t {
      Solid,
      AlphaTest,
      Water,
      Ghost,
      Multiply,
      Multiply2,
      Transparent,
      AdditiveLight,
      };

    const Tempest::Texture2d* tex=nullptr;
    std::vector<const Tempest::Texture2d*> frames;
    AlphaFunc                 alpha            = AlphaTest;
    float                     alphaWeight      = 1;
    Tempest::Point            texAniMapDirPeriod;
    uint64_t                  texAniFPSInv     = 1;
    bool                      isGhost          = false;
    float                     waveMaxAmplitude = 0;
    float                     envMapping       = 0;

    bool operator <  (const Material& other) const;
    bool operator >  (const Material& other) const;
    bool operator == (const Material& other) const;

    bool isSolid() const;
    int  alphaOrder() const { return alphaOrder(alpha,isGhost); }

    bool hasFrameAnimation()     const { return !frames.empty() && texAniFPSInv!=0;    }
    bool hasUvAnimation()        const { return texAniMapDirPeriod!=Tempest::Point(0); }
    bool isTesselated()          const { return isTesselated(alpha);                   }
    bool isForwardShading()      const { return isForwardShading(alpha);               }
    bool isSceneInfoRequired()   const { return isSceneInfoRequired(alpha);            }
    bool isShadowmapRequired()   const { return isShadowmapRequired(alpha);            }
    bool isTextureInShadowPass() const { return isTextureInShadowPass(alpha);          }

    static bool isTesselated(AlphaFunc alpha);
    static bool isForwardShading(AlphaFunc alpha);
    static bool isSceneInfoRequired(AlphaFunc alpha);
    static bool isShadowmapRequired(AlphaFunc alpha);
    static bool isTextureInShadowPass(AlphaFunc alpha);

  private:
    static int alphaOrder(AlphaFunc a, bool ghost);

    static AlphaFunc loadAlphaFunc(phoenix::alpha_function zenAlpha, phoenix::material_group matGroup,
                                   uint8_t alpha, const Tempest::Texture2d* tex, bool enableAlphaTest);
    void             loadFrames(const phoenix::material& m);
  };

