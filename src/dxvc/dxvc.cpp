// PIN_ROOT/source/include/pin/pin.H
#include "pin.H"

// PIN_ROOT/extras/cxx/include/...
#include "fstream"
#include "iostream"
#include "unordered_map"

// clang-format off

/// Type: x86 Extension Sets
/// @note Add more sets here
enum class VXESet {
    _NONE_ = -1, ///< Not an extension
    SSE1f,       ///< SSE (Pentium 3, 1999), Floating-point
    SSE1i,       ///< SSE (Pentium 3, 1999), Integer
    SSE2f,       ///< SSE2 (Pentium 4), Floating-point
    SSE2i,       ///< SSE2 (Pentium 4), Integer
    SSE3,        ///< SSE3 (later Pentium 4)
    SSSE3,       ///< SSSE3 (early Core 2)
    SSE41,       ///< SSE4.1 (later Core 2)
    SSE4a,       ///< SSE4.a (Phenom)
    SSE42,       ///< SSE4.2 (Nehalem)
    MMX,         ///< MMX (1996)
    AVX,         ///< AVX
    AVX2,        ///< AVX2
};

// << operator overload
std::ostream &operator<<(std::ostream &o, const VXESet &t) {
    switch (t) {
    case VXESet::_NONE_: o << "---";   break;
    case VXESet::SSE1f:  o << "SSE1f"; break;
    case VXESet::SSE1i:  o << "SSE1i"; break;
    case VXESet::SSE2f:  o << "SSE2f"; break;
    case VXESet::SSE2i:  o << "SSE2i"; break;
    case VXESet::SSE3:   o << "SSE3";  break;
    case VXESet::SSSE3:  o << "SSSE3"; break;
    case VXESet::SSE41:  o << "SSE41"; break;
    case VXESet::SSE4a:  o << "SSE4a"; break;
    case VXESet::SSE42:  o << "SSE42"; break;
    case VXESet::MMX:    o << "MMX";   break;
    case VXESet::AVX:    o << "AVX";   break;
    case VXESet::AVX2:   o << "AVX2";  break;
    }
    return o;
}

/// Table: Instruction -> Extension Set
/// @note Add more entries here
const std::unordered_map<UINT16, VXESet> VXTableESet = {
    // SSE (Pentium 3, 1999), Floating-point
    { XED_ICLASS_ADDSS,      VXESet::SSE1f },
    { XED_ICLASS_ADDPS,      VXESet::SSE1f },
    { XED_ICLASS_CMPPS,      VXESet::SSE1f },
    { XED_ICLASS_CMPSS,      VXESet::SSE1f },
    { XED_ICLASS_COMISS,     VXESet::SSE1f },
    { XED_ICLASS_CVTPI2PS,   VXESet::SSE1f },
    { XED_ICLASS_CVTPS2PI,   VXESet::SSE1f },
    { XED_ICLASS_CVTSI2SS,   VXESet::SSE1f },
    { XED_ICLASS_CVTSS2SI,   VXESet::SSE1f },
    { XED_ICLASS_CVTTPS2PI,  VXESet::SSE1f },
    { XED_ICLASS_CVTTSS2SI,  VXESet::SSE1f },
    { XED_ICLASS_DIVPS,      VXESet::SSE1f },
    { XED_ICLASS_DIVSS,      VXESet::SSE1f },
    { XED_ICLASS_LDMXCSR,    VXESet::SSE1f },
    { XED_ICLASS_MAXPS,      VXESet::SSE1f },
    { XED_ICLASS_MAXSS,      VXESet::SSE1f },
    { XED_ICLASS_MINPS,      VXESet::SSE1f },
    { XED_ICLASS_MINSS,      VXESet::SSE1f },
    { XED_ICLASS_MOVAPS,     VXESet::SSE1f },
    { XED_ICLASS_MOVHLPS,    VXESet::SSE1f },
    { XED_ICLASS_MOVHPS,     VXESet::SSE1f },
    { XED_ICLASS_MOVLHPS,    VXESet::SSE1f },
    { XED_ICLASS_MOVLPS,     VXESet::SSE1f },
    { XED_ICLASS_MOVMSKPS,   VXESet::SSE1f },
    { XED_ICLASS_MOVNTPS,    VXESet::SSE1f },
    { XED_ICLASS_MOVSS,      VXESet::SSE1f },
    { XED_ICLASS_MOVUPS,     VXESet::SSE1f },
    { XED_ICLASS_MULPS,      VXESet::SSE1f },
    { XED_ICLASS_MULSS,      VXESet::SSE1f },
    { XED_ICLASS_RCPPS,      VXESet::SSE1f },
    { XED_ICLASS_RCPSS,      VXESet::SSE1f },
    { XED_ICLASS_RSQRTPS,    VXESet::SSE1f },
    { XED_ICLASS_RSQRTSS,    VXESet::SSE1f },
    { XED_ICLASS_SHUFPS,     VXESet::SSE1f },
    { XED_ICLASS_SQRTPS,     VXESet::SSE1f },
    { XED_ICLASS_SQRTSS,     VXESet::SSE1f },
    { XED_ICLASS_STMXCSR,    VXESet::SSE1f },
    { XED_ICLASS_SUBPS,      VXESet::SSE1f },
    { XED_ICLASS_SUBSS,      VXESet::SSE1f },
    { XED_ICLASS_UCOMISS,    VXESet::SSE1f },
    { XED_ICLASS_UNPCKHPS,   VXESet::SSE1f },
    { XED_ICLASS_UNPCKLPS,   VXESet::SSE1f },
    // SSE (Pentium 3, 1999), Integer
    { XED_ICLASS_ANDNPS,     VXESet::SSE1i },
    { XED_ICLASS_ANDPS,      VXESet::SSE1i },
    { XED_ICLASS_ORPS,       VXESet::SSE1i },
    { XED_ICLASS_PAVGB,      VXESet::SSE1i },
    { XED_ICLASS_PAVGW,      VXESet::SSE1i },
    { XED_ICLASS_PEXTRW,     VXESet::SSE1i },
    { XED_ICLASS_PINSRW,     VXESet::SSE1i },
    { XED_ICLASS_PMAXSW,     VXESet::SSE1i },
    { XED_ICLASS_PMAXUB,     VXESet::SSE1i },
    { XED_ICLASS_PMINSW,     VXESet::SSE1i },
    { XED_ICLASS_PMINUB,     VXESet::SSE1i },
    { XED_ICLASS_PMOVMSKB,   VXESet::SSE1i },
    { XED_ICLASS_PMULHUW,    VXESet::SSE1i },
    { XED_ICLASS_PSADBW,     VXESet::SSE1i },
    { XED_ICLASS_PSHUFW,     VXESet::SSE1i },
    { XED_ICLASS_XORPS,      VXESet::SSE1i },
    // SSE2 (Pentium 4), Floating-point
    { XED_ICLASS_ADDPD,      VXESet::SSE2f },
    { XED_ICLASS_ADDSD,      VXESet::SSE2f },
    { XED_ICLASS_ANDNPD,     VXESet::SSE2f },
    { XED_ICLASS_ANDPD,      VXESet::SSE2f },
    { XED_ICLASS_CMPPD,      VXESet::SSE2f },
    { XED_ICLASS_CMPSD,      VXESet::SSE2f },
    { XED_ICLASS_COMISD,     VXESet::SSE2f },
    { XED_ICLASS_CVTDQ2PD,   VXESet::SSE2f },
    { XED_ICLASS_CVTDQ2PS,   VXESet::SSE2f },
    { XED_ICLASS_CVTPD2DQ,   VXESet::SSE2f },
    { XED_ICLASS_CVTPD2PI,   VXESet::SSE2f },
    { XED_ICLASS_CVTPD2PS,   VXESet::SSE2f },
    { XED_ICLASS_CVTPI2PD,   VXESet::SSE2f },
    { XED_ICLASS_CVTPS2DQ,   VXESet::SSE2f },
    { XED_ICLASS_CVTPS2PD,   VXESet::SSE2f },
    { XED_ICLASS_CVTSD2SI,   VXESet::SSE2f },
    { XED_ICLASS_CVTSD2SS,   VXESet::SSE2f },
    { XED_ICLASS_CVTSI2SD,   VXESet::SSE2f },
    { XED_ICLASS_CVTSS2SD,   VXESet::SSE2f },
    { XED_ICLASS_CVTTPD2DQ,  VXESet::SSE2f },
    { XED_ICLASS_CVTTPD2PI,  VXESet::SSE2f },
    { XED_ICLASS_CVTTPS2DQ,  VXESet::SSE2f },
    { XED_ICLASS_CVTTSD2SI,  VXESet::SSE2f },
    { XED_ICLASS_DIVPD,      VXESet::SSE2f },
    { XED_ICLASS_DIVSD,      VXESet::SSE2f },
    { XED_ICLASS_MAXPD,      VXESet::SSE2f },
    { XED_ICLASS_MAXSD,      VXESet::SSE2f },
    { XED_ICLASS_MINPD,      VXESet::SSE2f },
    { XED_ICLASS_MINSD,      VXESet::SSE2f },
    { XED_ICLASS_MOVAPD,     VXESet::SSE2f },
    { XED_ICLASS_MOVHPD,     VXESet::SSE2f },
    { XED_ICLASS_MOVLPD,     VXESet::SSE2f },
    { XED_ICLASS_MOVMSKPD,   VXESet::SSE2f },
    { XED_ICLASS_MOVSD,      VXESet::SSE2f },
    { XED_ICLASS_MOVUPD,     VXESet::SSE2f },
    { XED_ICLASS_MULPD,      VXESet::SSE2f },
    { XED_ICLASS_MULSD,      VXESet::SSE2f },
    { XED_ICLASS_ORPD,       VXESet::SSE2f },
    { XED_ICLASS_SHUFPD,     VXESet::SSE2f },
    { XED_ICLASS_SQRTPD,     VXESet::SSE2f },
    { XED_ICLASS_SQRTSD,     VXESet::SSE2f },
    { XED_ICLASS_SUBPD,      VXESet::SSE2f },
    { XED_ICLASS_SUBSD,      VXESet::SSE2f },
    { XED_ICLASS_UCOMISD,    VXESet::SSE2f },
    { XED_ICLASS_UNPCKHPD,   VXESet::SSE2f },
    { XED_ICLASS_UNPCKLPD,   VXESet::SSE2f },
    { XED_ICLASS_XORPD,      VXESet::SSE2f },
    // SSE2 (Pentium 4), Integer
    { XED_ICLASS_MOVDQ2Q,    VXESet::SSE2i },
    { XED_ICLASS_MOVDQA,     VXESet::SSE2i },
    { XED_ICLASS_MOVDQU,     VXESet::SSE2i },
    { XED_ICLASS_MOVQ2DQ,    VXESet::SSE2i },
    { XED_ICLASS_PADDQ,      VXESet::SSE2i },
    { XED_ICLASS_PSUBQ,      VXESet::SSE2i },
    { XED_ICLASS_PMULUDQ,    VXESet::SSE2i },
    { XED_ICLASS_PSHUFHW,    VXESet::SSE2i },
    { XED_ICLASS_PSHUFLW,    VXESet::SSE2i },
    { XED_ICLASS_PSHUFD,     VXESet::SSE2i },
    { XED_ICLASS_PSLLDQ,     VXESet::SSE2i },
    { XED_ICLASS_PSRLDQ,     VXESet::SSE2i },
    { XED_ICLASS_PUNPCKHQDQ, VXESet::SSE2i },
    { XED_ICLASS_PUNPCKLQDQ, VXESet::SSE2i },
    // SSE3 (later Pentium 4)
    { XED_ICLASS_ADDSUBPD,   VXESet::SSE3 },
    { XED_ICLASS_ADDSUBPS,   VXESet::SSE3 },
    { XED_ICLASS_HADDPD,     VXESet::SSE3 },
    { XED_ICLASS_HADDPS,     VXESet::SSE3 },
    { XED_ICLASS_HSUBPD,     VXESet::SSE3 },
    { XED_ICLASS_HSUBPS,     VXESet::SSE3 },
    { XED_ICLASS_MOVDDUP,    VXESet::SSE3 },
    { XED_ICLASS_MOVSHDUP,   VXESet::SSE3 },
    { XED_ICLASS_MOVSLDUP,   VXESet::SSE3 },
    // SSSE3 (early Core 2)
    { XED_ICLASS_PSIGNW,     VXESet::SSSE3 },
    { XED_ICLASS_PSIGND,     VXESet::SSSE3 },
    { XED_ICLASS_PSIGNB,     VXESet::SSSE3 },
    { XED_ICLASS_PSHUFB,     VXESet::SSSE3 },
    { XED_ICLASS_PMULHRSW,   VXESet::SSSE3 },
    { XED_ICLASS_PMADDUBSW,  VXESet::SSSE3 },
    { XED_ICLASS_PHSUBW,     VXESet::SSSE3 },
    { XED_ICLASS_PHSUBSW,    VXESet::SSSE3 },
    { XED_ICLASS_PHSUBD,     VXESet::SSSE3 },
    { XED_ICLASS_PHADDW,     VXESet::SSSE3 },
    { XED_ICLASS_PHADDSW,    VXESet::SSSE3 },
    { XED_ICLASS_PHADDD,     VXESet::SSSE3 },
    { XED_ICLASS_PALIGNR,    VXESet::SSSE3 },
    { XED_ICLASS_PABSW,      VXESet::SSSE3 },
    { XED_ICLASS_PABSD,      VXESet::SSSE3 },
    { XED_ICLASS_PABSB,      VXESet::SSSE3 },
    // SSE4.1 (later Core 2)
    { XED_ICLASS_MPSADBW,    VXESet::SSE41 },
    { XED_ICLASS_PHMINPOSUW, VXESet::SSE41 },
    { XED_ICLASS_PMULLD,     VXESet::SSE41 },
    { XED_ICLASS_PMULDQ,     VXESet::SSE41 },
    { XED_ICLASS_DPPS,       VXESet::SSE41 },
    { XED_ICLASS_DPPD,       VXESet::SSE41 },
    { XED_ICLASS_BLENDPS,    VXESet::SSE41 },
    { XED_ICLASS_BLENDPD,    VXESet::SSE41 },
    { XED_ICLASS_BLENDVPS,   VXESet::SSE41 },
    { XED_ICLASS_BLENDVPD,   VXESet::SSE41 },
    { XED_ICLASS_PBLENDVB,   VXESet::SSE41 },
    { XED_ICLASS_PBLENDW,    VXESet::SSE41 },
    { XED_ICLASS_PMINSB,     VXESet::SSE41 },
    { XED_ICLASS_PMAXSB,     VXESet::SSE41 },
    { XED_ICLASS_PMINUW,     VXESet::SSE41 },
    { XED_ICLASS_PMAXUW,     VXESet::SSE41 },
    { XED_ICLASS_PMINUD,     VXESet::SSE41 },
    { XED_ICLASS_PMAXUD,     VXESet::SSE41 },
    { XED_ICLASS_PMINSD,     VXESet::SSE41 },
    { XED_ICLASS_PMAXSD,     VXESet::SSE41 },
    { XED_ICLASS_ROUNDPS,    VXESet::SSE41 },
    { XED_ICLASS_ROUNDSS,    VXESet::SSE41 },
    { XED_ICLASS_ROUNDPD,    VXESet::SSE41 },
    { XED_ICLASS_ROUNDSD,    VXESet::SSE41 },
    { XED_ICLASS_INSERTPS,   VXESet::SSE41 },
    { XED_ICLASS_PINSRB,     VXESet::SSE41 },
    { XED_ICLASS_PINSRD,     VXESet::SSE41 },
    { XED_ICLASS_PINSRQ,     VXESet::SSE41 },
    { XED_ICLASS_EXTRACTPS,  VXESet::SSE41 },
    { XED_ICLASS_PEXTRB,     VXESet::SSE41 },
    { XED_ICLASS_PEXTRW,     VXESet::SSE41 },
    { XED_ICLASS_PEXTRD,     VXESet::SSE41 },
    { XED_ICLASS_PEXTRQ,     VXESet::SSE41 },
    { XED_ICLASS_PMOVSXBW,   VXESet::SSE41 },
    { XED_ICLASS_PMOVZXBW,   VXESet::SSE41 },
    { XED_ICLASS_PMOVSXBD,   VXESet::SSE41 },
    { XED_ICLASS_PMOVZXBD,   VXESet::SSE41 },
    { XED_ICLASS_PMOVSXBQ,   VXESet::SSE41 },
    { XED_ICLASS_PMOVZXBQ,   VXESet::SSE41 },
    { XED_ICLASS_PMOVSXWD,   VXESet::SSE41 },
    { XED_ICLASS_PMOVZXWD,   VXESet::SSE41 },
    { XED_ICLASS_PMOVSXWQ,   VXESet::SSE41 },
    { XED_ICLASS_PMOVZXWQ,   VXESet::SSE41 },
    { XED_ICLASS_PMOVSXDQ,   VXESet::SSE41 },
    { XED_ICLASS_PMOVZXDQ,   VXESet::SSE41 },
    { XED_ICLASS_PTEST,      VXESet::SSE41 },
    { XED_ICLASS_PCMPEQQ,    VXESet::SSE41 },
    { XED_ICLASS_PACKUSDW,   VXESet::SSE41 },
    { XED_ICLASS_MOVNTDQA,   VXESet::SSE41 },
    // SSE4.a (Phenom)
    { XED_ICLASS_LZCNT,      VXESet::SSE4a },
    { XED_ICLASS_POPCNT,     VXESet::SSE4a },
    { XED_ICLASS_EXTRQ,      VXESet::SSE4a },
    { XED_ICLASS_INSERTQ,    VXESet::SSE4a },
    { XED_ICLASS_MOVNTSD,    VXESet::SSE4a },
    { XED_ICLASS_MOVNTSS,    VXESet::SSE4a },
    // SSE4.2 (Nehalem)
    { XED_ICLASS_CRC32,      VXESet::SSE42 },
    { XED_ICLASS_PCMPESTRI,  VXESet::SSE42 },
    { XED_ICLASS_PCMPESTRM,  VXESet::SSE42 },
    { XED_ICLASS_PCMPISTRI,  VXESet::SSE42 },
    { XED_ICLASS_PCMPISTRM,  VXESet::SSE42 },
    { XED_ICLASS_PCMPGTQ,    VXESet::SSE42 },
    // MMX (1996)
    { XED_ICLASS_EMMS,       VXESet::MMX },
    { XED_ICLASS_MOVD,       VXESet::MMX },
    { XED_ICLASS_MOVQ,       VXESet::MMX },
    { XED_ICLASS_PACKSSDW,   VXESet::MMX },
    { XED_ICLASS_PACKSSWB,   VXESet::MMX },
    { XED_ICLASS_PACKUSWB,   VXESet::MMX },
    { XED_ICLASS_PADDB,      VXESet::MMX },
    { XED_ICLASS_PADDD,      VXESet::MMX },
    { XED_ICLASS_PADDSB,     VXESet::MMX },
    { XED_ICLASS_PADDSW,     VXESet::MMX },
    { XED_ICLASS_PADDUSB,    VXESet::MMX },
    { XED_ICLASS_PADDUSW,    VXESet::MMX },
    { XED_ICLASS_PADDW,      VXESet::MMX },
    { XED_ICLASS_PAND,       VXESet::MMX },
    { XED_ICLASS_PANDN,      VXESet::MMX },
    { XED_ICLASS_PCMPEQB,    VXESet::MMX },
    { XED_ICLASS_PCMPEQD,    VXESet::MMX },
    { XED_ICLASS_PCMPEQW,    VXESet::MMX },
    { XED_ICLASS_PCMPGTB,    VXESet::MMX },
    { XED_ICLASS_PCMPGTD,    VXESet::MMX },
    { XED_ICLASS_PCMPGTW,    VXESet::MMX },
    { XED_ICLASS_PMADDWD,    VXESet::MMX },
    { XED_ICLASS_PMULHW,     VXESet::MMX },
    { XED_ICLASS_PMULLW,     VXESet::MMX },
    { XED_ICLASS_POR,        VXESet::MMX },
    { XED_ICLASS_PSLLD,      VXESet::MMX },
    { XED_ICLASS_PSLLQ,      VXESet::MMX },
    { XED_ICLASS_PSLLW,      VXESet::MMX },
    { XED_ICLASS_PSRAD,      VXESet::MMX },
    { XED_ICLASS_PSRAW,      VXESet::MMX },
    { XED_ICLASS_PSRLD,      VXESet::MMX },
    { XED_ICLASS_PSRLQ,      VXESet::MMX },
    { XED_ICLASS_PSRLW,      VXESet::MMX },
    { XED_ICLASS_PSUBB,      VXESet::MMX },
    { XED_ICLASS_PSUBD,      VXESet::MMX },
    { XED_ICLASS_PSUBSB,     VXESet::MMX },
    { XED_ICLASS_PSUBSW,     VXESet::MMX },
    { XED_ICLASS_PSUBUSB,    VXESet::MMX },
    { XED_ICLASS_PSUBUSW,    VXESet::MMX },
    { XED_ICLASS_PSUBW,      VXESet::MMX },
    { XED_ICLASS_PUNPCKHBW,  VXESet::MMX },
    { XED_ICLASS_PUNPCKHDQ,  VXESet::MMX },
    { XED_ICLASS_PUNPCKHWD,  VXESet::MMX },
    { XED_ICLASS_PUNPCKLBW,  VXESet::MMX },
    { XED_ICLASS_PUNPCKLDQ,  VXESet::MMX },
    { XED_ICLASS_PUNPCKLWD,  VXESet::MMX },
    { XED_ICLASS_PXOR,       VXESet::MMX },
    // AVX
    { XED_ICLASS_VADDPD,                     VXESet::AVX },
    { XED_ICLASS_VADDPS,                     VXESet::AVX },
    { XED_ICLASS_VADDSD,                     VXESet::AVX },
    { XED_ICLASS_VADDSS,                     VXESet::AVX },
    { XED_ICLASS_VADDSUBPD,                  VXESet::AVX },
    { XED_ICLASS_VADDSUBPS,                  VXESet::AVX },
    { XED_ICLASS_VANDNPD,                    VXESet::AVX },
    { XED_ICLASS_VANDNPS,                    VXESet::AVX },
    { XED_ICLASS_VANDPD,                     VXESet::AVX },
    { XED_ICLASS_VANDPS,                     VXESet::AVX },
    { XED_ICLASS_VBLENDPD,                   VXESet::AVX },
    { XED_ICLASS_VBLENDPS,                   VXESet::AVX },
    { XED_ICLASS_VBLENDVPD,                  VXESet::AVX },
    { XED_ICLASS_VBLENDVPS,                  VXESet::AVX },
    { XED_ICLASS_VCMPPD,                     VXESet::AVX },
    { XED_ICLASS_VCMPPS,                     VXESet::AVX },
    { XED_ICLASS_VCOMISD,                    VXESet::AVX },
    { XED_ICLASS_VCOMISS,                    VXESet::AVX },
    { XED_ICLASS_VCVTDQ2PD,                  VXESet::AVX },
    { XED_ICLASS_VCVTDQ2PS,                  VXESet::AVX },
    { XED_ICLASS_VCVTPD2DQ,                  VXESet::AVX },
    { XED_ICLASS_VCVTPD2PS,                  VXESet::AVX },
    { XED_ICLASS_VCVTPS2DQ,                  VXESet::AVX },
    { XED_ICLASS_VCVTPS2PD,                  VXESet::AVX },
    { XED_ICLASS_VCVTSD2SI,                  VXESet::AVX },
    { XED_ICLASS_VCVTSD2SS,                  VXESet::AVX },
    { XED_ICLASS_VCVTSI2SD,                  VXESet::AVX },
    { XED_ICLASS_VCVTSI2SS,                  VXESet::AVX },
    { XED_ICLASS_VCVTSS2SD,                  VXESet::AVX },
    { XED_ICLASS_VCVTSS2SI,                  VXESet::AVX },
    { XED_ICLASS_VCVTTPD2DQ,                 VXESet::AVX },
    { XED_ICLASS_VCVTTPS2DQ,                 VXESet::AVX },
    { XED_ICLASS_VCVTTSD2SI,                 VXESet::AVX },
    { XED_ICLASS_VCVTTSS2SI,                 VXESet::AVX },
    { XED_ICLASS_VDIVPD,                     VXESet::AVX },
    { XED_ICLASS_VDIVPS,                     VXESet::AVX },
    { XED_ICLASS_VDIVSD,                     VXESet::AVX },
    { XED_ICLASS_VDIVSS,                     VXESet::AVX },
    { XED_ICLASS_VDPPD,                      VXESet::AVX },
    { XED_ICLASS_VDPPS,                      VXESet::AVX },
    { XED_ICLASS_VEXTRACTPS,                 VXESet::AVX },
    { XED_ICLASS_VHADDPD,                    VXESet::AVX },
    { XED_ICLASS_VHADDPS,                    VXESet::AVX },
    { XED_ICLASS_VHSUBPD,                    VXESet::AVX },
    { XED_ICLASS_VHSUBPS,                    VXESet::AVX },
    { XED_ICLASS_VINSERTPS,                  VXESet::AVX },
    { XED_ICLASS_VLDDQU,                     VXESet::AVX },
    { XED_ICLASS_VLDMXCSR,                   VXESet::AVX },
    { XED_ICLASS_VMASKMOVDQU,                VXESet::AVX },
    { XED_ICLASS_VMAXPD,                     VXESet::AVX },
    { XED_ICLASS_VMAXPS,                     VXESet::AVX },
    { XED_ICLASS_VMAXSD,                     VXESet::AVX },
    { XED_ICLASS_VMAXSS,                     VXESet::AVX },
    { XED_ICLASS_VMINPD,                     VXESet::AVX },
    { XED_ICLASS_VMINPS,                     VXESet::AVX },
    { XED_ICLASS_VMINSD,                     VXESet::AVX },
    { XED_ICLASS_VMINSS,                     VXESet::AVX },
    { XED_ICLASS_VMOVAPD,                    VXESet::AVX },
    { XED_ICLASS_VMOVAPS,                    VXESet::AVX },
    { XED_ICLASS_VMOVD,                      VXESet::AVX },
    { XED_ICLASS_VMOVDDUP,                   VXESet::AVX },
    { XED_ICLASS_VMOVDQA,                    VXESet::AVX },
    { XED_ICLASS_VMOVDQU,                    VXESet::AVX },
    { XED_ICLASS_VMOVHLPS,                   VXESet::AVX },
    { XED_ICLASS_VMOVHPD,                    VXESet::AVX },
    { XED_ICLASS_VMOVHPS,                    VXESet::AVX },
    { XED_ICLASS_VMOVLHPS,                   VXESet::AVX },
    { XED_ICLASS_VMOVLPD,                    VXESet::AVX },
    { XED_ICLASS_VMOVLPS,                    VXESet::AVX },
    { XED_ICLASS_VMOVMSKPD,                  VXESet::AVX },
    { XED_ICLASS_VMOVMSKPS,                  VXESet::AVX },
    { XED_ICLASS_VMOVNTDQ,                   VXESet::AVX },
    { XED_ICLASS_VMOVNTPD,                   VXESet::AVX },
    { XED_ICLASS_VMOVNTPS,                   VXESet::AVX },
    { XED_ICLASS_VMOVQ,                      VXESet::AVX },
    { XED_ICLASS_VMOVSD,                     VXESet::AVX },
    { XED_ICLASS_VMOVSHDUP,                  VXESet::AVX },
    { XED_ICLASS_VMOVSLDUP,                  VXESet::AVX },
    { XED_ICLASS_VMOVSS,                     VXESet::AVX },
    { XED_ICLASS_VMOVUPD,                    VXESet::AVX },
    { XED_ICLASS_VMOVUPS,                    VXESet::AVX },
    { XED_ICLASS_VMULPD,                     VXESet::AVX },
    { XED_ICLASS_VMULPS,                     VXESet::AVX },
    { XED_ICLASS_VMULSD,                     VXESet::AVX },
    { XED_ICLASS_VMULSS,                     VXESet::AVX },
    { XED_ICLASS_VORPD,                      VXESet::AVX },
    { XED_ICLASS_VORPS,                      VXESet::AVX },
    { XED_ICLASS_VPCMPESTRI,                 VXESet::AVX },
    { XED_ICLASS_VPCMPESTRM,                 VXESet::AVX },
    { XED_ICLASS_VPCMPISTRI,                 VXESet::AVX },
    { XED_ICLASS_VPCMPISTRM,                 VXESet::AVX },
    { XED_ICLASS_VPEXTRQ,                    VXESet::AVX },
    { XED_ICLASS_VPEXTRB,                    VXESet::AVX },
    { XED_ICLASS_VPEXTRD,                    VXESet::AVX },
    { XED_ICLASS_VPEXTRW,                    VXESet::AVX },
    { XED_ICLASS_VPHMINPOSUW,                VXESet::AVX },
    { XED_ICLASS_VPINSRQ,                    VXESet::AVX },
    { XED_ICLASS_VPINSRB,                    VXESet::AVX },
    { XED_ICLASS_VPINSRW,                    VXESet::AVX },
    { XED_ICLASS_VPINSRD,                    VXESet::AVX },
    { XED_ICLASS_VPINSRW,                    VXESet::AVX },
    { XED_ICLASS_VPTEST,                     VXESet::AVX },
    { XED_ICLASS_VRCPPS,                     VXESet::AVX },
    { XED_ICLASS_VRCPSS,                     VXESet::AVX },
    { XED_ICLASS_VROUNDPD,                   VXESet::AVX },
    { XED_ICLASS_VROUNDPS,                   VXESet::AVX },
    { XED_ICLASS_VROUNDSD,                   VXESet::AVX },
    { XED_ICLASS_VROUNDSS,                   VXESet::AVX },
    { XED_ICLASS_VRSQRTPS,                   VXESet::AVX },
    { XED_ICLASS_VRSQRTSS,                   VXESet::AVX },
    { XED_ICLASS_VSHUFPD,                    VXESet::AVX },
    { XED_ICLASS_VSHUFPS,                    VXESet::AVX },
    { XED_ICLASS_VSQRTPD,                    VXESet::AVX },
    { XED_ICLASS_VSQRTPS,                    VXESet::AVX },
    { XED_ICLASS_VSQRTSD,                    VXESet::AVX },
    { XED_ICLASS_VSQRTSS,                    VXESet::AVX },
    { XED_ICLASS_VSTMXCSR,                   VXESet::AVX },
    { XED_ICLASS_VSUBPD,                     VXESet::AVX },
    { XED_ICLASS_VSUBPS,                     VXESet::AVX },
    { XED_ICLASS_VSUBSD,                     VXESet::AVX },
    { XED_ICLASS_VSUBSS,                     VXESet::AVX },
    { XED_ICLASS_VUCOMISD,                   VXESet::AVX },
    { XED_ICLASS_VUCOMISS,                   VXESet::AVX },
    { XED_ICLASS_VUNPCKHPD,                  VXESet::AVX },
    { XED_ICLASS_VUNPCKHPS,                  VXESet::AVX },
    { XED_ICLASS_VUNPCKLPD,                  VXESet::AVX },
    { XED_ICLASS_VUNPCKLPS,                  VXESet::AVX },
    { XED_ICLASS_VBROADCASTF128,             VXESet::AVX },
    { XED_ICLASS_VEXTRACTF128,               VXESet::AVX },
    { XED_ICLASS_VINSERTF128,                VXESet::AVX },
    { XED_ICLASS_VMASKMOVPD,                 VXESet::AVX },
    { XED_ICLASS_VMASKMOVPS,                 VXESet::AVX },
    { XED_ICLASS_VPERM2F128,                 VXESet::AVX },
    { XED_ICLASS_VPERMILPD,                  VXESet::AVX },
    { XED_ICLASS_VPERMILPS,                  VXESet::AVX },
    { XED_ICLASS_VTESTPD,                    VXESet::AVX },
    { XED_ICLASS_VTESTPS,                    VXESet::AVX },
    { XED_ICLASS_VZEROALL,                   VXESet::AVX },
    { XED_ICLASS_VZEROUPPER,                 VXESet::AVX },
    { XED_ICLASS_VXORPD,                     VXESet::AVX },
    { XED_ICLASS_VXORPS,                     VXESet::AVX },
    { XED_ICLASS_VPCLMULQDQ,                 VXESet::AVX },
    // AVX2
    { XED_ICLASS_VMOVNTDQA,                  VXESet::AVX2 },
    { XED_ICLASS_VMPSADBW,                   VXESet::AVX2 },
    { XED_ICLASS_VPABSW,                     VXESet::AVX2 },
    { XED_ICLASS_VPABSB,                     VXESet::AVX2 },
    { XED_ICLASS_VPABSD,                     VXESet::AVX2 },
    { XED_ICLASS_VPABSQ,                     VXESet::AVX2 },
    { XED_ICLASS_VPACKSSDW,                  VXESet::AVX2 },
    { XED_ICLASS_VPACKSSWB,                  VXESet::AVX2 },
    { XED_ICLASS_VPACKUSDW,                  VXESet::AVX2 },
    { XED_ICLASS_VPACKUSWB,                  VXESet::AVX2 },
    { XED_ICLASS_VPADDQ,                     VXESet::AVX2 },
    { XED_ICLASS_VPADDW,                     VXESet::AVX2 },
    { XED_ICLASS_VPADDB,                     VXESet::AVX2 },
    { XED_ICLASS_VPADDD,                     VXESet::AVX2 },
    { XED_ICLASS_VPADDSW,                    VXESet::AVX2 },
    { XED_ICLASS_VPADDSB,                    VXESet::AVX2 },
    { XED_ICLASS_VPADDUSW,                   VXESet::AVX2 },
    { XED_ICLASS_VPADDUSB,                   VXESet::AVX2 },
    { XED_ICLASS_VPALIGNR,                   VXESet::AVX2 },
    { XED_ICLASS_VPAND,                      VXESet::AVX2 },
    { XED_ICLASS_VPANDN,                     VXESet::AVX2 },
    { XED_ICLASS_VPAVGW,                     VXESet::AVX2 },
    { XED_ICLASS_VPAVGB,                     VXESet::AVX2 },
    { XED_ICLASS_VPBLENDVB,                  VXESet::AVX2 },
    { XED_ICLASS_VPBLENDW,                   VXESet::AVX2 },
    { XED_ICLASS_VPCMPEQQ,                   VXESet::AVX2 },
    { XED_ICLASS_VPCMPEQW,                   VXESet::AVX2 },
    { XED_ICLASS_VPCMPEQD,                   VXESet::AVX2 },
    { XED_ICLASS_VPCMPEQB,                   VXESet::AVX2 },
    { XED_ICLASS_VPCMPGTQ,                   VXESet::AVX2 },
    { XED_ICLASS_VPCMPGTW,                   VXESet::AVX2 },
    { XED_ICLASS_VPCMPGTB,                   VXESet::AVX2 },
    { XED_ICLASS_VPCMPGTD,                   VXESet::AVX2 },
    { XED_ICLASS_VPHADDSW,                   VXESet::AVX2 },
    { XED_ICLASS_VPHADDW,                    VXESet::AVX2 },
    { XED_ICLASS_VPHADDD,                    VXESet::AVX2 },
    { XED_ICLASS_VPHSUBSW,                   VXESet::AVX2 },
    { XED_ICLASS_VPHSUBW,                    VXESet::AVX2 },
    { XED_ICLASS_VPHSUBD,                    VXESet::AVX2 },
    { XED_ICLASS_VPMADDUBSW,                 VXESet::AVX2 },
    { XED_ICLASS_VPMADDWD,                   VXESet::AVX2 },
    { XED_ICLASS_VPMAXSW,                    VXESet::AVX2 },
    { XED_ICLASS_VPMAXSB,                    VXESet::AVX2 },
    { XED_ICLASS_VPMAXSD,                    VXESet::AVX2 },
    { XED_ICLASS_VPMAXUB,                    VXESet::AVX2 },
    { XED_ICLASS_VPMAXUD,                    VXESet::AVX2 },
    { XED_ICLASS_VPMAXUW,                    VXESet::AVX2 },
    { XED_ICLASS_VPMINSB,                    VXESet::AVX2 },
    { XED_ICLASS_VPMINSD,                    VXESet::AVX2 },
    { XED_ICLASS_VPMINSW,                    VXESet::AVX2 },
    { XED_ICLASS_VPMINUB,                    VXESet::AVX2 },
    { XED_ICLASS_VPMINUD,                    VXESet::AVX2 },
    { XED_ICLASS_VPMINUW,                    VXESet::AVX2 },
    { XED_ICLASS_VPMOVMSKB,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVSXBD,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVSXBQ,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVSXBW,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVSXDQ,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVSXWD,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVSXWQ,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVZXBD,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVZXBQ,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVZXBW,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVZXDQ,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVZXWD,                  VXESet::AVX2 },
    { XED_ICLASS_VPMOVZXWQ,                  VXESet::AVX2 },
    { XED_ICLASS_VPMULDQ,                    VXESet::AVX2 },
    { XED_ICLASS_VPMULHRSW,                  VXESet::AVX2 },
    { XED_ICLASS_VPMULHUW,                   VXESet::AVX2 },
    { XED_ICLASS_VPMULHW,                    VXESet::AVX2 },
    { XED_ICLASS_VPMULLD,                    VXESet::AVX2 },
    { XED_ICLASS_VPMULLW,                    VXESet::AVX2 },
    { XED_ICLASS_VPMULUDQ,                   VXESet::AVX2 },
    { XED_ICLASS_VPOR,                       VXESet::AVX2 },
    { XED_ICLASS_VPSADBW,                    VXESet::AVX2 },
    { XED_ICLASS_VPSHUFB,                    VXESet::AVX2 },
    { XED_ICLASS_VPSHUFD,                    VXESet::AVX2 },
    { XED_ICLASS_VPSHUFHW,                   VXESet::AVX2 },
    { XED_ICLASS_VPSHUFLW,                   VXESet::AVX2 },
    { XED_ICLASS_VPSIGNW,                    VXESet::AVX2 },
    { XED_ICLASS_VPSIGNB,                    VXESet::AVX2 },
    { XED_ICLASS_VPSIGND,                    VXESet::AVX2 },
    { XED_ICLASS_VPSLLDQ,                    VXESet::AVX2 },
    { XED_ICLASS_VPSLLQ,                     VXESet::AVX2 },
    { XED_ICLASS_VPSLLW,                     VXESet::AVX2 },
    { XED_ICLASS_VPSLLD,                     VXESet::AVX2 },
    { XED_ICLASS_VPSRAW,                     VXESet::AVX2 },
    { XED_ICLASS_VPSRAD,                     VXESet::AVX2 },
    { XED_ICLASS_VPSRLDQ,                    VXESet::AVX2 },
    { XED_ICLASS_VPSRLQ,                     VXESet::AVX2 },
    { XED_ICLASS_VPSRLW,                     VXESet::AVX2 },
    { XED_ICLASS_VPSRLD,                     VXESet::AVX2 },
    { XED_ICLASS_VPSUBQ,                     VXESet::AVX2 },
    { XED_ICLASS_VPSUBW,                     VXESet::AVX2 },
    { XED_ICLASS_VPSUBB,                     VXESet::AVX2 },
    { XED_ICLASS_VPSUBD,                     VXESet::AVX2 },
    { XED_ICLASS_VPSUBSW,                    VXESet::AVX2 },
    { XED_ICLASS_VPSUBSB,                    VXESet::AVX2 },
    { XED_ICLASS_VPSUBUSW,                   VXESet::AVX2 },
    { XED_ICLASS_VPSUBUSB,                   VXESet::AVX2 },
    { XED_ICLASS_VPUNPCKHBW,                 VXESet::AVX2 },
    { XED_ICLASS_VPUNPCKHDQ,                 VXESet::AVX2 },
    { XED_ICLASS_VPUNPCKHQDQ,                VXESet::AVX2 },
    { XED_ICLASS_VPUNPCKHWD,                 VXESet::AVX2 },
    { XED_ICLASS_VPUNPCKLBW,                 VXESet::AVX2 },
    { XED_ICLASS_VPUNPCKLDQ,                 VXESet::AVX2 },
    { XED_ICLASS_VPUNPCKLQDQ,                VXESet::AVX2 },
    { XED_ICLASS_VPUNPCKLWD,                 VXESet::AVX2 },
    { XED_ICLASS_VPXOR,                      VXESet::AVX2 },
    { XED_ICLASS_VBROADCASTSD,               VXESet::AVX2 },
    { XED_ICLASS_VBROADCASTSS,               VXESet::AVX2 },
    { XED_ICLASS_VEXTRACTI128,               VXESet::AVX2 },
    { XED_ICLASS_VGATHERDPD,                 VXESet::AVX2 },
    { XED_ICLASS_VGATHERDPS,                 VXESet::AVX2 },
    { XED_ICLASS_VGATHERQPD,                 VXESet::AVX2 },
    { XED_ICLASS_VGATHERQPS,                 VXESet::AVX2 },
    { XED_ICLASS_VINSERTI128,                VXESet::AVX2 },
    { XED_ICLASS_VPBLENDD,                   VXESet::AVX2 },
    { XED_ICLASS_VPBROADCASTQ,               VXESet::AVX2 },
    { XED_ICLASS_VPBROADCASTW,               VXESet::AVX2 },
    { XED_ICLASS_VPBROADCASTB,               VXESet::AVX2 },
    { XED_ICLASS_VPBROADCASTD,               VXESet::AVX2 },
    { XED_ICLASS_VBROADCASTI128,             VXESet::AVX2 },
    { XED_ICLASS_VPERM2I128,                 VXESet::AVX2 },
    { XED_ICLASS_VPERMD,                     VXESet::AVX2 },
    { XED_ICLASS_VPERMPD,                    VXESet::AVX2 },
    { XED_ICLASS_VPERMPS,                    VXESet::AVX2 },
    { XED_ICLASS_VPERMQ,                     VXESet::AVX2 },
    { XED_ICLASS_VPGATHERDD,                 VXESet::AVX2 },
    { XED_ICLASS_VPGATHERDQ,                 VXESet::AVX2 },
    { XED_ICLASS_VPGATHERQD,                 VXESet::AVX2 },
    { XED_ICLASS_VPGATHERQQ,                 VXESet::AVX2 },
    { XED_ICLASS_VPMASKMOVQ,                 VXESet::AVX2 },
    { XED_ICLASS_VPMASKMOVD,                 VXESet::AVX2 },
    { XED_ICLASS_VPSLLVQ,                    VXESet::AVX2 },
    { XED_ICLASS_VPSLLVD,                    VXESet::AVX2 },
    { XED_ICLASS_VPSRAVD,                    VXESet::AVX2 },
    { XED_ICLASS_VPSRLVQ,                    VXESet::AVX2 },
    { XED_ICLASS_VPSRLVD,                    VXESet::AVX2 },
};

/// Get the Extension Set to which the current instruction belongs
/// @param o current instruction opcode
VXESet getVXESet(OPCODE opcode) {
    auto vxeset = VXTableESet.find(opcode);
    if (vxeset != VXTableESet.end())
        return vxeset->second;
    return VXESet::_NONE_;
}

/// Table: Instruction -> Description
/// @note Add more entries here
const std::unordered_map<UINT16, std::string> VXTableDesc = {
    // SSE (Pentium 3, 1999), Floating-Point
    { XED_ICLASS_ADDSS,      "Add Scalar Single-Precision Floating-Point Values" },
    { XED_ICLASS_ADDPS,      "Add Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_CMPPS,      "Compare Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_CMPSS,      "Compare Scalar Single-Precision Floating-Point Value" },
    { XED_ICLASS_COMISS,     "Compare Scalar Ordered Single-Precision Floating-Point Values and Set EFLAGS" },
    { XED_ICLASS_CVTPI2PS,   "Convert Packed Dword Integers to Packed Single-Precision FP Values" },
    { XED_ICLASS_CVTPS2PI,   "Convert Packed Single-Precision FP Values to Packed Dword Integers" },
    { XED_ICLASS_CVTSI2SS,   "Convert Doubleword Integer to Scalar Single-Precision Floating-Point Value" },
    { XED_ICLASS_CVTSS2SI,   "Convert Scalar Single-Precision Floating-Point Value to Doubleword Integer" },
    { XED_ICLASS_CVTTPS2PI,  "Convert with Truncation Packed Single-Precision FP Values to Packed Dword Integers" },
    { XED_ICLASS_CVTTSS2SI,  "Convert with Truncation Scalar Single-Precision Floating-Point Value to Integer" },
    { XED_ICLASS_DIVPS,      "Divide Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_DIVSS,      "Divide Scalar Single-Precision Floating-Point Values" },
    { XED_ICLASS_LDMXCSR,    "Load MXCSR Register" },
    { XED_ICLASS_MAXPS,      "Maximum of Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_MAXSS,      "Return Maximum Scalar Single-Precision Floating-Point Value" },
    { XED_ICLASS_MINPS,      "Minimum of Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_MINSS,      "Return Minimum Scalar Single-Precision Floating-Point Value" },
    { XED_ICLASS_MOVAPS,     "Move Aligned Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_MOVHLPS,    "Move Packed Single-Precision Floating-Point Values High to Low" },
    { XED_ICLASS_MOVHPS,     "Move High Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_MOVLHPS,    "Move Packed Single-Precision Floating-Point Values Low to High" },
    { XED_ICLASS_MOVLPS,     "Move Low Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_MOVMSKPS,   "Extract Packed Single-Precision Floating-Point Sign Mask" },
    { XED_ICLASS_MOVNTPS,    "Store Packed Single-Precision Floating-Point Values Using Non-Temporal Hint" },
    { XED_ICLASS_MOVSS,      "Move or Merge Scalar Single-Precision Floating-Point Value" },
    { XED_ICLASS_MOVUPS,     "Move Unaligned Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_MULPS,      "Multiply Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_MULSS,      "Multiply Scalar Single-Precision Floating-Point Values" },
    { XED_ICLASS_RCPPS,      "Compute Reciprocals of Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_RCPSS,      "Compute Reciprocal of Scalar Single-Precision Floating-Point Values" },
    { XED_ICLASS_RSQRTPS,    "Compute Reciprocals of Square Roots of Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_RSQRTSS,    "Compute Reciprocal of Square Root of Scalar Single-Precision Floating-Point Value" },
    { XED_ICLASS_SHUFPS,     "Packed Interleave Shuffle of Quadruplets of Single-Precision Floating-Point Values" },
    { XED_ICLASS_SQRTPS,     "Square Root of Single-Precision Floating-Point Values" },
    { XED_ICLASS_SQRTSS,     "Compute Square Root of Scalar Single-Precision Value" },
    { XED_ICLASS_STMXCSR,    "Store MXCSR Register State" },
    { XED_ICLASS_SUBPS,      "Subtract Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_SUBSS,      "Subtract Scalar Single-Precision Floating-Point Value" },
    { XED_ICLASS_UCOMISS,    "Unordered Compare Scalar Single-Precision Floating-Point Values and Set EFLAGS" },
    { XED_ICLASS_UNPCKHPS,   "Unpack and Interleave High Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_UNPCKLPS,   "Unpack and Interleave Low Packed Single-Precision Floating-Point Values" },
    // SSE (Pentium 3, 1999), Integer
    { XED_ICLASS_ANDNPS,     "Bitwise Logical AND NOT of Packed Single Precision Floating-Point Values" },
    { XED_ICLASS_ANDPS,      "Bitwise Logical AND of Packed Single Precision Floating-Point Values" },
    { XED_ICLASS_ORPS,       "Bitwise Logical OR of Packed Single Precision Floating-Point Values" },
    { XED_ICLASS_PAVGB,      "Average Packed Integers" },
    { XED_ICLASS_PAVGW,      "Average Packed Integers" },
    { XED_ICLASS_PEXTRW,     "Extract Word" },
    { XED_ICLASS_PINSRW,     "Insert Word" },
    { XED_ICLASS_PMAXSW,     "Maximum of Packed Signed Integers" },
    { XED_ICLASS_PMAXUB,     "Maximum of Packed Unsigned Integers" },
    { XED_ICLASS_PMINSW,     "Minimum of Packed Signed Integers" },
    { XED_ICLASS_PMINUB,     "Minimum of Packed Unsigned Integers" },
    { XED_ICLASS_PMOVMSKB,   "Move Byte Mask" },
    { XED_ICLASS_PMULHUW,    "Multiply Packed Unsigned Integers and Store High Result" },
    { XED_ICLASS_PSADBW,     "Compute Sum of Absolute Differences" },
    { XED_ICLASS_PSHUFW,     "Shuffle Packed Words" },
    { XED_ICLASS_XORPS,      "Bitwise Logical XOR of Packed Single Precision Floating-Point Values" },
    // SSE2 (Pentium 4), Floating-point
    { XED_ICLASS_ADDPD,      "Add Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_ADDSD,      "Add Scalar Double-Precision Floating-Point Values" },
    { XED_ICLASS_ANDNPD,     "Bitwise Logical AND NOT of Packed Double Precision Floating-Point Values" },
    { XED_ICLASS_ANDPD,      "Bitwise Logical AND of Packed Double Precision Floating-Point Values" },
    { XED_ICLASS_CMPPD,      "Compare Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_CMPSD,      "Compare Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_COMISD,     "Compare Scalar Ordered Double-Precision Floating-Point Values and Set EFLAGS" },
    { XED_ICLASS_CVTDQ2PD,   "Convert Packed Doubleword Integers to Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_CVTDQ2PS,   "Convert Packed Doubleword Integers to Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_CVTPD2DQ,   "Convert Packed Double-Precision Floating-Point Values to Packed Doubleword Integers" },
    { XED_ICLASS_CVTPD2PI,   "Convert Packed Double-Precision FP Values to Packed Dword Integers" },
    { XED_ICLASS_CVTPD2PS,   "Convert Packed Double-Precision Floating-Point Values to Packed Single-Precision Floating-Point Values" },
    { XED_ICLASS_CVTPI2PD,   "Convert Packed Dword Integers to Packed Double-Precision FP Values" },
    { XED_ICLASS_CVTPS2DQ,   "Convert Packed Single-Precision Floating-Point Values to Packed Signed Doubleword Integer Values" },
    { XED_ICLASS_CVTPS2PD,   "Convert Packed Single-Precision Floating-Point Values to Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_CVTSD2SI,   "Convert Scalar Double-Precision Floating-Point Value to Doubleword Integer" },
    { XED_ICLASS_CVTSD2SS,   "Convert Scalar Double-Precision Floating-Point Value to Scalar Single-Precision Floating-Point Value" },
    { XED_ICLASS_CVTSI2SD,   "Convert Doubleword Integer to Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_CVTSS2SD,   "Convert Scalar Single-Precision Floating-Point Value to Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_CVTTPD2DQ,  "Convert with Truncation Packed Double-Precision Floating-Point Values to Packed Doubleword Integers" },
    { XED_ICLASS_CVTTPD2PI,  "Convert with Truncation Packed Double-Precision FP Values to Packed Dword Integers" },
    { XED_ICLASS_CVTTPS2DQ,  "Convert with Truncation Packed Single-Precision Floating-Point Values to Packed Signed Doubleword Integer Values" },
    { XED_ICLASS_CVTTSD2SI,  "Convert with Truncation Scalar Double-Precision Floating-Point Value to Signed Integer" },
    { XED_ICLASS_DIVPD,      "Divide Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_DIVSD,      "Divide Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_MAXPD,      "Maximum of Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_MAXSD,      "Return Maximum Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_MINPD,      "Minimum of Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_MINSD,      "Return Minimum Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_MOVAPD,     "Move Aligned Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_MOVHPD,     "Move High Packed Double-Precision Floating-Point Value" },
    { XED_ICLASS_MOVLPD,     "Move Low Packed Double-Precision Floating-Point Value" },
    { XED_ICLASS_MOVMSKPD,   "Extract Packed Double-Precision Floating-Point Sign Mask" },
    { XED_ICLASS_MOVSD,      "Move or Merge Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_MOVUPD,     "Move Unaligned Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_MULPD,      "Multiply Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_MULSD,      "Multiply Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_ORPD,       "Bitwise Logical OR of Packed Double Precision Floating-Point Values" },
    { XED_ICLASS_SHUFPD,     "Packed Interleave Shuffle of Pairs of Double-Precision Floating-Point Values" },
    { XED_ICLASS_SQRTPD,     "Square Root of Double-Precision Floating-Point Values" },
    { XED_ICLASS_SQRTSD,     "Compute Square Root of Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_SUBPD,      "Subtract Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_SUBSD,      "Subtract Scalar Double-Precision Floating-Point Value" },
    { XED_ICLASS_UCOMISD,    "Unordered Compare Scalar Double-Precision Floating-Point Values and Set EFLAGS" },
    { XED_ICLASS_UNPCKHPD,   "Unpack and Interleave High Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_UNPCKLPD,   "Unpack and Interleave Low Packed Double-Precision Floating-Point Values" },
    { XED_ICLASS_XORPD,      "Bitwise Logical XOR of Packed Double Precision Floating-Point Values" },
    // SSE2 (Pentium 4), Integer
    { XED_ICLASS_MOVDQ2Q,    "Move Quadword from XMM to MMX Technology Register" },
    { XED_ICLASS_MOVDQA,     "Move Aligned Packed Integer Values" },
    { XED_ICLASS_MOVDQU,     "Move Unaligned Packed Integer Values" },
    { XED_ICLASS_MOVQ2DQ,    "Move Quadword from MMX Technology to XMM Register" },
    { XED_ICLASS_PADDQ,      "Add Packed Integers" },
    { XED_ICLASS_PSUBQ,      "Subtract Packed Quadword Integers" },
    { XED_ICLASS_PMULUDQ,    "Multiply Packed Unsigned Doubleword Integers" },
    { XED_ICLASS_PSHUFHW,    "Shuffle Packed High Words" },
    { XED_ICLASS_PSHUFLW,    "Shuffle Packed Low Words" },
    { XED_ICLASS_PSHUFD,     "Shuffle Packed Doublewords" },
    { XED_ICLASS_PSLLDQ,     "Shift Double Quadword Left Logical" },
    { XED_ICLASS_PSRLDQ,     "Shift Double Quadword Right Logical" },
    { XED_ICLASS_PUNPCKHQDQ, "Unpack High Data" },
    { XED_ICLASS_PUNPCKLQDQ, "Unpack Low Data" },
    // SSE3 (later Pentium 4)
    { XED_ICLASS_ADDSUBPD,   "Packed Double-FP Add/Subtract" },
    { XED_ICLASS_ADDSUBPS,   "Packed Single-FP Add/Subtract" },
    { XED_ICLASS_HADDPD,     "Packed Double-FP Horizontal Add" },
    { XED_ICLASS_HADDPS,     "Packed Single-FP Horizontal Add" },
    { XED_ICLASS_HSUBPD,     "Packed Double-FP Horizontal Subtract" },
    { XED_ICLASS_HSUBPS,     "Packed Single-FP Horizontal Subtract" },
    { XED_ICLASS_MOVDDUP,    "Replicate Double FP Values" },
    { XED_ICLASS_MOVSHDUP,   "Replicate Single FP Values" },
    { XED_ICLASS_MOVSLDUP,   "Replicate Single FP Values" },
    // SSSE3 (early Core 2)
    { XED_ICLASS_PSIGNW,     "Packed SIGN" },
    { XED_ICLASS_PSIGND,     "Packed SIGN" },
    { XED_ICLASS_PSIGNB,     "Packed SIGN" },
    { XED_ICLASS_PSHUFB,     "Packed Shuffle Bytes" },
    { XED_ICLASS_PMULHRSW,   "Packed Multiply High with Round and Scale" },
    { XED_ICLASS_PMADDUBSW,  "Multiply and Add Packed Signed and Unsigned Bytes" },
    { XED_ICLASS_PHSUBW,     "Packed Horizontal Subtract" },
    { XED_ICLASS_PHSUBSW,    "Packed Horizontal Subtract and Saturate" },
    { XED_ICLASS_PHSUBD,     "Packed Horizontal Subtract" },
    { XED_ICLASS_PHADDW,     "Packed Horizontal Add" },
    { XED_ICLASS_PHADDSW,    "Packed Horizontal Add and Saturate" },
    { XED_ICLASS_PHADDD,     "Packed Horizontal Add" },
    { XED_ICLASS_PALIGNR,    "Packed Align Right" },
    { XED_ICLASS_PABSW,      "Packed Absolute Value" },
    { XED_ICLASS_PABSD,      "Packed Absolute Value" },
    { XED_ICLASS_PABSB,      "Packed Absolute Value" },
    // SSE4.1 (later Core 2)
    { XED_ICLASS_MPSADBW,    "Compute Multiple Packed Sums of Absolute Difference" },
    { XED_ICLASS_PHMINPOSUW, "Packed Horizontal Word Minimum" },
    { XED_ICLASS_PMULLD,     "Multiply Packed Integers and Store Low Result" },
    { XED_ICLASS_PMULDQ,     "Multiply Packed Doubleword Integers" },
    { XED_ICLASS_DPPS,       "Dot Product of Packed Single Precision Floating-Point Values" },
    { XED_ICLASS_DPPD,       "Dot Product of Packed Double Precision Floating-Point Values" },
    { XED_ICLASS_BLENDPS,    "Blend Packed Single Precision Floating-Point Values" },
    { XED_ICLASS_BLENDPD,    "Blend Packed Double Precision Floating-Point Values" },
    { XED_ICLASS_BLENDVPS,   "Variable Blend Packed Single Precision Floating-Point Values" },
    { XED_ICLASS_BLENDVPD,   "Variable Blend Packed Double Precision Floating-Point Values" },
    { XED_ICLASS_PBLENDVB,   "Variable Blend Packed Bytes" },
    { XED_ICLASS_PBLENDW,    "Blend Packed Words" },
    { XED_ICLASS_PMINSB,     "Minimum of Packed Signed Integers" },
    { XED_ICLASS_PMAXSB,     "Maximum of Packed Signed Integers" },
    { XED_ICLASS_PMINUW,     "Minimum of Packed Unsigned Integers" },
    { XED_ICLASS_PMAXUW,     "Maximum of Packed Unsigned Integers" },
    { XED_ICLASS_PMINUD,     "Minimum of Packed Unsigned Integers" },
    { XED_ICLASS_PMAXUD,     "Maximum of Packed Unsigned Integers" },
    { XED_ICLASS_PMINSD,     "Minimum of Packed Signed Integers" },
    { XED_ICLASS_PMAXSD,     "Maximum of Packed Signed Integers" },
    { XED_ICLASS_ROUNDPS,    "Round Packed Single Precision Floating-Point Values" },
    { XED_ICLASS_ROUNDSS,    "Round Scalar Single Precision Floating-Point Values" },
    { XED_ICLASS_ROUNDPD,    "Round Packed Double Precision Floating-Point Values" },
    { XED_ICLASS_ROUNDSD,    "Round Scalar Double Precision Floating-Point Values" },
    { XED_ICLASS_INSERTPS,   "Insert Scalar Single-Precision Floating-Point Value" },
    { XED_ICLASS_PINSRB,     "Insert Byte/Dword/Qword" },
    { XED_ICLASS_PINSRD,     "Insert Byte/Dword/Qword" },
    { XED_ICLASS_PINSRQ,     "Insert Byte/Dword/Qword" },
    { XED_ICLASS_EXTRACTPS,  "Extract Packed Floating-Point Values" },
    { XED_ICLASS_PEXTRB,     "Extract Byte/Dword/Qword" },
    { XED_ICLASS_PEXTRW,     "Extract Word" },
    { XED_ICLASS_PEXTRD,     "Extract Byte/Dword/Qword" },
    { XED_ICLASS_PEXTRQ,     "Extract Byte/Dword/Qword" },
    { XED_ICLASS_PMOVSXBW,   "Packed Move with Sign Extend" },
    { XED_ICLASS_PMOVZXBW,   "Packed Move with Zero Extend" },
    { XED_ICLASS_PMOVSXBD,   "Packed Move with Sign Extend" },
    { XED_ICLASS_PMOVZXBD,   "Packed Move with Zero Extend" },
    { XED_ICLASS_PMOVSXBQ,   "Packed Move with Sign Extend" },
    { XED_ICLASS_PMOVZXBQ,   "Packed Move with Zero Extend" },
    { XED_ICLASS_PMOVSXWD,   "Packed Move with Zero ExtendPacked Move with Sign Extend" },
    { XED_ICLASS_PMOVZXWD,   "Packed Move with Zero Extend" },
    { XED_ICLASS_PMOVSXWQ,   "Packed Move with Sign Extend" },
    { XED_ICLASS_PMOVZXWQ,   "Packed Move with Zero Extend" },
    { XED_ICLASS_PMOVSXDQ,   "Packed Move with Sign Extend" },
    { XED_ICLASS_PMOVZXDQ,   "Packed Move with Zero Extend" },
    { XED_ICLASS_PTEST,      "Logical Compare" },
    { XED_ICLASS_PCMPEQQ,    "Compare Packed Qword Data for Equal" },
    { XED_ICLASS_PACKUSDW,   "Pack with Unsigned Saturation" },
    { XED_ICLASS_MOVNTDQA,   "Load Double Quadword Non-Temporal Aligned Hint" },
    // SSE4.a (Phenom)
    { XED_ICLASS_LZCNT,      "Count the Number of Leading Zero Bits" },
    { XED_ICLASS_POPCNT,     "Return the Count of Number of Bits Set to 1" },
    { XED_ICLASS_EXTRQ,      "Extract Byte/Dword/Qword" },
    { XED_ICLASS_INSERTQ,    "Insert Field" },
    { XED_ICLASS_MOVNTSD,    "Move Non-Temporal Scalar Double-Precision Floating-point" },
    { XED_ICLASS_MOVNTSS,    "Move Non-Temporal Scalar Single-Precision Floating-point" },
    // SSE4.2 (Nehalem)
    { XED_ICLASS_CRC32,      "Accumulate CRC32 Value" },
    { XED_ICLASS_PCMPESTRI,  "Packed Compare Explicit Length Strings and Return Index" },
    { XED_ICLASS_PCMPESTRM,  "Packed Compare Explicit Length Strings and Return Mask" },
    { XED_ICLASS_PCMPISTRI,  "Packed Compare Implicit Length Strings and Return Index" },
    { XED_ICLASS_PCMPISTRM,  "Packed Compare Implicit Length Strings and Return Mask" },
    { XED_ICLASS_PCMPGTQ,    "Compare Packed Data for Greater Than" },
    // MMX (1996)
    { XED_ICLASS_EMMS,       "Empty MMX Technology State" },
    { XED_ICLASS_MOVD,       "Move Doubleword/Move Quadword" },
    { XED_ICLASS_MOVQ,       "Move Doubleword/Move Quadword" },
    { XED_ICLASS_PACKSSDW,   "Pack with Signed Saturation" },
    { XED_ICLASS_PACKSSWB,   "Pack with Signed Saturation" },
    { XED_ICLASS_PACKUSWB,   "Pack with Unsigned Saturation" },
    { XED_ICLASS_PADDB,      "Add Packed Integers" },
    { XED_ICLASS_PADDD,      "Add Packed Integers" },
    { XED_ICLASS_PADDSB,     "Add Packed Signed Integers with Signed Saturation" },
    { XED_ICLASS_PADDSW,     "Add Packed Signed Integers with Signed Saturation" },
    { XED_ICLASS_PADDUSB,    "Add Packed Unsigned Integers with Unsigned Saturation" },
    { XED_ICLASS_PADDUSW,    "Add Packed Unsigned Integers with Unsigned Saturation" },
    { XED_ICLASS_PADDW,      "Add Packed Integers" },
    { XED_ICLASS_PAND,       "Logical AND" },
    { XED_ICLASS_PANDN,      "Logical AND NOT" },
    { XED_ICLASS_PCMPEQB,    "Compare Packed Data for Equal" },
    { XED_ICLASS_PCMPEQD,    "Compare Packed Data for Equal" },
    { XED_ICLASS_PCMPEQW,    "Compare Packed Data for Equal" },
    { XED_ICLASS_PCMPGTB,    "Compare Packed Signed Integers for Greater Than" },
    { XED_ICLASS_PCMPGTD,    "Compare Packed Signed Integers for Greater Than" },
    { XED_ICLASS_PCMPGTW,    "Compare Packed Signed Integers for Greater Than" },
    { XED_ICLASS_PMADDWD,    "Multiply and Add Packed Integers" },
    { XED_ICLASS_PMULHW,     "Multiply Packed Signed Integers and Store High Result" },
    { XED_ICLASS_PMULLW,     "Multiply Packed Signed Integers and Store Low Result" },
    { XED_ICLASS_POR,        "Bitwise Logical OR" },
    { XED_ICLASS_PSLLD,      "Shift Packed Data Left Logical" },
    { XED_ICLASS_PSLLQ,      "Shift Packed Data Left Logical" },
    { XED_ICLASS_PSLLW,      "Shift Packed Data Left Logical" },
    { XED_ICLASS_PSRAD,      "Shift Packed Data Right Arithmetic" },
    { XED_ICLASS_PSRAW,      "Shift Packed Data Right Arithmetic" },
    { XED_ICLASS_PSRLD,      "Shift Packed Data Right Logical" },
    { XED_ICLASS_PSRLQ,      "Shift Packed Data Right Logical" },
    { XED_ICLASS_PSRLW,      "Shift Packed Data Right Logical" },
    { XED_ICLASS_PSUBB,      "Subtract Packed Integers" },
    { XED_ICLASS_PSUBD,      "Subtract Packed Integers" },
    { XED_ICLASS_PSUBSB,     "Subtract Packed Signed Integers with Signed Saturation" },
    { XED_ICLASS_PSUBSW,     "Subtract Packed Signed Integers with Signed Saturation" },
    { XED_ICLASS_PSUBUSB,    "Subtract Packed Unsigned Integers with Unsigned Saturation" },
    { XED_ICLASS_PSUBUSW,    "Subtract Packed Unsigned Integers with Unsigned Saturation" },
    { XED_ICLASS_PSUBW,      "Subtract Packed Integers" },
    { XED_ICLASS_PUNPCKHBW,  "Unpack High Data" },
    { XED_ICLASS_PUNPCKHDQ,  "Unpack High Data" },
    { XED_ICLASS_PUNPCKHWD,  "Unpack High Data" },
    { XED_ICLASS_PUNPCKLBW,  "Unpack Low Data" },
    { XED_ICLASS_PUNPCKLDQ,  "Unpack Low Data" },
    { XED_ICLASS_PUNPCKLWD,  "Unpack Low Data" },
    { XED_ICLASS_PXOR,       "Logical Exclusive OR" },
};

/// Get the Description associated with the current instruction
/// @param o current instruction opcode
std::string getVXDesc(OPCODE opcode) {
    auto vxdesc = VXTableDesc.find(opcode);
    if (vxdesc != VXTableDesc.end())
        return vxdesc->second;
    return "";
}

/// Type: x86 Instruction Types
/// @note Add more types here
enum class VXType {
    _NONE_,
    LOAD,
    STORE,
    DATA_TRANSFER,
    CONVERSION,
    ARITHMETIC,
    COMPARISON,
    LOGICAL,
    EXTRACT,
    INSERT,
    SHUFFLE,
    SHIFT,
    PACK,
    UNPACK,
    STATE_MANAGEMENT,
};

// << operator overload
std::ostream &operator<<(std::ostream &o, const VXType &t) {
    switch (t) {
    case VXType::_NONE_:           o << "---";              break;
    case VXType::LOAD:             o << "LOAD";             break;
    case VXType::STORE:            o << "STORE";            break;
    case VXType::DATA_TRANSFER:    o << "DATA_TRANSFER";    break;
    case VXType::CONVERSION:       o << "CONVERSION";       break;
    case VXType::ARITHMETIC:       o << "ARITHMETIC";       break;
    case VXType::COMPARISON:       o << "COMPARISON";       break;
    case VXType::LOGICAL:          o << "LOGICAL";          break;
    case VXType::EXTRACT:          o << "EXTRACT";          break;
    case VXType::INSERT:           o << "INSERT";           break;
    case VXType::SHUFFLE:          o << "SHUFFLE";          break;
    case VXType::SHIFT:            o << "SHIFT";            break;
    case VXType::PACK:             o << "PACK";             break;
    case VXType::UNPACK:           o << "UNPACK";           break;
    case VXType::STATE_MANAGEMENT: o << "STATE_MANAGEMENT"; break;
    }
    return o;
}

/// Table: Instruction -> Type
/// @note Add more entries here
const std::unordered_map<UINT16, VXType> VXTableType = {
    // SSE (Pentium 3, 1999), Floating-Point
    { XED_ICLASS_ADDSS,      VXType::ARITHMETIC },
    { XED_ICLASS_ADDPS,      VXType::ARITHMETIC },
    { XED_ICLASS_CMPPS,      VXType::COMPARISON },
    { XED_ICLASS_CMPSS,      VXType::COMPARISON },
    { XED_ICLASS_COMISS,     VXType::COMPARISON },
    { XED_ICLASS_CVTPI2PS,   VXType::CONVERSION },
    { XED_ICLASS_CVTPS2PI,   VXType::CONVERSION },
    { XED_ICLASS_CVTSI2SS,   VXType::CONVERSION },
    { XED_ICLASS_CVTSS2SI,   VXType::CONVERSION },
    { XED_ICLASS_CVTTPS2PI,  VXType::CONVERSION },
    { XED_ICLASS_CVTTSS2SI,  VXType::CONVERSION },
    { XED_ICLASS_DIVPS,      VXType::ARITHMETIC },
    { XED_ICLASS_DIVSS,      VXType::ARITHMETIC },
    { XED_ICLASS_LDMXCSR,    VXType::LOAD },
    { XED_ICLASS_MAXPS,      VXType::COMPARISON },
    { XED_ICLASS_MAXSS,      VXType::COMPARISON },
    { XED_ICLASS_MINPS,      VXType::COMPARISON },
    { XED_ICLASS_MINSS,      VXType::COMPARISON },
    { XED_ICLASS_MOVAPS,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVHLPS,    VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVHPS,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVLHPS,    VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVLPS,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVMSKPS,   VXType::EXTRACT },
    { XED_ICLASS_MOVNTPS,    VXType::STORE },
    { XED_ICLASS_MOVSS,      VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVUPS,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MULPS,      VXType::ARITHMETIC },
    { XED_ICLASS_MULSS,      VXType::ARITHMETIC },
    { XED_ICLASS_RCPPS,      VXType::ARITHMETIC },
    { XED_ICLASS_RCPSS,      VXType::ARITHMETIC },
    { XED_ICLASS_RSQRTPS,    VXType::ARITHMETIC },
    { XED_ICLASS_RSQRTSS,    VXType::ARITHMETIC },
    { XED_ICLASS_SHUFPS,     VXType::SHUFFLE },
    { XED_ICLASS_SQRTPS,     VXType::ARITHMETIC },
    { XED_ICLASS_SQRTSS,     VXType::ARITHMETIC },
    { XED_ICLASS_STMXCSR,    VXType::STORE },
    { XED_ICLASS_SUBPS,      VXType::ARITHMETIC },
    { XED_ICLASS_SUBSS,      VXType::ARITHMETIC },
    { XED_ICLASS_UCOMISS,    VXType::COMPARISON },
    { XED_ICLASS_UNPCKHPS,   VXType::UNPACK },
    { XED_ICLASS_UNPCKLPS,   VXType::UNPACK },
    // SSE (Pentium 3, 1999), Integer
    { XED_ICLASS_ANDNPS,     VXType::LOGICAL },
    { XED_ICLASS_ANDPS,      VXType::LOGICAL },
    { XED_ICLASS_ORPS,       VXType::LOGICAL },
    { XED_ICLASS_PAVGB,      VXType::ARITHMETIC },
    { XED_ICLASS_PAVGW,      VXType::ARITHMETIC },
    { XED_ICLASS_PEXTRW,     VXType::EXTRACT },
    { XED_ICLASS_PINSRW,     VXType::INSERT },
    { XED_ICLASS_PMAXSW,     VXType::ARITHMETIC },
    { XED_ICLASS_PMAXUB,     VXType::ARITHMETIC },
    { XED_ICLASS_PMINSW,     VXType::ARITHMETIC },
    { XED_ICLASS_PMINUB,     VXType::ARITHMETIC },
    { XED_ICLASS_PMOVMSKB,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMULHUW,    VXType::ARITHMETIC },
    { XED_ICLASS_PSADBW,     VXType::ARITHMETIC },
    { XED_ICLASS_PSHUFW,     VXType::SHUFFLE },
    { XED_ICLASS_XORPS,      VXType::LOGICAL },
    // SSE2 (Pentium 4), Floating-point
    { XED_ICLASS_ADDPD,      VXType::ARITHMETIC },
    { XED_ICLASS_ADDSD,      VXType::ARITHMETIC },
    { XED_ICLASS_ANDNPD,     VXType::LOGICAL },
    { XED_ICLASS_ANDPD,      VXType::LOGICAL },
    { XED_ICLASS_CMPPD,      VXType::COMPARISON },
    { XED_ICLASS_CMPSD,      VXType::COMPARISON },
    { XED_ICLASS_COMISD,     VXType::COMPARISON },
    { XED_ICLASS_CVTDQ2PD,   VXType::CONVERSION },
    { XED_ICLASS_CVTDQ2PS,   VXType::CONVERSION },
    { XED_ICLASS_CVTPD2DQ,   VXType::CONVERSION },
    { XED_ICLASS_CVTPD2PI,   VXType::CONVERSION },
    { XED_ICLASS_CVTPD2PS,   VXType::CONVERSION },
    { XED_ICLASS_CVTPI2PD,   VXType::CONVERSION },
    { XED_ICLASS_CVTPS2DQ,   VXType::CONVERSION },
    { XED_ICLASS_CVTPS2PD,   VXType::CONVERSION },
    { XED_ICLASS_CVTSD2SI,   VXType::CONVERSION },
    { XED_ICLASS_CVTSD2SS,   VXType::CONVERSION },
    { XED_ICLASS_CVTSI2SD,   VXType::CONVERSION },
    { XED_ICLASS_CVTSS2SD,   VXType::CONVERSION },
    { XED_ICLASS_CVTTPD2DQ,  VXType::CONVERSION },
    { XED_ICLASS_CVTTPD2PI,  VXType::CONVERSION },
    { XED_ICLASS_CVTTPS2DQ,  VXType::CONVERSION },
    { XED_ICLASS_CVTTSD2SI,  VXType::CONVERSION },
    { XED_ICLASS_DIVPD,      VXType::ARITHMETIC },
    { XED_ICLASS_DIVSD,      VXType::ARITHMETIC },
    { XED_ICLASS_MAXPD,      VXType::COMPARISON },
    { XED_ICLASS_MAXSD,      VXType::COMPARISON },
    { XED_ICLASS_MINPD,      VXType::COMPARISON },
    { XED_ICLASS_MINSD,      VXType::COMPARISON },
    { XED_ICLASS_MOVAPD,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVHPD,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVLPD,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVMSKPD,   VXType::EXTRACT },
    { XED_ICLASS_MOVSD,      VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVUPD,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MULPD,      VXType::ARITHMETIC },
    { XED_ICLASS_MULSD,      VXType::ARITHMETIC },
    { XED_ICLASS_ORPD,       VXType::LOGICAL },
    { XED_ICLASS_SHUFPD,     VXType::SHUFFLE },
    { XED_ICLASS_SQRTPD,     VXType::ARITHMETIC },
    { XED_ICLASS_SQRTSD,     VXType::ARITHMETIC },
    { XED_ICLASS_SUBPD,      VXType::ARITHMETIC },
    { XED_ICLASS_SUBSD,      VXType::ARITHMETIC },
    { XED_ICLASS_UCOMISD,    VXType::COMPARISON },
    { XED_ICLASS_UNPCKHPD,   VXType::UNPACK },
    { XED_ICLASS_UNPCKLPD,   VXType::UNPACK },
    { XED_ICLASS_XORPD,      VXType::LOGICAL },
    // SSE2 (Pentium 4), Integer
    { XED_ICLASS_MOVDQ2Q,    VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVDQA,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVDQU,     VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVQ2DQ,    VXType::DATA_TRANSFER },
    { XED_ICLASS_PADDQ,      VXType::ARITHMETIC },
    { XED_ICLASS_PSUBQ,      VXType::ARITHMETIC },
    { XED_ICLASS_PMULUDQ,    VXType::ARITHMETIC },
    { XED_ICLASS_PSHUFHW,    VXType::SHUFFLE },
    { XED_ICLASS_PSHUFLW,    VXType::SHUFFLE },
    { XED_ICLASS_PSHUFD,     VXType::SHUFFLE },
    { XED_ICLASS_PSLLDQ,     VXType::SHIFT },
    { XED_ICLASS_PSRLDQ,     VXType::SHIFT },
    { XED_ICLASS_PUNPCKHQDQ, VXType::UNPACK },
    { XED_ICLASS_PUNPCKLQDQ, VXType::UNPACK },
    // SSE3 (later Pentium 4)
    { XED_ICLASS_ADDSUBPD,   VXType::ARITHMETIC },
    { XED_ICLASS_ADDSUBPS,   VXType::ARITHMETIC },
    { XED_ICLASS_HADDPD,     VXType::ARITHMETIC },
    { XED_ICLASS_HADDPS,     VXType::ARITHMETIC },
    { XED_ICLASS_HSUBPD,     VXType::ARITHMETIC },
    { XED_ICLASS_HSUBPS,     VXType::ARITHMETIC },
    { XED_ICLASS_MOVDDUP,    VXType::ARITHMETIC },
    { XED_ICLASS_MOVSHDUP,   VXType::ARITHMETIC },
    { XED_ICLASS_MOVSLDUP,   VXType::ARITHMETIC },
    // SSSE3 (early Core 2)
    { XED_ICLASS_PSIGNW,     VXType::ARITHMETIC },
    { XED_ICLASS_PSIGND,     VXType::ARITHMETIC },
    { XED_ICLASS_PSIGNB,     VXType::ARITHMETIC },
    { XED_ICLASS_PSHUFB,     VXType::SHUFFLE },
    { XED_ICLASS_PMULHRSW,   VXType::ARITHMETIC },
    { XED_ICLASS_PMADDUBSW,  VXType::ARITHMETIC },
    { XED_ICLASS_PHSUBW,     VXType::ARITHMETIC },
    { XED_ICLASS_PHSUBSW,    VXType::ARITHMETIC },
    { XED_ICLASS_PHSUBD,     VXType::ARITHMETIC },
    { XED_ICLASS_PHADDW,     VXType::ARITHMETIC },
    { XED_ICLASS_PHADDSW,    VXType::ARITHMETIC },
    { XED_ICLASS_PHADDD,     VXType::ARITHMETIC },
    { XED_ICLASS_PALIGNR,    VXType::ARITHMETIC },
    { XED_ICLASS_PABSW,      VXType::ARITHMETIC },
    { XED_ICLASS_PABSD,      VXType::ARITHMETIC },
    { XED_ICLASS_PABSB,      VXType::ARITHMETIC },
    // SSE4.1 (later Core 2)
    { XED_ICLASS_MPSADBW,    VXType::ARITHMETIC },
    { XED_ICLASS_PHMINPOSUW, VXType::COMPARISON },
    { XED_ICLASS_PMULLD,     VXType::ARITHMETIC },
    { XED_ICLASS_PMULDQ,     VXType::ARITHMETIC },
    { XED_ICLASS_DPPS,       VXType::ARITHMETIC },
    { XED_ICLASS_DPPD,       VXType::ARITHMETIC },
    { XED_ICLASS_BLENDPS,    VXType::DATA_TRANSFER },
    { XED_ICLASS_BLENDPD,    VXType::DATA_TRANSFER },
    { XED_ICLASS_BLENDVPS,   VXType::DATA_TRANSFER },
    { XED_ICLASS_BLENDVPD,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PBLENDVB,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PBLENDW,    VXType::DATA_TRANSFER },
    { XED_ICLASS_PMINSB,     VXType::COMPARISON },
    { XED_ICLASS_PMAXSB,     VXType::COMPARISON },
    { XED_ICLASS_PMINUW,     VXType::COMPARISON },
    { XED_ICLASS_PMAXUW,     VXType::COMPARISON },
    { XED_ICLASS_PMINUD,     VXType::COMPARISON },
    { XED_ICLASS_PMAXUD,     VXType::COMPARISON },
    { XED_ICLASS_PMINSD,     VXType::COMPARISON },
    { XED_ICLASS_PMAXSD,     VXType::COMPARISON },
    { XED_ICLASS_ROUNDPS,    VXType::ARITHMETIC },
    { XED_ICLASS_ROUNDSS,    VXType::ARITHMETIC },
    { XED_ICLASS_ROUNDPD,    VXType::ARITHMETIC },
    { XED_ICLASS_ROUNDSD,    VXType::ARITHMETIC },
    { XED_ICLASS_INSERTPS,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PINSRB,     VXType::DATA_TRANSFER },
    { XED_ICLASS_PINSRD,     VXType::DATA_TRANSFER },
    { XED_ICLASS_PINSRQ,     VXType::DATA_TRANSFER },
    { XED_ICLASS_EXTRACTPS,  VXType::DATA_TRANSFER},
    { XED_ICLASS_PEXTRB,     VXType::DATA_TRANSFER },
    { XED_ICLASS_PEXTRW,     VXType::DATA_TRANSFER },
    { XED_ICLASS_PEXTRD,     VXType::DATA_TRANSFER },
    { XED_ICLASS_PEXTRQ,     VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVSXBW,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVZXBW,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVSXBD,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVZXBD,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVSXBQ,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVZXBQ,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVSXWD,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVZXWD,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVSXWQ,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVZXWQ,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVSXDQ,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PMOVZXDQ,   VXType::DATA_TRANSFER },
    { XED_ICLASS_PTEST,      VXType::COMPARISON },
    { XED_ICLASS_PCMPEQQ,    VXType::COMPARISON },
    { XED_ICLASS_PACKUSDW,   VXType::PACK },
    { XED_ICLASS_MOVNTDQA,   VXType::LOAD },
    // SSE4.a (Phenom)
    { XED_ICLASS_LZCNT,      VXType::COMPARISON },
    { XED_ICLASS_POPCNT,     VXType::COMPARISON },
    { XED_ICLASS_EXTRQ,      VXType::DATA_TRANSFER },
    { XED_ICLASS_INSERTQ,    VXType::INSERT },
    { XED_ICLASS_MOVNTSD,    VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVNTSS,    VXType::DATA_TRANSFER },
    // SSE4.2 (Nehalem)
    { XED_ICLASS_CRC32,      VXType::ARITHMETIC },
    { XED_ICLASS_PCMPESTRI,  VXType::COMPARISON },
    { XED_ICLASS_PCMPESTRM,  VXType::COMPARISON },
    { XED_ICLASS_PCMPISTRI,  VXType::COMPARISON },
    { XED_ICLASS_PCMPISTRM,  VXType::COMPARISON },
    { XED_ICLASS_PCMPGTQ,    VXType::COMPARISON },
    // MMX (1996)
    { XED_ICLASS_EMMS,       VXType::STATE_MANAGEMENT },
    { XED_ICLASS_MOVD,       VXType::DATA_TRANSFER },
    { XED_ICLASS_MOVQ,       VXType::DATA_TRANSFER },
    { XED_ICLASS_PACKSSDW,   VXType::PACK },
    { XED_ICLASS_PACKSSWB,   VXType::PACK },
    { XED_ICLASS_PACKUSWB,   VXType::PACK },
    { XED_ICLASS_PADDB,      VXType::ARITHMETIC },
    { XED_ICLASS_PADDD,      VXType::ARITHMETIC },
    { XED_ICLASS_PADDSB,     VXType::ARITHMETIC },
    { XED_ICLASS_PADDSW,     VXType::ARITHMETIC },
    { XED_ICLASS_PADDUSB,    VXType::ARITHMETIC },
    { XED_ICLASS_PADDUSW,    VXType::ARITHMETIC },
    { XED_ICLASS_PADDW,      VXType::ARITHMETIC },
    { XED_ICLASS_PAND,       VXType::LOGICAL },
    { XED_ICLASS_PANDN,      VXType::LOGICAL },
    { XED_ICLASS_PCMPEQB,    VXType::COMPARISON },
    { XED_ICLASS_PCMPEQD,    VXType::COMPARISON },
    { XED_ICLASS_PCMPEQW,    VXType::COMPARISON },
    { XED_ICLASS_PCMPGTB,    VXType::COMPARISON },
    { XED_ICLASS_PCMPGTD,    VXType::COMPARISON },
    { XED_ICLASS_PCMPGTW,    VXType::COMPARISON },
    { XED_ICLASS_PMADDWD,    VXType::ARITHMETIC },
    { XED_ICLASS_PMULHW,     VXType::ARITHMETIC },
    { XED_ICLASS_PMULLW,     VXType::ARITHMETIC },
    { XED_ICLASS_POR,        VXType::LOGICAL },
    { XED_ICLASS_PSLLD,      VXType::SHIFT },
    { XED_ICLASS_PSLLQ,      VXType::SHIFT },
    { XED_ICLASS_PSLLW,      VXType::SHIFT },
    { XED_ICLASS_PSRAD,      VXType::SHIFT },
    { XED_ICLASS_PSRAW,      VXType::SHIFT },
    { XED_ICLASS_PSRLD,      VXType::SHIFT },
    { XED_ICLASS_PSRLQ,      VXType::SHIFT },
    { XED_ICLASS_PSRLW,      VXType::SHIFT },
    { XED_ICLASS_PSUBB,      VXType::ARITHMETIC },
    { XED_ICLASS_PSUBD,      VXType::ARITHMETIC },
    { XED_ICLASS_PSUBSB,     VXType::ARITHMETIC },
    { XED_ICLASS_PSUBSW,     VXType::ARITHMETIC },
    { XED_ICLASS_PSUBUSB,    VXType::ARITHMETIC },
    { XED_ICLASS_PSUBUSW,    VXType::ARITHMETIC },
    { XED_ICLASS_PSUBW,      VXType::ARITHMETIC },
    { XED_ICLASS_PUNPCKHBW,  VXType::UNPACK },
    { XED_ICLASS_PUNPCKHDQ,  VXType::UNPACK },
    { XED_ICLASS_PUNPCKHWD,  VXType::UNPACK },
    { XED_ICLASS_PUNPCKLBW,  VXType::UNPACK },
    { XED_ICLASS_PUNPCKLDQ,  VXType::UNPACK },
    { XED_ICLASS_PUNPCKLWD,  VXType::UNPACK },
    { XED_ICLASS_PXOR,       VXType::LOGICAL },
};

/// Get the Type associated with the current instruction
/// @param o current instruction opcode
VXType getVXType(OPCODE opcode) {
    auto vxtype = VXTableType.find(opcode);
    if (vxtype != VXTableType.end())
        return vxtype->second;
    return VXType::_NONE_;
}

// clang-format on

// Alias definition -> umap (extension-set: (opcode: counter))
using VXTableCount =
    std::unordered_map<VXESet, std::unordered_map<UINT16, UINT64>>;

/// Thread's data = id + counters
/// Let each thread's data be in its own data cache line so that
/// multiple threads do not contend for the same data cache line
struct ThreadData {
  THREADID id;
  VXTableCount tc;
  ThreadData();
};

// Constructor
ThreadData::ThreadData() : id(), tc() {}

// << operator overload
std::ostream &operator<<(std::ostream &o, const ThreadData &t) {
  for (auto &i : t.tc) {
    for (auto &j : i.second) {
      o << t.id;
      o << ',' << i.first;
      o << ',' << j.first;
      o << ',' << OPCODE_StringShort(j.first);
      auto css = CATEGORY_StringShort(j.first);
      o << ',' << (css == "LAST" ? "---" : css);
      auto ess = EXTENSION_StringShort(j.first);
      o << ',' << (ess == "LAST" ? "---" : ess);
      o << ',' << getVXType(j.first);
      o << ',' << j.second;
      o << ',' << getVXDesc(j.first) << std::endl;
    }
  }
  return o;
}

// Key for accessing TLS storage in the threads
// @note Initialized once in main()
static TLS_KEY tls_key;

/// Function to access thread-specific data
/// @param tid current thread id (assigned by pin)
ThreadData *getTLS(THREADID tid) {
  return static_cast<ThreadData *>(PIN_GetThreadData(tls_key, tid));
}

/// This function is called for every basic block
/// Increments the correct thread-local counter:
/// - extension-set -> opcode -> counter
/// @param o current instruction opcode
/// @param x current instruction extension-set
/// @param x current thread id (assigned by pin)
/// @note use atomic operations for multi-threaded applications
VOID PIN_FAST_ANALYSIS_CALL VXCountIncr(OPCODE opcode, VXESet eset,
                                        THREADID tid) {
  getTLS(tid)->tc[eset][opcode]++;
}

// Number of threads counter
INT32 NThreads = 0;
// Max number of threads allowed
const INT32 maxNThreads = 10000;

/// This function is called for every thread created
/// by the application when it is about to start
/// running (including the root thread)
/// @param tid thread id (assigned by pin)
/// @param ctxt initial register state for the new thread
/// @param flags thread creation flags (OS specific)
/// @param v value specified by the tool in the
///          PIN_AddThreadStartFunction call
VOID threadStart(THREADID tid, CONTEXT *ctxt, INT32 flags, VOID *v) {
  // Increase the number of threads counter
  NThreads++;

  // abort() if NThreads > maxNThreads
  // could be an ASSERT() call
  if (NThreads > maxNThreads) {
    std::cerr << "max number of threads exceeded!" << std::endl;
    PIN_ExitProcess(1);
  }

  // Create new ThreadData
  ThreadData *data = new ThreadData();
  PIN_SetThreadData(tls_key, data, tid);
  // Assign id
  data->id = tid;
}

/// This function is called every time a new trace is encountered
/// It inserts a call to the VXCountIncr analysis routine
/// @param trace trace to be instrumented
/// @param value specified by the tool in the
///        TRACE_AddInstrumentFunction call
VOID trace(TRACE trace, VOID *v) {
  // Visit every basic block in the trace
  for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl)) {
    // Visit every instruction in the current basic block
    for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins)) {
      // Get the current instruction opcode
      OPCODE insOpcode = INS_Opcode(ins);
      // Get the current instruction extension-set
      VXESet insESET = getVXESet(insOpcode);
      // If the current instruction is a vector instruction
      if (insESET != VXESet::_NONE_)
        // Insert a call to VXCountIncr passing the opcode
        // and the set of the instruction
        // IPOINT_ANYWHERE allows Pin to schedule the call
        // anywhere to obtain best performance
        BBL_InsertCall(bbl, IPOINT_ANYWHERE, (AFUNPTR)VXCountIncr,
                       IARG_FAST_ANALYSIS_CALL, IARG_UINT32, insOpcode,
                       IARG_UINT32, insESET, IARG_THREAD_ID, IARG_END);
    }
  }
}

// Thread's-data output stream
std::ostream *td_csvOut = nullptr;
// Thread's-data CSV header
const auto td_csvHeader =
    "thread,set,opcode,mnemonic,category,extension,type,counter,description";

/// This function is called for every thread destroyed
/// by the application
/// Print out analysis results:
/// - The data of threads to:
///   - <name>.td.csv OR
///   - stdout
/// @param tid thread id (assigned by pin)
/// @param ctxt initial register state for the new thread
/// @param flags thread creation flags (OS specific)
/// @param v value specified by the tool in the
///          PIN_AddThreadFiniFunction call
VOID threadFini(THREADID tid, const CONTEXT *ctxt, INT32 code, VOID *v) {
  *td_csvOut << *getTLS(tid);
}

// Number-of-threads output stream
std::ostream *nt_csvOut = nullptr;
// Number-of-threads CSV header
const auto nt_csvHeader = "threads";

/// This function is called when the application exits
/// Print out analysis results:
/// - Total number of threads to:
///   - <name>.nt.csv OR
///   - stdout
/// @param code exit code of the app
/// @param v value spcified by the tool in the
///          PIN_AddFiniFunction call
VOID fini(INT32 code, VOID *v) {
  *nt_csvOut << nt_csvHeader << std::endl;
  *nt_csvOut << NThreads << std::endl;
}

// Pintool name
const auto PINTOOL = "dxvc";

/// Print out usage and exit
INT32 usage() {
  std::cerr << PINTOOL << std::endl;
  std::cerr << "This pintool prints out the number of dynamically";
  std::cerr << "executed simd instructions, using thread-local counters";
  std::cerr << std::endl << std::endl;
  std::cerr << KNOB_BASE::StringKnobSummary() << std::endl;
  return 1;
}

// -o <name> flag/arg
// Specify output streams filename
KNOB<std::string> knobOFile(KNOB_MODE_WRITEONCE, "pintool", "o", "",
                            "output filename");

/// The main procedure of the tool
/// This function is called when the app image is loaded
/// but not yet started
/// @param argc total number of elements in the argv array
/// @param argv array of CLI args including `pin -t <pintool> -- ...`
int main(int argc, char *argv[]) {
  // Initialize pin
  // Print help message if:
  // - -h(elp) flag is specified in the CLI
  // - the CLI is invalid
  if (PIN_Init(argc, argv))
    return usage();

  // Header message
  std::cout << "INFO: This application is instrumented by " << PINTOOL;
  std::cout << std::endl;

  // Initialize output streams
  // If -o <name> flag/arg is passed:
  // - bind them to stdout
  // Otherwise:
  // - create <name>.td.csv stream
  // - create <name>.nt.csv stream
  if (knobOFile.Value().empty()) {
    td_csvOut = &std::cout;
    nt_csvOut = &std::cout;
    std::cout << "INFO: Writing to: stdout";
    std::cout << std::endl;
  } else {
    td_csvOut = new std::ofstream(knobOFile.Value() + ".td.csv");
    nt_csvOut = new std::ofstream(knobOFile.Value() + ".nt.csv");
    std::cout << "INFO: Writing to: " << knobOFile.Value() << ".[td,nt].csv";
    std::cout << std::endl;
  }

  // Obtain a key for TLS storage
  tls_key = PIN_CreateThreadDataKey(nullptr);
  // MAX_CLIENT_TLS_KEYS limit reached: abort()
  if (-1 == tls_key) {
    std::cerr << "num of already allocated keys reached the ";
    std::cerr << "MAX_CLIENT_TLS_KEYS limit";
    std::cerr << std::endl;
    PIN_ExitProcess(1);
  }

  // Print `threads data` header
  *td_csvOut << td_csvHeader << std::endl;

  // Register threadStart to be called when thread starts
  PIN_AddThreadStartFunction(threadStart, nullptr);
  // Register threadFini to be called when thread exits
  PIN_AddThreadFiniFunction(threadFini, nullptr);
  // Register fini to be called when the application exits
  PIN_AddFiniFunction(fini, nullptr);
  // Register trace to be called to instrument instructions
  TRACE_AddInstrumentFunction(trace, nullptr);

  // Divergent function: never returns
  PIN_StartProgram();

  return 1;
}
