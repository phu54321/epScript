a = [EUDVariable() for _ in range(1)]
_IGVA(a, lambda: [1])
@EUDFunc
def f_x():
    A = 1
    A.B()
    f_dwread()
    a_1 = EUDVariable()
    a_1 << (f_dwread()[5])
    a_1 << (A[5])
    _ARRW(A, a_1) << (7)
