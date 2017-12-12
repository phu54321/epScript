class X(EUDStruct):
    _fields_ = [
    ]

t = _CGFW(lambda: [X()], 1)[0]
