@EUDFunc
def f_x():
    if EUDIf()(EUDOr(1 == 2, [2 + 3 == 5, 7 == 8])):
        EUDReturn(3)
    EUDEndIf()
    if EUDIf()(EUDOr(Always(), Never(), Always())):
        EUDReturn(5)
    EUDEndIf()

@EUDFunc
def f_y():
    if EUDIf()(1 == 2):
        EUDReturn(3)
    if EUDElseIf()(4 == 5):
        EUDReturn(6)
    if EUDElse()():
        EUDReturn(7)
    EUDEndIf()
