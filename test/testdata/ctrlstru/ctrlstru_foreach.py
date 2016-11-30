@EUDFunc
def f_x():
    A, B = List2Assignable([1, 1])
    for x in A:
        pass

    x = EUDVariable()
    for x_1, y in B:
        DoActions(SetDeaths(x_1, 7, y, 0))
