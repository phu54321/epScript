from xt import f_a
@EUDFunc
def f_x():
    A = List2Assignable([1])
    A.B()
    f_dwread()
    a = EUDVariable()
    a << f_dwread()[5]
