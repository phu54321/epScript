from _epspy import a1
from test._epspy import a2
import a3
from test import a4
@EUDFunc
def f_x():
    A = 1
    A.B()
    f_dwread()
    a = EUDVariable()
    a << (f_dwread()[5])
    a << (A[5])
    _ARRW(A, a) << (7)
