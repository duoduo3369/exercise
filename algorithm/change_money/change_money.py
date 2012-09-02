def count_change(money):
    first_denomination = {1:1,
                          2:5,
                          3:10,
                          4:20,
                          5:50,
                          6:100
                          }
    def change(money,kind_of_coins):
        if money is 0:
            return 1
        elif money < 0 or kind_of_coins is 0:
            return 0
        else:
            return change(money,kind_of_coins-1) + \
                   change(money - first_denomination[kind_of_coins],
                          kind_of_coins)

    return change(money,6)
