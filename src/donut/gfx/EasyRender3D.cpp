#pragma peephole off
#include <donut/gfx/EasyRender3D.hpp>
#include <donut/gfx/Utility.hpp>
#include <hel/math/Vector3.hpp>
#include <hel/math/Matrix34.hpp>
#include <hel/math/Matrix44.hpp>
#include <hel/math/Math.hpp>

namespace {
    static hel::math::Matrix34 t_viewMtx;

    void t_loadPosMtx(const hel::math::Matrix34& rPosMtx) {
        nw4r::math::MTX34 posMtx;
        nw4r::math::MTX34 secondMtx; //only set to identity lololol

        PSMTXIdentity(posMtx);
        PSMTXConcat(t_viewMtx.mBaseMtx, rPosMtx.mBaseMtx, posMtx);
        PSMTXIdentity(secondMtx);
        GXLoadPosMtxImm(posMtx, 0);
        GXSetCurrentMtx(0);
    }
}

namespace gfx {
    namespace EasyRender3D {

        void SetupGX(const hel::math::Matrix44& arg1, bool arg2) {
            Utility::SetGXStateDirty();
            GXSetProjection(arg1.mBaseMtx, (GXProjectionType)!arg2);
            GXSetNumChans(1);
            GXSetNumTexGens(0);
            GXSetNumTevStages(1);
            GXSetNumIndStages(0);
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEX_DISABLE, GX_COLOR0A0);
            GXSetTevDirect(GX_TEVSTAGE0);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
            GXColor tevKColor = {255, 255, 255, 255};
            GXSetTevKColor(GX_KCOLOR0, tevKColor);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE, GX_CC_C0);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST, GX_CA_A0);
            GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
            GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
            GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
            GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
            GXEnableTexOffsets(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
            GXInvalidateVtxCache();
            GXClearVtxDesc();
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetCullMode(GX_CULL_BACK);
            GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
            GXSetZCompLoc(GX_TRUE);
            GXSetColorUpdate(GX_TRUE);
            GXSetClipMode(GX_CLIP_ENABLE);
            GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
            GXSetDstAlpha(GX_FALSE, 0);
            GXSetAlphaUpdate(GX_FALSE);
            GXSetMisc(1, 8);
            GXColor mainColor = {64, 64, 192, 255};
            SetColor(mainColor);
            hel::math::Matrix34 viewMtx;
            SetViewMtx(viewMtx);
        }

        void SetColor(const GXColor& rColor) {
            GXSetTevColor(GX_TEVREG0, rColor);
        }

        void SetViewMtx(const hel::math::Matrix34& rViewMtx) {
            if (t_viewMtx.mBaseMtx == rViewMtx.mBaseMtx) {
                return;
            }
            PSMTXCopy(rViewMtx.mBaseMtx.mtx, t_viewMtx.mBaseMtx);
        }

        //https://decomp.me/scratch/aDscN
        void DrawCircleFill(const hel::math::Matrix34& rPosMtx, f32 arg2, f32 vertCount, const hel::math::Vector3 & rArg4, const hel::math::Vector3 & rArg5) {
            t_loadPosMtx(rPosMtx);
            GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 2.0f + vertCount);
            GXPosition3f32(0.0f, 0.0f, 0.0f);

            for (u32 i = 0;  i <= vertCount; i++) {
                f32 circumfrence = (2.0f * i * 3.1415927f) / vertCount;
                hel::math::Vector3 stack_A8 = rArg5 * (arg2 * -hel::math::Math::SinF(circumfrence));
                hel::math::Vector3 stack_9C = (rArg4 * (arg2 * hel::math::Math::CosF(circumfrence)));
                hel::math::Vector3 finalGXPosition = stack_9C + stack_A8;
                GXPosition3f32(finalGXPosition.x, finalGXPosition.y, finalGXPosition.z);
            }
        }

        void DrawQuadFill(const hel::math::Matrix34& rPosMtx, const hel::math::Vector3& rArg2, const hel::math::Vector3& rArg3,
            const hel::math::Vector3& rArg4, const hel::math::Vector3& rArg5) {

            t_loadPosMtx(rPosMtx);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(rArg2.x, rArg2.y, rArg2.z);
            GXPosition3f32(rArg3.x, rArg3.y, rArg3.z);
            GXPosition3f32(rArg4.x, rArg4.y, rArg4.z);
            GXPosition3f32(rArg5.x, rArg5.y, rArg5.z);
        }

        void DrawStarFill(const hel::math::Matrix34& rPosMtx, f32 arg2, f32 arg3, f32 vertCount, const hel::math::Vector3& rArg5, const hel::math::Vector3& rArg6) {
            f32 possibleBases[2];
            possibleBases[0] = arg2;
            possibleBases[1] = arg3;

            t_loadPosMtx(rPosMtx);
            GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 2.0f + vertCount);
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            for (u32 i = 0; i <= vertCount; i++) {
                f32 fVar1 = possibleBases[i & 1];
                f32 circumfrence = (2.0f * i * 3.1415927f) / vertCount;
                hel::math::Vector3 stack_A8 = rArg6 * (fVar1 * -hel::math::Math::SinF(circumfrence));
                hel::math::Vector3 stack_9C = (rArg5 * (fVar1 * hel::math::Math::CosF(circumfrence)));
                hel::math::Vector3 finalGXPosition = stack_9C + stack_A8;
                GXPosition3f32(finalGXPosition.x, finalGXPosition.y, finalGXPosition.z);
            }
        }

        void DrawLine(const hel::math::Matrix34 & rPosMtx, const hel::math::Vector3 & rArg2, const hel::math::Vector3 & rArg3, f32 lineWidth) {
            t_loadPosMtx(rPosMtx);
            u8 finalWidth = 6.0f * lineWidth;
            GXSetLineWidth(finalWidth, 0);
            GXBegin(GX_LINES, GX_VTXFMT0, 2);
            GXPosition3f32(rArg2.x, rArg2.y, rArg2.z);
            GXPosition3f32(rArg3.x, rArg3.y, rArg3.z);
        }

    }
}
