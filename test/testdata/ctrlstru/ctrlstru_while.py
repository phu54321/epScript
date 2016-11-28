@EUDFunc
def f_x():
    _t1 = NextTrigger()
    _t2 = Forward()
    _t3 = (1 == 2)
    EUDJumpIfNot(_t3, _t2)
    EUDJump(_t1)
    EUDJump(_t1)
    _t2 << NextTrigger()
