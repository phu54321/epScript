@EUDFunc
def f_x():
    _t1 = Forward()
    _t2 = (1 == 2)
    _t3 = 2 + 3
    _t4 = (_t3 == 5)
    _t5 = (7 == 8)
    _t6 = [_t4, _t5]
    _t7 = EUDOr([_t2, _t6])
    EUDJumpIfNot(_t7, _t1)
    _t1 << NextTrigger()

@EUDFunc
def f_y():
    _t1 = Forward()
    _t2 = (1 == 2)
    EUDJumpIfNot(_t2, _t1)
    _t3 = Forward()
    EUDJump(_t3)
    _t1 << NextTrigger()
    _t4 = Forward()
    _t5 = (4 == 5)
    EUDJumpIfNot(_t5, _t4)
    _t6 = Forward()
    EUDJump(_t6)
    _t4 << NextTrigger()
    _t6 << NextTrigger()
    _t3 << NextTrigger()
