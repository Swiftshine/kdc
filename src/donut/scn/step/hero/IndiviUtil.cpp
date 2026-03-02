#include "scn/step/hero/IndiviUtil.hpp"
#include "hel/math/Vector3.hpp"
#include "param/JITParam.hpp"

using namespace scn::step::hero;

scn::step::common::Param* IndiviUtil::Param(const Hero& rHero) {
    switch (rHero.kind()) {
        case KIND_KIRBY_1:
        case KIND_KIRBY_2:
        case KIND_KIRBY_3:
        case KIND_KIRBY_4:
            return rHero.param()->indiviKirby();
        case KIND_META:
            return rHero.param()->indiviMeta();
        case KIND_DEDEDE:
            return rHero.param()->indiviDedede();
        case KIND_DEE:
            return rHero.param()->indiviDee();
        default:
            return rHero.param()->indiviKirby();
    }
}

template <>
const NodeAttachParam& param::JITParam::data<NodeAttachParam>() const;

// https://decomp.me/scratch/lY9I9
void IndiviUtil::InitNodeAttach(NodeAttach& rNodeAttach, Kind kind) {
    switch (kind) {
        case KIND_META: {
            param::JITParam param("step/hero/nodeattach/Meta");
            const NodeAttachParam& data = param.data<NodeAttachParam>();

            rNodeAttach.setOffset(hel::math::Vector3(data.mOffset.x, data.mOffset.y, data.mOffset.z));
            rNodeAttach.setRotate(hel::math::Vector3(data.mRotate.x, data.mRotate.y, data.mRotate.z));
            rNodeAttach.setScale(data.mScale);

            break;
        }

        case KIND_DEDEDE: {
            param::JITParam param("step/hero/nodeattach/Dedede");
            const NodeAttachParam& data = param.data<NodeAttachParam>();

            rNodeAttach.setOffset(hel::math::Vector3(data.mOffset.x, data.mOffset.y, data.mOffset.z));
            rNodeAttach.setRotate(hel::math::Vector3(data.mRotate.x, data.mRotate.y, data.mRotate.z));
            rNodeAttach.setScale(data.mScale);
            break;
        }

        case KIND_DEE: {
            param::JITParam param("step/hero/nodeattach/Dee");
            const NodeAttachParam& data = param.data<NodeAttachParam>();

            rNodeAttach.setOffset(hel::math::Vector3(data.mOffset.x, data.mOffset.y, data.mOffset.z));
            rNodeAttach.setRotate(hel::math::Vector3(data.mRotate.x, data.mRotate.y, data.mRotate.z));
            rNodeAttach.setScale(data.mScale);
            break;
        }

        default: break;
    }
}

// https://decomp.me/scratch/CdXv3
template <>
const NodeAttachParam& param::JITParam::data<NodeAttachParam>() const {
    loadCheck();
    xdata::XDataHeader* header = mAccessor->mXData;
    return (NodeAttachParam&)(*(NodeAttachParam*)xdata::XData::dataHeadAddress(header));
}

float IndiviUtil::CenterOffset(Kind kind) {
    switch (kind) {
        case KIND_KIRBY_1:
        case KIND_KIRBY_2:
        case KIND_KIRBY_3:
        case KIND_KIRBY_4:
            return 0.5f;
        case KIND_META:     return 0.5f;
        case KIND_DEDEDE:   return 0.75f;
        case KIND_DEE:      return 0.5f;
        default:            return 0.5f;
    }
}

void IndiviUtil::VacuumAttackerOffset() {
    m_0 = 0.0f;
    m_4 = 0.75f;
}

// https://decomp.me/scratch/HpNqE
bool IndiviUtil::IsKirby(Kind kind) {
    return kind < KIND_META;
}

bool IndiviUtil::IsMeta(Kind kind) {
    return kind == KIND_META;
}

bool IndiviUtil::IsDedede(Kind kind) {
    return kind == KIND_DEDEDE;
}

bool IndiviUtil::IsDee(Kind kind) {
    return kind == KIND_DEE;
}

bool IndiviUtil::CanHover(Kind kind) {
    if (IsKirby(kind)) {
        return true;
    }

    return IsDedede(kind);
}
