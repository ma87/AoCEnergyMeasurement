def test_1a():
    import day_1a

    answer = day_1a.read_and_solve()
    assert(402 == answer)


def test_1b():
    import day_1b
    
    answer = day_1b.read_and_solve()
    assert(481 == answer)


def test_2a():
    import day_2a
    
    answer = day_2a.read_and_solve()
    assert(4940 == answer)


def test_2b():
    import day_2b
    
    answer = day_2b.read_and_solve()
    assert('wrziyfdmlumeqvaatbiosngkc' == answer)


def test_3a():
    import day_3a
    
    answer = day_3a.read_and_solve()
    assert(121163 == answer)


def test_3b():
    import day_3b
    
    answer = day_3b.read_and_solve()
    assert(943 == answer)


def test_4a():
    import day_4a
    
    answer = day_4a.read_and_solve()
    assert(151754 == answer)


def test_4b():
    import day_4b
    
    answer = day_4b.read_and_solve()
    assert(19896 == answer)


def test_5a():
    import day_5a
    
    answer = day_5a.read_and_solve()
    assert(9704 == answer)


def test_5b():
    import day_5b
    
    answer = day_5b.read_and_solve()
    assert(6942 == answer)


def test_6a():
    import day_6a
    
    answer = day_6a.read_and_solve()
    assert(4976 == answer)


def test_6b():
    import day_6b
    
    answer = day_6b.read_and_solve()
    assert(46462 == answer)


def test_7a():
    import day_7a
    
    answer = day_7a.read_and_solve()
    assert('BFKEGNOVATIHXYZRMCJDLSUPWQ' == answer)


def test_7b():
    import day_7b
    
    answer = day_7b.read_and_solve()
    assert(1020 == answer)


def test_8a():
    import day_8a
    
    answer = day_8a.read_and_solve()
    assert(43825 == answer)


def test_8b():
    import day_8b
    
    answer = day_8b.read_and_solve()
    assert(19276 == answer)


def test_9a():
    import day_9a

    answer = day_9a.read_and_solve()
    assert(428690 == answer)
    

def test_9b():
    import day_9b

    answer = day_9b.read_and_solve()
    assert(3628143500 == answer)


def test_10a():
    import day_10a

    answer = day_10a.read_and_solve()
    expected = """xxxxx---xxxxx---x----x--x----x--x----x--xxxxxx--xxxxxx--xxxxx-
x----x--x----x--xx---x--xx---x--x----x--x------------x--x----x
x----x--x----x--xx---x--xx---x---x--x---x------------x--x----x
x----x--x----x--x-x--x--x-x--x---x--x---x-----------x---x----x
xxxxx---xxxxx---x-x--x--x-x--x----xx----xxxxx------x----xxxxx-
x--x----x-------x--x-x--x--x-x----xx----x---------x-----x--x--
x---x---x-------x--x-x--x--x-x---x--x---x--------x------x---x-
x---x---x-------x---xx--x---xx---x--x---x-------x-------x---x-
x----x--x-------x---xx--x---xx--x----x--x-------x-------x----x
x----x--x-------x----x--x----x--x----x--x-------xxxxxx--x----x"""
    assert(expected == answer)


def test_10b():
    import day_10b

    answer = day_10b.read_and_solve()
    assert(10946 == answer)


def test_11a():
    import day_11a

    answer = day_11a.read_and_solve()
    assert('243,72' == answer)


def test_11b():
    import day_11b

    answer = day_11b.read_and_solve()
    assert('229,192,11' == answer)