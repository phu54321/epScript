# (Line 1) function x() {
@EUDFunc
def f_x():
    # (Line 2) while(1 == 2) continue;
    _t1 = NextTrigger()
    _t2 = Forward()
    _t3 = (1 == 2)
    EUDJumpIfNot(_t3, _t2)
    # (Line 3) }
    EUDJump(_t1)
    EUDJump(_t1)
    _t2 << NextTrigger()
