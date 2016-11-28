@EUDFunc
def f_x(a, b):
    EUDReturn(a + b)

@EUDFunc
def f_y():
    f_x(1, 2)
