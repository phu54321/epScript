//
// Created by phu54321 on 2017-12-10.
//

#include "test_base.hpp"

TEST_CASE("Object definition") {
    SECTION("Empty object definition & initialization") {
        check_string(
                "object X {}; const t = X();",
                "class X(EUDStruct):\n    _fields_ = []\n\nt = _CGFW(lambda: [X()], 1)[0]\n"
        );
    }

    SECTION("Member variable") {
        check_string(
                "object X { var x, y; };",
                "class X(EUDStruct):\n    _fields_ = ['x', 'y', ]\n"
        );
    }

    SECTION("Method") {
        check_string(
                "object X { function x() { return 0; } };",
                "class X(EUDStruct):\n    @EUDMethod\n    def x(this):\n        EUDReturn(0)\n\n    _fields_ = []\n"
        );
    }

    SECTION("Method & variable mix") {
        check_string(
            "object V2 {\n"
            "    var x;\n"
            "    function length_sq() {\n"
            "        return this.x * this.x + this.y * this.y;\n"
            "    }\n"
            "    var y;\n"
            "};",

            "class V2(EUDStruct):\n"
                    "    @EUDMethod\n"
                    "    def length_sq(this):\n"
                    "        EUDReturn(this.x * this.x + this.y * this.y)\n"
                    "\n"
                    "    _fields_ = ['x', 'y', ]"
        );
    }
}

TEST_CASE("Using objects") {
    SECTION("Object methods") {
        check_string(
                "function f(A) {\n"
                        "    const B = EUDByteReader();\n"
                        "    B.seekepd(A);\n"
                        "    A = B.k;\n"
                        "    B.k = 1;\n"
                        "    A, B.k = 3;\n"
                        "}",

                "@EUDFunc\n"
                        "def f_f(A):\n"
                        "    B = EUDByteReader()\n"
                        "    B.seekepd(A)\n"
                        "    A << (B.k)\n"
                        "    _ATTW(B, 'k') << (1)\n"
                        "    _SV([A, _ATTW(B, 'k')], [3])\n"
        );
    }
}

TEST_CASE("Allocating objects") {
    check_string(
            "object V2{}; const X = V2.alloc();",

            "class V2(EUDStruct):\n    _fields_ = []\n\nX = _CGFW(lambda: [V2.alloc()], 1)[0]\n"
    );
}
