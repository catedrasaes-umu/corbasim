#ifndef MAPPING_SERVANT_HPP
#define MAPPING_SERVANT_HPP

#include "mappingS.h"
#include "mapping_adapted.hpp"

namespace corbasim
{
namespace adapted
{

template< >
struct servant< HelloApp::Hello >
{
    template < typename F >
    class _type : public virtual POA_HelloApp::Hello
    {
    public:

        _type(F f) :
            __f(f)
        {
        }


        char* sayHello()
        {
            _corbasim_HelloApp::Hello::sayHello _val;

            __f(_val);

            return CORBA::string_dup(_val._return);
        }

        char* sayHelloTo(const HelloApp::Names& people)
        {
            _corbasim_HelloApp::Hello::sayHelloTo _val(people);

            __f(_val);

            return CORBA::string_dup(_val._return);
        }

        void shutdown()
        {
            _corbasim_HelloApp::Hello::shutdown _val;

            __f(_val);

        }


    protected:
        F __f;
    };
};

} // adapted
} // corbasim

namespace corbasim
{
namespace adapted
{

template< >
struct servant< Test::Huge >
{
    template < typename F >
    class _type : public virtual POA_Test::Huge
    {
    public:

        _type(F f) :
            __f(f)
        {
        }


        void operation1(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation1 _val(a);

            __f(_val);

        }

        void operation2(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation2 _val(a);

            __f(_val);

        }

        void operation3(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation3 _val(a);

            __f(_val);

        }

        void operation4(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation4 _val(a);

            __f(_val);

        }

        void operation5(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation5 _val(a);

            __f(_val);

        }

        void operation6(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation6 _val(a);

            __f(_val);

        }

        void operation7(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation7 _val(a);

            __f(_val);

        }

        void operation8(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation8 _val(a);

            __f(_val);

        }

        void operation9(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation9 _val(a);

            __f(_val);

        }

        void operation10(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation10 _val(a);

            __f(_val);

        }

        void operation11(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation11 _val(a);

            __f(_val);

        }

        void operation12(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation12 _val(a);

            __f(_val);

        }

        void operation13(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation13 _val(a);

            __f(_val);

        }

        void operation14(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation14 _val(a);

            __f(_val);

        }

        void operation15(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation15 _val(a);

            __f(_val);

        }

        void operation16(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation16 _val(a);

            __f(_val);

        }

        void operation17(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation17 _val(a);

            __f(_val);

        }

        void operation18(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation18 _val(a);

            __f(_val);

        }

        void operation19(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation19 _val(a);

            __f(_val);

        }

        void operation20(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation20 _val(a);

            __f(_val);

        }

        void operation21(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation21 _val(a);

            __f(_val);

        }

        void operation22(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation22 _val(a);

            __f(_val);

        }

        void operation23(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation23 _val(a);

            __f(_val);

        }

        void operation24(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation24 _val(a);

            __f(_val);

        }

        void operation25(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation25 _val(a);

            __f(_val);

        }

        void operation26(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation26 _val(a);

            __f(_val);

        }

        void operation27(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation27 _val(a);

            __f(_val);

        }

        void operation28(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation28 _val(a);

            __f(_val);

        }

        void operation29(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation29 _val(a);

            __f(_val);

        }

        void operation30(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation30 _val(a);

            __f(_val);

        }

        void operation31(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation31 _val(a);

            __f(_val);

        }

        void operation32(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation32 _val(a);

            __f(_val);

        }

        void operation33(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation33 _val(a);

            __f(_val);

        }

        void operation34(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation34 _val(a);

            __f(_val);

        }

        void operation35(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation35 _val(a);

            __f(_val);

        }

        void operation36(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation36 _val(a);

            __f(_val);

        }

        void operation37(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation37 _val(a);

            __f(_val);

        }

        void operation38(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation38 _val(a);

            __f(_val);

        }

        void operation39(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation39 _val(a);

            __f(_val);

        }

        void operation40(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation40 _val(a);

            __f(_val);

        }

        void operation41(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation41 _val(a);

            __f(_val);

        }

        void operation42(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation42 _val(a);

            __f(_val);

        }

        void operation43(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation43 _val(a);

            __f(_val);

        }

        void operation44(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation44 _val(a);

            __f(_val);

        }

        void operation45(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation45 _val(a);

            __f(_val);

        }

        void operation46(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation46 _val(a);

            __f(_val);

        }

        void operation47(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation47 _val(a);

            __f(_val);

        }

        void operation48(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation48 _val(a);

            __f(_val);

        }

        void operation49(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation49 _val(a);

            __f(_val);

        }

        void operation50(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation50 _val(a);

            __f(_val);

        }

        void operation51(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation51 _val(a);

            __f(_val);

        }

        void operation52(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation52 _val(a);

            __f(_val);

        }

        void operation53(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation53 _val(a);

            __f(_val);

        }

        void operation54(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation54 _val(a);

            __f(_val);

        }

        void operation55(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation55 _val(a);

            __f(_val);

        }

        void operation56(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation56 _val(a);

            __f(_val);

        }

        void operation57(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation57 _val(a);

            __f(_val);

        }

        void operation58(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation58 _val(a);

            __f(_val);

        }

        void operation59(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation59 _val(a);

            __f(_val);

        }

        void operation60(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation60 _val(a);

            __f(_val);

        }

        void operation61(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation61 _val(a);

            __f(_val);

        }

        void operation62(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation62 _val(a);

            __f(_val);

        }

        void operation63(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation63 _val(a);

            __f(_val);

        }

        void operation64(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation64 _val(a);

            __f(_val);

        }

        void operation65(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation65 _val(a);

            __f(_val);

        }

        void operation66(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation66 _val(a);

            __f(_val);

        }

        void operation67(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation67 _val(a);

            __f(_val);

        }

        void operation68(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation68 _val(a);

            __f(_val);

        }

        void operation69(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation69 _val(a);

            __f(_val);

        }

        void operation70(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation70 _val(a);

            __f(_val);

        }

        void operation71(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation71 _val(a);

            __f(_val);

        }

        void operation72(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation72 _val(a);

            __f(_val);

        }

        void operation73(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation73 _val(a);

            __f(_val);

        }

        void operation74(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation74 _val(a);

            __f(_val);

        }

        void operation75(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation75 _val(a);

            __f(_val);

        }

        void operation76(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation76 _val(a);

            __f(_val);

        }

        void operation77(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation77 _val(a);

            __f(_val);

        }

        void operation78(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation78 _val(a);

            __f(_val);

        }

        void operation79(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation79 _val(a);

            __f(_val);

        }

        void operation80(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation80 _val(a);

            __f(_val);

        }

        void operation81(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation81 _val(a);

            __f(_val);

        }

        void operation82(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation82 _val(a);

            __f(_val);

        }

        void operation83(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation83 _val(a);

            __f(_val);

        }

        void operation84(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation84 _val(a);

            __f(_val);

        }

        void operation85(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation85 _val(a);

            __f(_val);

        }

        void operation86(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation86 _val(a);

            __f(_val);

        }

        void operation87(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation87 _val(a);

            __f(_val);

        }

        void operation88(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation88 _val(a);

            __f(_val);

        }

        void operation89(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation89 _val(a);

            __f(_val);

        }

        void operation90(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation90 _val(a);

            __f(_val);

        }

        void operation91(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation91 _val(a);

            __f(_val);

        }

        void operation92(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation92 _val(a);

            __f(_val);

        }

        void operation93(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation93 _val(a);

            __f(_val);

        }

        void operation94(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation94 _val(a);

            __f(_val);

        }

        void operation95(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation95 _val(a);

            __f(_val);

        }

        void operation96(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation96 _val(a);

            __f(_val);

        }

        void operation97(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation97 _val(a);

            __f(_val);

        }

        void operation98(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation98 _val(a);

            __f(_val);

        }

        void operation99(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation99 _val(a);

            __f(_val);

        }

        void operation100(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation100 _val(a);

            __f(_val);

        }

        void operation101(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation101 _val(a);

            __f(_val);

        }

        void operation102(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation102 _val(a);

            __f(_val);

        }

        void operation103(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation103 _val(a);

            __f(_val);

        }

        void operation104(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation104 _val(a);

            __f(_val);

        }

        void operation105(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation105 _val(a);

            __f(_val);

        }

        void operation106(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation106 _val(a);

            __f(_val);

        }

        void operation107(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation107 _val(a);

            __f(_val);

        }

        void operation108(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation108 _val(a);

            __f(_val);

        }

        void operation109(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation109 _val(a);

            __f(_val);

        }

        void operation110(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation110 _val(a);

            __f(_val);

        }

        void operation111(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation111 _val(a);

            __f(_val);

        }

        void operation112(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation112 _val(a);

            __f(_val);

        }

        void operation113(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation113 _val(a);

            __f(_val);

        }

        void operation114(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation114 _val(a);

            __f(_val);

        }

        void operation115(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation115 _val(a);

            __f(_val);

        }

        void operation116(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation116 _val(a);

            __f(_val);

        }

        void operation117(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation117 _val(a);

            __f(_val);

        }

        void operation118(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation118 _val(a);

            __f(_val);

        }

        void operation119(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation119 _val(a);

            __f(_val);

        }

        void operation120(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation120 _val(a);

            __f(_val);

        }

        void operation121(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation121 _val(a);

            __f(_val);

        }

        void operation122(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation122 _val(a);

            __f(_val);

        }

        void operation123(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation123 _val(a);

            __f(_val);

        }

        void operation124(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation124 _val(a);

            __f(_val);

        }

        void operation125(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation125 _val(a);

            __f(_val);

        }

        void operation126(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation126 _val(a);

            __f(_val);

        }

        void operation127(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation127 _val(a);

            __f(_val);

        }

        void operation128(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation128 _val(a);

            __f(_val);

        }

        void operation129(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation129 _val(a);

            __f(_val);

        }

        void operation130(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation130 _val(a);

            __f(_val);

        }

        void operation131(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation131 _val(a);

            __f(_val);

        }

        void operation132(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation132 _val(a);

            __f(_val);

        }

        void operation133(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation133 _val(a);

            __f(_val);

        }

        void operation134(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation134 _val(a);

            __f(_val);

        }

        void operation135(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation135 _val(a);

            __f(_val);

        }

        void operation136(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation136 _val(a);

            __f(_val);

        }

        void operation137(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation137 _val(a);

            __f(_val);

        }

        void operation138(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation138 _val(a);

            __f(_val);

        }

        void operation139(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation139 _val(a);

            __f(_val);

        }

        void operation140(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation140 _val(a);

            __f(_val);

        }

        void operation141(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation141 _val(a);

            __f(_val);

        }

        void operation142(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation142 _val(a);

            __f(_val);

        }

        void operation143(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation143 _val(a);

            __f(_val);

        }

        void operation144(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation144 _val(a);

            __f(_val);

        }

        void operation145(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation145 _val(a);

            __f(_val);

        }

        void operation146(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation146 _val(a);

            __f(_val);

        }

        void operation147(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation147 _val(a);

            __f(_val);

        }

        void operation148(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation148 _val(a);

            __f(_val);

        }

        void operation149(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation149 _val(a);

            __f(_val);

        }

        void operation150(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation150 _val(a);

            __f(_val);

        }

        void operation151(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation151 _val(a);

            __f(_val);

        }

        void operation152(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation152 _val(a);

            __f(_val);

        }

        void operation153(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation153 _val(a);

            __f(_val);

        }

        void operation154(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation154 _val(a);

            __f(_val);

        }

        void operation155(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation155 _val(a);

            __f(_val);

        }

        void operation156(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation156 _val(a);

            __f(_val);

        }

        void operation157(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation157 _val(a);

            __f(_val);

        }

        void operation158(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation158 _val(a);

            __f(_val);

        }

        void operation159(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation159 _val(a);

            __f(_val);

        }

        void operation160(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation160 _val(a);

            __f(_val);

        }

        void operation161(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation161 _val(a);

            __f(_val);

        }

        void operation162(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation162 _val(a);

            __f(_val);

        }

        void operation163(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation163 _val(a);

            __f(_val);

        }

        void operation164(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation164 _val(a);

            __f(_val);

        }

        void operation165(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation165 _val(a);

            __f(_val);

        }

        void operation166(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation166 _val(a);

            __f(_val);

        }

        void operation167(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation167 _val(a);

            __f(_val);

        }

        void operation168(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation168 _val(a);

            __f(_val);

        }

        void operation169(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation169 _val(a);

            __f(_val);

        }

        void operation170(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation170 _val(a);

            __f(_val);

        }

        void operation171(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation171 _val(a);

            __f(_val);

        }

        void operation172(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation172 _val(a);

            __f(_val);

        }

        void operation173(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation173 _val(a);

            __f(_val);

        }

        void operation174(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation174 _val(a);

            __f(_val);

        }

        void operation175(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation175 _val(a);

            __f(_val);

        }

        void operation176(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation176 _val(a);

            __f(_val);

        }

        void operation177(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation177 _val(a);

            __f(_val);

        }

        void operation178(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation178 _val(a);

            __f(_val);

        }

        void operation179(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation179 _val(a);

            __f(_val);

        }

        void operation180(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation180 _val(a);

            __f(_val);

        }

        void operation181(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation181 _val(a);

            __f(_val);

        }

        void operation182(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation182 _val(a);

            __f(_val);

        }

        void operation183(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation183 _val(a);

            __f(_val);

        }

        void operation184(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation184 _val(a);

            __f(_val);

        }

        void operation185(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation185 _val(a);

            __f(_val);

        }

        void operation186(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation186 _val(a);

            __f(_val);

        }

        void operation187(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation187 _val(a);

            __f(_val);

        }

        void operation188(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation188 _val(a);

            __f(_val);

        }

        void operation189(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation189 _val(a);

            __f(_val);

        }

        void operation190(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation190 _val(a);

            __f(_val);

        }

        void operation191(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation191 _val(a);

            __f(_val);

        }

        void operation192(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation192 _val(a);

            __f(_val);

        }

        void operation193(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation193 _val(a);

            __f(_val);

        }

        void operation194(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation194 _val(a);

            __f(_val);

        }

        void operation195(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation195 _val(a);

            __f(_val);

        }

        void operation196(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation196 _val(a);

            __f(_val);

        }

        void operation197(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation197 _val(a);

            __f(_val);

        }

        void operation198(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation198 _val(a);

            __f(_val);

        }

        void operation199(::CORBA::Long a)
        {
            _corbasim_Test::Huge::operation199 _val(a);

            __f(_val);

        }


    protected:
        F __f;
    };
};

} // adapted
} // corbasim

namespace corbasim
{
namespace adapted
{

template< >
struct servant< AAAAAAAAA::IIIIIIIIII >
{
    template < typename F >
    class _type : public virtual POA_AAAAAAAAA::IIIIIIIIII
    {
    public:

        _type(F f) :
            __f(f)
        {
        }


        AAAAAAAAA::EEESeq* op1()
        {
            _corbasim_AAAAAAAAA::IIIIIIIIII::op1 _val;

            __f(_val);

            return _val._return._retn();
        }

        AAAAAAAAA::ESS* op2()
        {
            _corbasim_AAAAAAAAA::IIIIIIIIII::op2 _val;

            __f(_val);

            return _val._return._retn();
        }


    protected:
        F __f;
    };
};

} // adapted
} // corbasim

namespace corbasim
{
namespace adapted
{

template< >
struct servant< SimpleExample::Test >
{
    template < typename F >
    class _type : public virtual POA_SimpleExample::Test
    {
    public:

        _type(F f) :
            __f(f)
        {
        }


        void operation1(::CORBA::Long a, ::CORBA::Long b, const SimpleExample::St& c)
        {
            _corbasim_SimpleExample::Test::operation1 _val(a, b, c);

            __f(_val);

        }

        void operation4(SimpleExample::Test_ptr a)
        {
            _corbasim_SimpleExample::Test::operation4 _val(a);

            __f(_val);

        }


    protected:
        F __f;
    };
};

} // adapted
} // corbasim

namespace corbasim
{
namespace adapted
{

template< >
struct servant< StringTest::InterfaceString >
{
    template < typename F >
    class _type : public virtual POA_StringTest::InterfaceString
    {
    public:

        _type(F f) :
            __f(f)
        {
        }


        void operation1(const char* s)
        {
            _corbasim_StringTest::InterfaceString::operation1 _val(s);

            __f(_val);

        }

        void operation2(const char* n)
        {
            _corbasim_StringTest::InterfaceString::operation2 _val(n);

            __f(_val);

        }

        void operation3(const StringTest::NameSeq& n)
        {
            _corbasim_StringTest::InterfaceString::operation3 _val(n);

            __f(_val);

        }

        void operation4(const StringTest::StructWithStrings& n)
        {
            _corbasim_StringTest::InterfaceString::operation4 _val(n);

            __f(_val);

        }

        void operation5(const char* n)
        {
            _corbasim_StringTest::InterfaceString::operation5 _val(n);

            __f(_val);

        }

        void operation6(const StringTest::NameIDSeq& n)
        {
            _corbasim_StringTest::InterfaceString::operation6 _val(n);

            __f(_val);

        }

        void operation7(const StringTest::StringSeq& n)
        {
            _corbasim_StringTest::InterfaceString::operation7 _val(n);

            __f(_val);

        }


    protected:
        F __f;
    };
};

} // adapted
} // corbasim

namespace corbasim
{
namespace adapted
{

template< >
struct servant< MyModule::MyInterface >
{
    template < typename F >
    class _type : public virtual POA_MyModule::MyInterface
    {
    public:

        _type(F f) :
            __f(f)
        {
        }


        void operation(const MyModule::MyUnion& uni)
        {
            _corbasim_MyModule::MyInterface::operation _val(uni);

            __f(_val);

        }

        void operation1(const MyModule::MyUnion2& uni)
        {
            _corbasim_MyModule::MyInterface::operation1 _val(uni);

            __f(_val);

        }

        void operation2(const MyModule::MyStruct& uni)
        {
            _corbasim_MyModule::MyInterface::operation2 _val(uni);

            __f(_val);

        }

        void operation3(const MyModule::MyUnion3& uni)
        {
            _corbasim_MyModule::MyInterface::operation3 _val(uni);

            __f(_val);

        }


    protected:
        F __f;
    };
};

} // adapted
} // corbasim

namespace corbasim
{
namespace adapted
{

template< >
struct servant< Test::Prueba >
{
    template < typename F >
    class _type : public virtual POA_Test::Prueba
    {
    public:

        _type(F f) :
            __f(f)
        {
        }


        void operacion1(const Test::St2& a, const Test::St& b)
        {
            _corbasim_Test::Prueba::operacion1 _val(a, b);

            __f(_val);

        }

        void operacion2(Test::Prueba_ptr myref)
        {
            _corbasim_Test::Prueba::operacion2 _val(myref);

            __f(_val);

        }

        void operacion3()
        {
            _corbasim_Test::Prueba::operacion3 _val;

            __f(_val);

        }


    protected:
        F __f;
    };
};

} // adapted
} // corbasim


#endif // MAPPING_SERVANT_HPP


