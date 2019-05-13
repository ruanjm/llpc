#version 450

layout(set = 0, binding = 0) uniform sampler2DShadow      samp2DShadow;
layout(set = 1, binding = 0) uniform sampler2DArrayShadow samp2DArrayShadow[4];
layout(set = 0, binding = 1) uniform sampler2DRectShadow  samp2DRectShadow;

layout(set = 2, binding = 0) uniform Uniforms
{
    int index;
    ivec2 i2;
};

layout(location = 0) out vec4 fragColor;

void main()
{
    vec4 f4 = textureGatherOffset(samp2DShadow, vec2(0.1), 0.9, ivec2(1));
    f4 += textureGatherOffset(samp2DArrayShadow[index], vec3(0.2), 0.8, i2);
    f4 += textureGatherOffset(samp2DRectShadow, vec2(1.0), 0.7, i2);

    fragColor = f4;
}
// BEGIN_SHADERTEST
/*
; RUN: amdllpc -spvgen-dir=%spvgendir% -v %gfxip %s | FileCheck -check-prefix=SHADERTEST %s
; SHADERTEST-LABEL: {{^// LLPC}} SPIRV-to-LLVM translation results
; SHADERTEST-LABEL: {{^// LLPC}}  SPIR-V lowering results
; SHADERTEST: call <4 x i32> {{.*}} @llpc.call.desc.load.sampler.v4i32(i32 0, i32 0, i32 0, i1 false)
; SHADERTEST: call <8 x i32> {{.*}} @llpc.call.desc.load.resource.v8i32(i32 0, i32 0, i32 0, i1 false)
; SHADERTEST: call <4 x float> @llpc.image.gather.f32.2D.dref.constoffset{{.*}}({{.*}},{{.*}}, <2 x float> <float 0x3FB99999A0000000, float 0x3FB99999A0000000>, float 0x3FECCCCCC0000000, <2 x i32> <i32 1, i32 1>,{{.*}})
; SHADERTEST: call <4 x i32> {{.*}} @llpc.call.desc.load.sampler.v4i32(i32 1, i32 0,{{.*}}, i1 false)
; SHADERTEST: call <8 x i32> {{.*}} @llpc.call.desc.load.resource.v8i32(i32 1, i32 0,{{.*}}, i1 false)
; SHADERTEST: call <4 x float> @llpc.image.gather.f32.2DArray.dref.offset{{.*}}({{.*}},{{.*}}, <3 x float> <float 0x3FC99999A0000000, float 0x3FC99999A0000000, float 0x3FC99999A0000000>, float 0x3FE99999A0000000,{{.*}},{{.*}})
; SHADERTEST: call <4 x i32> {{.*}} @llpc.call.desc.load.sampler.v4i32(i32 0, i32 1, i32 0, i1 false)
; SHADERTEST: call <8 x i32> {{.*}} @llpc.call.desc.load.resource.v8i32(i32 0, i32 1, i32 0, i1 false)
; SHADERTEST: call <4 x float> @llpc.image.gather.f32.Rect.dref.offset{{.*}}({{.*}},{{.*}}, <2 x float> <float 1.000000e+00, float 1.000000e+00>, float 0x3FE6666660000000,{{.*}},{{.*}})

; SHADERTEST-LABEL: {{^// LLPC}}  pipeline patching results
; SHADERTEST: call <4 x float> @llvm.amdgcn.image.gather4.c.lz.o.2d.v4f32.f32(i32 1, i32 257, float 0x3FECCCCCC0000000, float 0x3FB99999A0000000, float 0x3FB99999A0000000,{{.*}},{{.*}}, i1 false, i32 0, i32 0)
; SHADERTEST: call <4 x float> @llvm.amdgcn.image.gather4.c.lz.o.2darray.v4f32.f32(i32 1,{{.*}}, float 0x3FE99999A0000000, float 0x3FC99999A0000000, float 0x3FC99999A0000000, float 0.000000e+00,{{.*}},{{.*}}, i1 false, i32 0, i32 0)
; SHADERTEST: call <4 x float> @llvm.amdgcn.image.gather4.c.lz.o.2d.v4f32.f32(i32 1,{{.*}}, float 0x3FE6666660000000, float 1.000000e+00, float 1.000000e+00,{{.*}},{{.*}}, i1 false, i32 0, i32 0)
; SHADERTEST: AMDLLPC SUCCESS
*/
// END_SHADERTEST