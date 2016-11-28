# (Line 1) function x() {
@EUDFunc
def f_x():
    # (Line 2) if(1 == 2 || 2 + 3 == 5 && 7 == 8) 3;
    _t1 = Forward()
    _t2 = (1 == 2)
    _t3 = 2 + 3
    _t4 = (_t3 == 5)
    _t5 = (7 == 8)
    _t6 = [_t4, _t5]
    _t7 = EUDOr([_t2, _t6])
    EUDJumpIfNot(_t7, _t1)
    # (Line 3) }
    _t1 << NextTrigger()
    # (Line 5) function y() {

@EUDFunc
def f_y():
    # (Line 6) if(1 == 2) 3;
    _t1 = Forward()
    _t2 = (1 == 2)
    EUDJumpIfNot(_t2, _t1)
    # (Line 7) else if(4 == 5) 6;
    _t3 = Forward()
    EUDJump(_t3)
    _t1 << NextTrigger()
    _t4 = Forward()
    _t5 = (4 == 5)
    EUDJumpIfNot(_t5, _t4)
    # (Line 8) else 7;
    _t6 = Forward()
    EUDJump(_t6)
    _t4 << NextTrigger()
    # (Line 9) }
    _t6 << NextTrigger()
    _t3 << NextTrigger()
